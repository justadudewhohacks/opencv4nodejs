#include "ArrayConverter.h"

#ifndef __FF_ARRAY_OF_ARRAYS_CONVERTER_H__
#define __FF_ARRAY_OF_ARRAYS_CONVERTER_H__

namespace FF {

	template <class ElementConverterImpl, class ElementCastType>
	class ArrayOfArraysConverterImpl : private ArrayConverterImpl<ElementConverterImpl, ElementCastType> {
	public:
		typedef std::vector<std::vector<ElementCastType>> Type;
		typedef ArrayConverterImpl<ElementConverterImpl, ElementCastType> super;

		static std::string getTypeName() {
			return std::string("array of arrays of ") + ElementConverterImpl::getTypeName();
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsArray();
		}

		static Type unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			Type vecOfVecs;
			unwrap(&vecOfVecs, jsVal);
			return vecOfVecs;
		}

		static bool unwrap(Type* vecOfVecs, v8::Local<v8::Value> jsVal) {
			if (!jsVal->IsArray()) {
				return true;
			}

			v8::Local<v8::Array> jsArr = v8::Local<v8::Array>::Cast(jsVal);
			for (uint i = 0; i < jsArr->Length(); i++) {
				std::vector<ElementCastType> vec;
				Nan::TryCatch tryCatch;
				if (super::unwrap(&vec, Nan::Get(jsArr, i).ToLocalChecked())) {
					tryCatch.ReThrow();
					return true;
				}
				vecOfVecs->push_back(vec);
			}
			return false;
		}

		static v8::Local<v8::Value> wrap(Type vec) {
			v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(vec.size());
			for (uint i = 0; i < jsArr->Length(); i++) {
				Nan::Set(jsArr, i, super::wrap(vec.at(i)));
			}
			return jsArr;
		}
	};

}

#endif
