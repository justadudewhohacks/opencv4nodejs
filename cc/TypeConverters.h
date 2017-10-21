#include "AbstractConverter.h"

#ifndef __FF_TYPECONVERTERS_H__
#define __FF_TYPECONVERTERS_H__

template<typename T>
class TypeConverter {
public:
	static v8::Local<v8::Value> wrap(T val) {
		return Nan::New(val);
	}
};

class IntTypeConverter : public TypeConverter<int> {
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

typedef AbstractConverter<SingleTypeConverter<IntTypeConverter, int>, int> IntConverter;


class UintTypeConverter : public TypeConverter<uint> {
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

typedef AbstractConverter<SingleTypeConverter<UintTypeConverter, uint>, uint> UintConverter;


class BoolTypeConverter : public TypeConverter<bool> {
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

typedef AbstractConverter<SingleTypeConverter<BoolTypeConverter, bool>, bool>  BoolConverter;


class NumberTypeConverter : public TypeConverter<double> {
public:
	static const char* getTypeName() {
		return "number";
	}

	static bool assertType(v8::Local<v8::Value> jsVal) {
		return jsVal->IsNumber();
	}

	static double unwrap(v8::Local<v8::Value> jsVal) {
		return jsVal->NumberValue();
	}
};

typedef AbstractConverter<SingleTypeConverter<NumberTypeConverter, double>, double>  DoubleConverter;
typedef AbstractConverter<SingleTypeConverter<NumberTypeConverter, float>, float>  FloatConverter;

#endif