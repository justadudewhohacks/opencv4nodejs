#include <nan.h>

#ifndef __FF_ARRAY_CONVERTER_H__
#define __FF_ARRAY_CONVERTER_H__

namespace FF {

	template <class ElementConverterImpl, class ElementCastType>
	class ArrayConverterImpl {
	public:
		typedef std::vector<ElementCastType> Type;

		static std::string getTypeName() {
			return std::string("array of ") + ElementConverterImpl::getTypeName();
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsArray();
		}

		static Type unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			Type vec;
			unwrap(&vec, jsVal);
			return vec;
		}

		static bool unwrap(Type* vec, v8::Local<v8::Value> jsVal) {
			if (!jsVal->IsArray()) {
				return true;
			}

			v8::Local<v8::Array> jsArr = v8::Local<v8::Array>::Cast(jsVal);
			for (int i = 0; i < (int)jsArr->Length(); i++) {
				if (!ElementConverterImpl::assertType(Nan::Get(jsArr, i).ToLocalChecked())) {
					Nan::ThrowError(
						Nan::New(
							std::string("expected array element at index ")
							+ std::to_string(i)
							+ std::string(" to be of type ")
							+ std::string(ElementConverterImpl::getTypeName())
						).ToLocalChecked()
					);
					return true;
				}

				ElementCastType obj = (ElementCastType)ElementConverterImpl::unwrapUnchecked(Nan::Get(jsArr, i).ToLocalChecked());
				vec->push_back(obj);
			}

			return false;
		}

		static v8::Local<v8::Value> wrap(Type vec) {
			v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(vec.size());
			for (int i = 0; i < (int)jsArr->Length(); i++) {
				Nan::Set(jsArr, i, ElementConverterImpl::wrap(vec.at(i)));
			}
			return jsArr;
		}
	};

}
#endif
