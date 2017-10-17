#include "GenericConverter.h"

#ifndef __FF_CONVERTERS_H__
#define __FF_CONVERTERS_H__

class IntTypeConverter {
public:
  static bool assertType(v8::Local<v8::Value> jsVal) {
    return jsVal->IsInt32();
  }

	static int unwrap(v8::Local<v8::Value> jsVal) {
		return jsVal->Int32Value();
	}
};

typedef AbstractConverter<IntTypeConverter, int> IntConverter;
const char* IntConverter::typeName = "int";


class UintTypeConverter {
public:
	static bool assertType(v8::Local<v8::Value> jsVal) {
		return jsVal->IsUint32();
	}

	static uint unwrap(v8::Local<v8::Value> jsVal) {
		return jsVal->Uint32Value();
	}
};

typedef AbstractConverter<UintTypeConverter, uint> UintConverter;
const char* UintConverter::typeName = "uint";


class BoolTypeConverter {
public:
	static bool assertType(v8::Local<v8::Value> jsVal) {
		return jsVal->IsBoolean();
	}

	static bool unwrap(v8::Local<v8::Value> jsVal) {
		return jsVal->BooleanValue();
	}
};

typedef AbstractConverter<BoolTypeConverter, bool>  BoolConverter;
const char* BoolConverter::typeName = "bool";


template <class Clazz, class T>
class InstanceConverterType {
public:
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
		return assertType(jsVal);
	}
};

#endif