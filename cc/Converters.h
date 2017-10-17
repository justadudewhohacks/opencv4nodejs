#include "GenericConverter.h"

#ifndef __FF_CONVERTERS_H__
#define __FF_CONVERTERS_H__

class IntTypeConverter {
public:
	static const char* getTypeName() {
		return "int";
	}

  static bool assertType(v8::Local<v8::Value> jsVal) {
    return jsVal->IsInt32();
  }

	static int unwrap(v8::Local<v8::Value> jsVal) {
		return jsVal->Int32Value();
	}
};

typedef AbstractConverter<IntTypeConverter, int> IntConverter;


class UintTypeConverter {
public:
	static const char* getTypeName() {
		return "uint";
	}

	static bool assertType(v8::Local<v8::Value> jsVal) {
		return jsVal->IsUint32();
	}

	static uint unwrap(v8::Local<v8::Value> jsVal) {
		return jsVal->Uint32Value();
	}
};

typedef AbstractConverter<UintTypeConverter, uint> UintConverter;


class BoolTypeConverter {
public:
	static const char* getTypeName() {
		return "bool";
	}

	static bool assertType(v8::Local<v8::Value> jsVal) {
		return jsVal->IsBoolean();
	}

	static bool unwrap(v8::Local<v8::Value> jsVal) {
		return jsVal->BooleanValue();
	}
};

typedef AbstractConverter<BoolTypeConverter, bool>  BoolConverter;


template <class Clazz, class T>
class InstanceConverterType {
public:
	static const char* getTypeName() {
		return Clazz::getClassName();
	}

	static bool assertType(v8::Local<v8::Value> jsVal) {
		return Nan::New(Clazz::constructor)->HasInstance(jsVal);
	}

	static T unwrap(v8::Local<v8::Value> jsMat) {
		return Nan::ObjectWrap::Unwrap<Clazz>(jsMat->ToObject())->getNativeObject();
	}
};

template <class Clazz, class T>
class InstanceConverter : public AbstractConverter<InstanceConverterType<Clazz, T>, T> {
public:
	static bool hasInstance(v8::Local<v8::Value> jsVal) {
		return InstanceConverterType<Clazz, T>::assertType(jsVal);
	}
};

#endif