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
class AbstractConverter {
public:
	static const char* typeName;

	static bool assertType(v8::Local<v8::Value> jsVal) {
		return ConverterType::assertType(jsVal);
	}

	static T unwrap(v8::Local<v8::Value> jsVal) {
		return ConverterType::unwrap(jsVal);
	}

	static bool unwrap(T* val, v8::Local<v8::Value> jsVal) {
		if (!assertType(jsVal)) {
			return true;
		}
		*val = unwrap(jsVal);
		return false;
	}

	static bool optProp(T* val, const char* prop, v8::Local<v8::Object> opts) {
		if (Nan::HasOwnProperty(opts, Nan::New(prop).ToLocalChecked()).FromJust()) {
			Nan::ThrowError(
				Nan::New(
					std::string("expected property ")
					+ std::string(prop)
					+ std::string(" to be of type ")
					+ std::string(typeName)
				).ToLocalChecked()
			);
			return unwrap(val, Nan::Get(opts, Nan::New(prop).ToLocalChecked()).ToLocalChecked());
		}
		return false;
	}

	static bool arg(int argN, T* val, Nan::NAN_METHOD_ARGS_TYPE info) {
		if (!hasArg(argN, info) || unwrap(val, info[argN])) {
			Nan::ThrowError(
				Nan::New(
					std::string("expected argument ")
					+ std::to_string(argN)
					+ std::string(" to be of type ")
					+ std::string(typeName)
				).ToLocalChecked()
			);
			return true;
		}
		return false;
	}

	static bool optArg(int argN, T* val, Nan::NAN_METHOD_ARGS_TYPE info) {
		if (isCallback(argN, info)) {
			return false;
		}
		if (hasArg(argN, info) && unwrap(val, info[argN])) {
			Nan::ThrowError(
				Nan::New(
					std::string("expected argument ")
					+ std::to_string(argN)
					+ std::string(" to be of type ")
					+ std::string(typeName)
				).ToLocalChecked()
			);
			return true;
		}
		return false;
	}
};

#endif