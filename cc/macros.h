#include "NativeNodeUtils.h"

#ifndef __FF_MACROS_H__
#define __FF_MACROS_H__

/* TO BE REMOVED */
#define FF_CAST_OBJ(val) Nan::To<v8::Object>(val).ToLocalChecked()
#define FF_IS_ARRAY(val) val->IsArray()

#define FF_METHOD_CONTEXT(methodName) std::string ff_methodName = methodName;
#define FF_THROW(msg) return Nan::ThrowError(FF::newString(std::string(ff_methodName) + " - " + std::string(msg)));

/* ------------- */

#define FF_GETTER(clazz, name, prop)	\
	NAN_GETTER(name) { info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<clazz>(info.This())->prop); }

#define FF_GETTER_SIMPLE(clazz, name, prop, converter)  \
	NAN_GETTER(name) { 																		\
		v8::Local<v8::Value> jsValue = converter::wrap(			\
			Nan::ObjectWrap::Unwrap<clazz>(info.This())->prop	\
		);																									\
		info.GetReturnValue().Set(jsValue);									\
	}

#define FF_GETTER_COMPLEX(clazz, name, prop, converter) FF_GETTER_SIMPLE(clazz, name, prop, converter)

#define FF_SET_JS_PROP(obj, prop, val) Nan::Set(obj, FF::newString(#prop), val)

#define FF_SET_CV_CONSTANT(obj, cvConstant) \
	FF_SET_JS_PROP(obj, cvConstant, Nan::New<v8::Integer>(cvConstant));

#define FF_ASSERT_CONSTRUCT_CALL(ctor)																\
  if (!info.IsConstructCall()) {																			\
    return Nan::ThrowError(FF::newString(std::string(#ctor)						\
        + "::New - expect to be called with \"new\"")); 							\
  }

#define FF_SETTER(clazz, name, prop, ff_converter, ff_type)	\
	NAN_SETTER(name##Set) {	\
		FF::TryCatch tryCatch; \
		ff_type val; \
		if (ff_converter::unwrapTo(&val, value)) { \
			return tryCatch.throwNew(tryCatch.formatCatchedError(#name)); \
		} \
		Nan::ObjectWrap::Unwrap<clazz>(info.This())->prop = val; \
	}

#define FF_SETTER_INT(clazz, name, prop) FF_SETTER(clazz, name, prop, FF::IntConverter, int)
#define FF_SETTER_UINT(clazz, name, prop) FF_SETTER(clazz, name, prop, FF::UintConverter, uint)
#define FF_SETTER_NUMBER(clazz, name, prop) FF_SETTER(clazz, name, prop, FF::DoubleConverter, double)
#define FF_SETTER_BOOL(clazz, name, prop) FF_SETTER(clazz, name, prop, FF::BoolConverter, bool)
#define FF_SETTER_STRING(clazz, name, prop) FF_SETTER(clazz, name, prop, FF::StringConverter, std::string)

#define FF_SETTER_SIMPLE(clazz, name, prop, converter)  										\
	NAN_SETTER(name##Set) {																										\
		FF_METHOD_CONTEXT(#name);												      									\
		Nan::ObjectWrap::Unwrap<clazz>(info.This())->prop = converter::unwrapUnchecked(	\
			value																																	\
		);																																			\
	}

#define FF_SETTER_COMPLEX(clazz, name, prop, type, converter) 	\
	NAN_SETTER(name##Set) {																				\
		FF_METHOD_CONTEXT(#name);												    				\
		type target;																								\
		converter::unwrapTo(&target, value);													\
		Nan::ObjectWrap::Unwrap<clazz>(info.This())->prop = target;	\
	}

#endif
