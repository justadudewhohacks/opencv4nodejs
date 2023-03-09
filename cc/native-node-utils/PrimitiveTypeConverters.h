#include "AbstractConverter.h"
#include "UnwrapperBase.h"
#include "utils.h"

#ifndef __FF_PRIMITIVE_TYPE_CONVERTERS_H__
#define __FF_PRIMITIVE_TYPE_CONVERTERS_H__

namespace FF {

	template<class ConverterImpl, class T>
	class PrimitiveTypeConverter : public UnwrapperBase<ConverterImpl, T> {
	public:
		static v8::Local<v8::Value> wrap(T val) {
			return Nan::New(val);
		}
	};

	class IntConverterImpl : public PrimitiveTypeConverter<IntConverterImpl, int> {
	public:
		typedef int Type;

		static std::string getTypeName() {
			return std::string("int");
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsInt32();
		}

		static int unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return Nan::To<int>(jsVal).ToChecked();
		}
	};

	class UintConverterImpl : public PrimitiveTypeConverter<UintConverterImpl, uint> {
	public:
		typedef uint Type;

		static std::string getTypeName() {
			return std::string("uint");
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsUint32();
		}

		static uint unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return Nan::To<uint>(jsVal).ToChecked();
		}
	};

	class LongConverterImpl : public PrimitiveTypeConverter<LongConverterImpl, long> {
	public:
		typedef long Type;

		static std::string getTypeName() {
			return std::string("long");
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsNumber();
		}

		static long unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return (long)Nan::To<int>(jsVal).ToChecked();
		}
	};

	class UlongConverterImpl : public PrimitiveTypeConverter<UlongConverterImpl, ulong> {
	public:
		typedef ulong Type;

		static std::string getTypeName() {
			return std::string("ulong");
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsNumber();
		}

		static ulong unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return (ulong)Nan::To<uint>(jsVal).ToChecked();
		}
	};

	class CharConverterImpl : public PrimitiveTypeConverter<CharConverterImpl, char> {
	public:
		typedef char Type;

		static std::string getTypeName() {
			return std::string("char");
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsNumber();
		}

		static char unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return (char)Nan::To<int>(jsVal).ToChecked();
		}
	};

	class UcharConverterImpl : public PrimitiveTypeConverter<UcharConverterImpl, uchar> {
	public:
		typedef uchar Type;

		static std::string getTypeName() {
			return std::string("uchar");
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsNumber();
		}

		static char unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return (uchar)Nan::To<uint>(jsVal).ToChecked();
		}
	};

	class BoolConverterImpl : public PrimitiveTypeConverter<BoolConverterImpl, bool> {
	public:
		typedef bool Type;

		static std::string getTypeName() {
			return std::string("bool");
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsBoolean();
		}

		static bool unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return Nan::To<bool>(jsVal).ToChecked();
		}
	};

	class DoubleConverterImpl : public PrimitiveTypeConverter<DoubleConverterImpl, double> {
	public:
		typedef double Type;

		static std::string getTypeName() {
			return std::string("double");
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsNumber();
		}

		static double unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return Nan::To<double>(jsVal).ToChecked();
		}
	};

	class FloatConverterImpl : public PrimitiveTypeConverter<FloatConverterImpl, float> {
	public:
		typedef float Type;

		static std::string getTypeName() {
			return std::string("float");
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsNumber();
		}

		static float unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return (float)Nan::To<double>(jsVal).ToChecked();
		}
	};

	class StringConverterImpl : public UnwrapperBase<StringConverterImpl, std::string> {
	public:
		typedef std::string Type;

		static std::string getTypeName() {
			return std::string("string");
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsString();
		}

		static std::string unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return std::string(*Nan::Utf8String(jsVal->ToString(Nan::GetCurrentContext()).ToLocalChecked()));
		}

		static v8::Local<v8::Value> wrap(std::string val) {
			return Nan::New(val).ToLocalChecked();
		}
	};

}

#endif