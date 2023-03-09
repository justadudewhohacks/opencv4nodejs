#include "utils.h"

#ifndef __FF_ABSTRACT_CONVERTER_H__
#define __FF_ABSTRACT_CONVERTER_H__

namespace FF {

	/*
	ConverterImpl implements:
		static std::string getTypeName()
		static v8::Local<v8::Value> wrap(ConverterImpl::Type val)
		static bool unwrap(ConverterImpl::Type* pVal, v8::Local<v8::Value> jsVal)
		static ConverterImpl::Type unwrapUnchecked(v8::Local<v8::Value> jsVal)
	*/
	template <class ConverterImpl>
	class AbstractConverter {
	public:
		typedef typename ConverterImpl::Type Type;

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return ConverterImpl::assertType(jsVal);
		}

		static v8::Local<v8::Value> wrap(Type val) {
			return ConverterImpl::wrap(val);
		}

		static Type unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return ConverterImpl::unwrapUnchecked(jsVal);
		}

		static bool unwrapTo(Type* val, v8::Local<v8::Value> jsVal) {
			if (ConverterImpl::unwrap(val, jsVal)) {
				Nan::ThrowError(FF::newString(
					std::string("failed to unwrap value, expected ") 
					+ std::string(ConverterImpl::getTypeName())
				));
				return true;
			}
			return false;
		}

		static bool arg(int argN, Type* val, Nan::NAN_METHOD_ARGS_TYPE info) {
			Nan::TryCatch tryCatch;
			if (!hasArg(info, argN) || ConverterImpl::unwrap(val, info[argN])) {
				if (tryCatch.HasCaught()) {
					tryCatch.ReThrow();
				}
				else {
					Nan::ThrowError(FF::newString(
						std::string("expected argument ")
						+ std::to_string(argN)
						+ std::string(" to be of type ")
						+ std::string(ConverterImpl::getTypeName())
					));
					tryCatch.ReThrow();
				}
				return true;
			}
			return false;
		}

		static bool optArg(int argN, Type* val, Nan::NAN_METHOD_ARGS_TYPE info) {
			if (hasArg(info, argN) && info[argN]->IsFunction()) {
				return false;
			}

			Nan::TryCatch tryCatch;
			if (hasArg(info, argN) && ConverterImpl::unwrap(val, info[argN])) {
				if (tryCatch.HasCaught()) {
					tryCatch.ReThrow();
				}
				else {
					Nan::ThrowError(FF::newString(
						std::string("expected argument ")
						+ std::to_string(argN)
						+ std::string(" to be of type ")
						+ std::string(ConverterImpl::getTypeName())
					));
					tryCatch.ReThrow();
				}
				return true;
			}
			return false;
		}

		static bool prop(Type* val, const char* prop, v8::Local<v8::Object> opts) {
			if (!Nan::HasOwnProperty(opts, Nan::New(prop).ToLocalChecked()).FromJust()) {
				Nan::ThrowError(FF::newString(
					std::string("expected object to have property: ") 
					+ std::string(prop)
				));
				return true;
			}

			return AbstractConverter::optProp(val, prop, opts);
		}

		static bool optProp(Type* val, const char* prop, v8::Local<v8::Object> opts) {
			Nan::TryCatch tryCatch;
			if (
				Nan::HasOwnProperty(opts, Nan::New(prop).ToLocalChecked()).FromJust()
				&& ConverterImpl::unwrap(val, Nan::Get(opts, Nan::New(prop).ToLocalChecked()).ToLocalChecked())
				) {
				if (tryCatch.HasCaught()) {
					tryCatch.ReThrow();
				}
				else {
					Nan::ThrowError(FF::newString(
						std::string("expected property ")
						+ std::string(prop)
						+ std::string(" to be of type ")
						+ std::string(ConverterImpl::getTypeName())
					));
					tryCatch.ReThrow();
				}
				return true;
			}
			return false;
		}
	};
}


#endif