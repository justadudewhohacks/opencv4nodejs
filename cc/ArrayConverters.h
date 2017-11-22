#include "TypeConverters.h"
#include "InstanceConverter.h"

#ifndef __FF_ARRAYCONVERTER_H__
#define __FF_ARRAYCONVERTER_H__

template <class Converter, class T, class CastType = T>
class ArrayConverterType {
public:
	static const char* getTypeName() {
		return "array";
	}

  static bool unwrap(std::vector<CastType>* vec, v8::Local<v8::Value> jsVal) {
		if (!jsVal->IsArray()) {
			return true;
		}

		v8::Local<v8::Array> jsArr = v8::Local<v8::Array>::Cast(jsVal);
    for (int i = 0; i < jsArr->Length(); i++) {
      if (!Converter::assertType(jsArr->Get(i))) {
				Nan::ThrowError(
					Nan::New(
						std::string("expected array element at index ")
						+ std::to_string(i)
						+ std::string(" to be of type ")
						+ std::string(Converter::getTypeName())
					).ToLocalChecked()
        );
        return true;
      }

			CastType obj = (CastType)Converter::unwrap(jsArr->Get(i));
      vec->push_back(obj);
    }
		return false;
	}

	static v8::Local<v8::Value> wrap(std::vector<CastType> vec) {
		v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(vec.size());
		for (int i = 0; i < jsArr->Length(); i++) {
			jsArr->Set(i, Converter::wrap(vec.at(i)));
		}
		return jsArr;
	}
};

class BoolArrayConverter : public AbstractConverter<ArrayConverterType<BoolTypeConverter, bool>, std::vector<bool>> {};
class DoubleArrayConverter : public AbstractConverter<ArrayConverterType<NumberTypeConverter, double>, std::vector<double>> {};
class FloatArrayConverter : public AbstractConverter<ArrayConverterType<NumberTypeConverter, float>, std::vector<float>> {};
class UintArrayConverter : public AbstractConverter<ArrayConverterType<UintTypeConverter, uint>, std::vector<uint>> {};
class IntArrayConverter : public AbstractConverter<ArrayConverterType<IntTypeConverter, int>, std::vector<int>> {};
class StringArrayConverter : public AbstractConverter<ArrayConverterType<StringTypeConverter, std::string>, std::vector<std::string>> {};

template <class Clazz, class T, class CastType = T>
class ObjectArrayConverter : public AbstractConverter<ArrayConverterType<InstanceConverterType<Clazz, CastType>, T, CastType>, std::vector<CastType>> {};


template <class Converter, class T, class CastType = T>
class ArrayOfArraysConverterType : private ArrayConverterType<Converter, T, CastType> {
public:
	static const char* getTypeName() {
		return "array";
	}

	static bool unwrap(std::vector<std::vector<CastType>>* vecOfVecs, v8::Local<v8::Value> jsVal) {
		if (!jsVal->IsArray()) {
			return true;
		}

		v8::Local<v8::Array> jsArr = v8::Local<v8::Array>::Cast(jsVal);
		for (int i = 0; i < jsArr->Length(); i++) {
			std::vector<CastType> vec;
			Nan::TryCatch tryCatch;
			if (ArrayConverterType<Converter, T, CastType>::unwrap(&vec, jsArr->Get(i))) {
				tryCatch.ReThrow();
				return true;
			}
			vecOfVecs->push_back(vec);
		}
		return false;
	}

	static v8::Local<v8::Value> wrap(std::vector<std::vector<CastType>> vec) {
		v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(vec.size());
		for (int i = 0; i < jsArr->Length(); i++) {
			jsArr->Set(i, ArrayConverterType<Converter, T, CastType>::wrap(vec.at(i)));
		}
		return jsArr;
	}
};

template <class Clazz, class T, class CastType = T>
class ObjectArrayOfArraysConverter : public AbstractConverter<ArrayOfArraysConverterType<InstanceConverterType<Clazz, CastType>, T, CastType>, std::vector<std::vector<CastType>>> {};

#endif