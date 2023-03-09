#include "AbstractConverter.h"
#include "UnwrapperBase.h"
#include "utils.h"

#ifndef __FF_INSTANCE_CONVERTER_H__
#define __FF_INSTANCE_CONVERTER_H__

namespace FF {

	template <class TClass, class T>
	class InstanceConverterImpl : public UnwrapperBase<InstanceConverterImpl<TClass, T>, T> {
	public:
		typedef T Type;

		static std::string getTypeName() {
			return TClass::getClassName();
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return !jsVal->IsNull() && !jsVal->IsUndefined() && Nan::New(TClass::constructor)->HasInstance(jsVal);
		}

		static T unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return unwrapNanObjectWrap<TClass>(jsVal)->self;
		}

		static v8::Local<v8::Value> wrap(T val) {
			v8::Local<v8::Object> jsObj = FF::newInstance(Nan::New(TClass::constructor));
			unwrapNanObjectWrap<TClass>(jsObj)->setNativeObject(val);
			return jsObj;
		}
	};

}

#endif