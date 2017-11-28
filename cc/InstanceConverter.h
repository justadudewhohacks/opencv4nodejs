#include "AbstractConverter.h"

#ifndef __FF_INSTANCECONVERTER_H__
#define __FF_INSTANCECONVERTER_H__

template <class Clazz, class T>
class InstanceConverterType {
public:
	static const char* getTypeName() {
		return Clazz::getClassName();
	}

	static bool assertType(v8::Local<v8::Value> jsVal) {
		return !jsVal->IsNull() && !jsVal->IsUndefined() && Nan::New(Clazz::constructor)->HasInstance(jsVal);
	}

	static T unwrap(v8::Local<v8::Value> jsVal) {
		return Nan::ObjectWrap::Unwrap<Clazz>(jsVal->ToObject())->getNativeObject();
	}

	static T* unwrapPtr(v8::Local<v8::Value> jsVal) {
		return Nan::ObjectWrap::Unwrap<Clazz>(jsVal->ToObject())->getNativeObjectPtr();
	}

	static v8::Local<v8::Value> wrap(T val) {
		v8::Local<v8::Object> jsObj = Nan::NewInstance(Nan::New(Clazz::constructor)->GetFunction()).ToLocalChecked();
		*Nan::ObjectWrap::Unwrap<Clazz>(jsObj)->getNativeObjectPtr() = val;
		return jsObj;
	}
};

template <class Clazz, class T>
class InstanceConverter : public AbstractConverter<SingleTypeConverter<InstanceConverterType<Clazz, T>, T>, T> {
public:
	static bool hasInstance(v8::Local<v8::Value> jsVal) {
		return InstanceConverterType<Clazz, T>::assertType(jsVal);
	}
};

#endif