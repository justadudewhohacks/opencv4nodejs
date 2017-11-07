#include "macros.h"

#ifndef __FF_GENERICCONVERTER_H__
#define __FF_GENERICCONVERTER_H__

typedef unsigned int uint;

static inline bool hasArg(int argN, Nan::NAN_METHOD_ARGS_TYPE info) {
	return argN < info.Length();
}

static inline bool isCallback(int argN, Nan::NAN_METHOD_ARGS_TYPE info) {
	return hasArg(argN, info) && info[argN]->IsFunction();
}

template <class ConverterType, class T>
class SingleTypeConverter {
public:
	static const char* getTypeName() {
		return ConverterType::getTypeName();
	}

	static bool assertType(v8::Local<v8::Value> jsVal) {
		return ConverterType::assertType(jsVal);
	}

	static T unwrap(v8::Local<v8::Value> jsVal) {
		return ConverterType::unwrap(jsVal);
	}

	static T* unwrapPtr(v8::Local<v8::Value> jsVal) {
		return ConverterType::unwrapPtr(jsVal);
	}

	static v8::Local<v8::Value> wrap(T val) {
		return ConverterType::wrap(val);
	}

	static bool unwrap(T* val, v8::Local<v8::Value> jsVal) {
		if (!assertType(jsVal)) {
			return true;
		}
		*val = unwrap(jsVal);
		return false;
	}
};

template <class ConverterType, class T>
class AbstractConverter {
public:
	static T unwrap(v8::Local<v8::Value> jsVal) {
		return ConverterType::unwrap(jsVal);
	}

	static T* unwrapPtr(v8::Local<v8::Value> jsVal) {
		return ConverterType::unwrapPtr(jsVal);
	}

	static v8::Local<v8::Value> wrap(T val) {
		return ConverterType::wrap(val);
	}

	static bool unwrap(T* val, v8::Local<v8::Value> jsVal) {
		return ConverterType::unwrap(val, jsVal);
	}

	static bool optProp(T* val, const char* prop, v8::Local<v8::Object> opts) {
		Nan::TryCatch tryCatch;
		if (
			Nan::HasOwnProperty(opts, Nan::New(prop).ToLocalChecked()).FromJust() 
			&& ConverterType::unwrap(val, Nan::Get(opts, Nan::New(prop).ToLocalChecked()).ToLocalChecked())
			) {
			if (tryCatch.HasCaught()) {
				tryCatch.ReThrow();
			}
			else {
				Nan::ThrowError(
					Nan::New(
						std::string("expected property ")
						+ std::string(prop)
						+ std::string(" to be of type ")
						+ std::string(ConverterType::getTypeName())
					).ToLocalChecked()
				);
				tryCatch.ReThrow();
			}
			return true;
		}
		return false;
	}

	static bool arg(int argN, T* val, Nan::NAN_METHOD_ARGS_TYPE info) {
		Nan::TryCatch tryCatch;
		if (!hasArg(argN, info) || ConverterType::unwrap(val, info[argN])) {
			if (tryCatch.HasCaught()) {
				tryCatch.ReThrow();
			} else {
				Nan::ThrowError(
					Nan::New(
						std::string("expected argument ")
						+ std::to_string(argN)
						+ std::string(" to be of type ")
						+ std::string(ConverterType::getTypeName())
					).ToLocalChecked()
				);
				tryCatch.ReThrow();
			}
			return true;
		}
		return false;
	}

	static bool optArg(int argN, T* val, Nan::NAN_METHOD_ARGS_TYPE info) {
		if (isCallback(argN, info)) {
			return false;
		}

		Nan::TryCatch tryCatch;
		if (hasArg(argN, info) && ConverterType::unwrap(val, info[argN])) {
			if (tryCatch.HasCaught()) {
				tryCatch.ReThrow();
			}
			else {
				Nan::ThrowError(
					Nan::New(
						std::string("expected argument ")
						+ std::to_string(argN)
						+ std::string(" to be of type ")
						+ std::string(ConverterType::getTypeName())
					).ToLocalChecked()
				);
				tryCatch.ReThrow();
			}
			return true;
		}
		return false;
	}
};

#endif