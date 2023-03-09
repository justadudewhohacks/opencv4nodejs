#include <memory>
#include <iostream>
#include <nan.h>

#ifndef __FF_UTILS_H__
#define __FF_UTILS_H__

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;

namespace FF {

	static inline v8::Local<v8::Function> getFunction(v8::Local<v8::FunctionTemplate> fnTempl) {
		return Nan::GetFunction(fnTempl).ToLocalChecked();
	}

	static inline v8::Local<v8::Object> newInstance(v8::Local<v8::FunctionTemplate> ctor) {
		return Nan::NewInstance(FF::getFunction(ctor)).ToLocalChecked();
	}

	static inline bool hasArg(Nan::NAN_METHOD_ARGS_TYPE info, int argN) {
		return argN < info.Length();
	}

	static inline bool isArgObject(Nan::NAN_METHOD_ARGS_TYPE info, int argN) {
		return FF::hasArg(info, argN) && info[argN]->IsObject() && !info[argN]->IsArray() && !info[argN]->IsFunction();
	}

	static inline v8::Local<v8::String> newString(std::string str) {
		return Nan::New(str).ToLocalChecked();
	}

	static inline bool hasOwnProperty(v8::Local<v8::Object> obj, const char* prop) {
		return Nan::HasOwnProperty(obj, FF::newString(prop)).FromJust();
	}

	template<class TClass>
	static inline TClass* unwrapNanObjectWrap(v8::Local<v8::Object> jsObj) {
		return Nan::ObjectWrap::Unwrap<TClass>(jsObj);
	}

	template<class TClass>
	static inline TClass* unwrapNanObjectWrap(v8::Local<v8::Value> jsVal) {
		return unwrapNanObjectWrap<TClass>(jsVal->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
	}

}

#endif
