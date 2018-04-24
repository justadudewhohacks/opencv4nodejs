#include <macro-inferno.h>
#include "NativeNodeUtils.h"

#ifndef __FF_MACROS_H__
#define __FF_MACROS_H__

#define FF_NEW_INSTANCE(ctor) Nan::NewInstance(Nan::New(ctor)->GetFunction()).ToLocalChecked()

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

#define FF_GETTER_JSOBJ(clazz, name, value, unwrapper, ctor)	\
	NAN_GETTER(name) {																					\
		v8::Local<v8::Object> jsObj = FF_NEW_INSTANCE(ctor);			\
		unwrapper(jsObj) = FF_UNWRAP(info.This(), clazz)->value;	\
		info.GetReturnValue().Set(jsObj);													\
	}

#define FF_SET_JS_PROP(obj, prop, val) Nan::Set(obj, FF_NEW_STRING(#prop), val)

#define FF_SET_CV_CONSTANT(obj, cvConstant) \
	FF_SET_JS_PROP(obj, cvConstant, Nan::New<v8::Integer>(cvConstant));

#define FF_REQUIRE_INSTANCE(objCtor, obj, err)	\
	if (!FF_IS_INSTANCE(objCtor, obj)) {					\
			return Nan::ThrowError(err);							\
	}

#define FF_GET_UNPACK_UCHAR_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, uchar, ff_uint, ff_defaultValue)
#define FF_ARG_UNPACK_UCHAR_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_uint, ff_defaultValue)

/* unwrappers */

#define FF_UNWRAP(obj, clazz)	Nan::ObjectWrap::Unwrap<clazz>(obj)

#define FF_UNWRAP_MAT(obj) FF_UNWRAP(obj, Mat)
#define FF_UNWRAP_MAT_AND_GET(obj) FF_UNWRAP_MAT(obj)->mat

#define FF_UNWRAP_VEC2(obj) FF_UNWRAP(obj, Vec2)
#define FF_UNWRAP_VEC2_AND_GET(obj) FF_UNWRAP_VEC2(obj)->vec

#define FF_UNWRAP_VEC3(obj) FF_UNWRAP(obj, Vec3)
#define FF_UNWRAP_VEC3_AND_GET(obj) FF_UNWRAP_VEC3(obj)->vec

#define FF_UNWRAP_VEC4(obj) FF_UNWRAP(obj, Vec4)
#define FF_UNWRAP_VEC4_AND_GET(obj) FF_UNWRAP_VEC4(obj)->vec

#define FF_UNWRAP_PT2(obj) FF_UNWRAP(obj, Point2)
#define FF_UNWRAP_PT2_AND_GET(obj) FF_UNWRAP_PT2(obj)->pt

#define FF_UNWRAP_PT3(obj) FF_UNWRAP(obj, Point3)
#define FF_UNWRAP_PT3_AND_GET(obj) FF_UNWRAP_PT3(obj)->pt

#define FF_UNWRAP_SIZE(obj)	FF_UNWRAP(obj, Size)
#define FF_UNWRAP_SIZE_AND_GET(obj)	FF_UNWRAP_SIZE(obj)->size

#define FF_UNWRAP_CONTOUR(obj) FF_UNWRAP(obj, Contour)
#define FF_UNWRAP_CONTOUR_AND_GET(obj) FF_UNWRAP_CONTOUR(obj)->contour

#define FF_UNWRAP_RECT(obj) FF_UNWRAP(obj, Rect)
#define FF_UNWRAP_RECT_AND_GET(obj)	FF_UNWRAP_RECT(obj)->rect

#define FF_UNWRAP_ROTATEDRECT(obj) FF_UNWRAP(obj, RotatedRect)
#define FF_UNWRAP_ROTATEDRECT_AND_GET(obj) FF_UNWRAP_ROTATEDRECT(obj)->rect

#define FF_UNWRAP_TRAINDATA(obj) FF_UNWRAP(obj, TrainData)
#define FF_UNWRAP_TRAINDATA_AND_GET(obj) FF_UNWRAP_TRAINDATA(obj)->trainData

#define FF_UNWRAP_TERMCRITERA(obj) FF_UNWRAP(obj, TermCriteria)
#define FF_UNWRAP_TERMCRITERA_AND_GET(obj) FF_UNWRAP_TERMCRITERA(obj)->termCriteria

/* TODO: move this to macro-inferno */
#define FF_IS_FUNC(val) val->IsFunction()
#define FF_CAST_FUNC(val) val.As<v8::Function>()
struct FF_TYPE(FUNC, v8::Local<v8::Function>, FF_IS_FUNC, FF_CAST_FUNC);
static FF_FUNC_TYPE ff_func = FF_FUNC_TYPE();
#define FF_ARG_FUNC(argN, var) FF_ARG(argN, var, ff_func)

#define FF_ARG_IS_OBJECT(argN) FF_HAS_ARG(argN) && info[argN]->IsObject() && !info[argN]->IsArray() && !info[argN]->IsFunction()

/* for setters */
#define FF_REQUIRE_VALUE(ff_value, ff_type)													\
  if (!ff_type.checkType(ff_value)) {																\
    FF_THROW("expected value to be of type: " + ff_type.typeName);	\
  }

#define FF_SETTER(clazz, name, prop, ff_type)																\
	NAN_SETTER(name##Set) {																										\
		FF_METHOD_CONTEXT(#name);																								\
		FF_REQUIRE_VALUE(value, ff_type);																				\
		Nan::ObjectWrap::Unwrap<clazz>(info.This())->prop = ff_type.cast(value);\
	}

#define FF_SETTER_INT(clazz, name, prop) FF_SETTER(clazz, name, prop, ff_int)
#define FF_SETTER_UINT(clazz, name, prop) FF_SETTER(clazz, name, prop, ff_uint)
#define FF_SETTER_NUMBER(clazz, name, prop) FF_SETTER(clazz, name, prop, ff_number)
#define FF_SETTER_BOOL(clazz, name, prop) FF_SETTER(clazz, name, prop, ff_bool)

#define FF_SETTER_SIMPLE(clazz, name, prop, converter)  										\
	NAN_SETTER(name##Set) {																										\
		FF_METHOD_CONTEXT(#name);												      									\
		Nan::ObjectWrap::Unwrap<clazz>(info.This())->prop = converter::unwrap(	\
			value																																	\
		);																																			\
	}

#define FF_SETTER_COMPLEX(clazz, name, prop, type, converter) 	\
	NAN_SETTER(name##Set) {																				\
		FF_METHOD_CONTEXT(#name);												    				\
		type target;																								\
		converter::unwrap(&target, value);													\
		Nan::ObjectWrap::Unwrap<clazz>(info.This())->prop = target;	\
	}

#endif
