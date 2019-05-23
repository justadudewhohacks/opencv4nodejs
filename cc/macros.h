#include "NativeNodeUtils.h"

#ifndef __FF_MACROS_H__
#define __FF_MACROS_H__

typedef unsigned int uint;

namespace FF {
	static inline bool hasArg(Nan::NAN_METHOD_ARGS_TYPE info, int argN) {
		return argN < info.Length();
	}

	static inline bool isArgObject(Nan::NAN_METHOD_ARGS_TYPE info, int argN) {
		return FF::hasArg(info, argN) && info[argN]->IsObject() && !info[argN]->IsArray() && !info[argN]->IsFunction();
	}

	static inline v8::Local<v8::String> newString(std::string str) {
		return Nan::New(str).ToLocalChecked();
	}

	static inline bool hasOwnProperty(v8::Local<v8::Object> obj, char* prop) {
		return Nan::HasOwnProperty(obj, FF::newString(prop)).FromJust();
	}
}

/* TO BE REMOVED */
#define FF_CAST_OBJ(val) Nan::To<v8::Object>(val).ToLocalChecked()
#define FF_IS_ARRAY(val) val->IsArray()

#define FF_METHOD_CONTEXT(methodName) std::string ff_methodName = methodName;
#define FF_THROW(msg) return Nan::ThrowError(FF::newString(std::string(ff_methodName) + " - " + std::string(msg)));

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

#define FF_GETTER_JSOBJ(clazz, name, value, unwrapper, ctor)	\
	NAN_GETTER(name) {																					\
		v8::Local<v8::Object> jsObj = FF::newInstance(Nan::New(ctor));			\
		unwrapper(jsObj) = FF_UNWRAP(info.This(), clazz)->value;	\
		info.GetReturnValue().Set(jsObj);													\
	}

#define FF_SET_JS_PROP(obj, prop, val) Nan::Set(obj, FF::newString(#prop), val)

#define FF_SET_CV_CONSTANT(obj, cvConstant) \
	FF_SET_JS_PROP(obj, cvConstant, Nan::New<v8::Integer>(cvConstant));

#define FF_ASSERT_CONSTRUCT_CALL(ctor)																\
  if (!info.IsConstructCall()) {																			\
    return Nan::ThrowError(FF::newString(std::string(#ctor)						\
        + "::New - expect to be called with \"new\"")); 							\
  }

#define FF_SETTER(clazz, name, prop, ff_check_type, ff_cast_type, ff_type_name)	\
	NAN_SETTER(name##Set) {	\
		FF_METHOD_CONTEXT(#name); \
		if (!ff_check_type(value)) { \
			FF_THROW("expected value to be of type: " + std::string(ff_type_name));\
		} \
		Nan::ObjectWrap::Unwrap<clazz>(info.This())->prop = ff_cast_type(value); \
	}

#define FF_SETTER_INT(clazz, name, prop) FF_SETTER(clazz, name, prop, IntTypeConverter::assertType, IntConverter::unwrap, "INT")
#define FF_SETTER_UINT(clazz, name, prop) FF_SETTER(clazz, name, prop, UintTypeConverter::assertType, UintConverter::unwrap, "UINT")
#define FF_SETTER_NUMBER(clazz, name, prop) FF_SETTER(clazz, name, prop, NumberTypeConverter::assertType, DoubleConverter::unwrap, "NUMBER")
#define FF_SETTER_BOOL(clazz, name, prop) FF_SETTER(clazz, name, prop, BoolTypeConverter::assertType, BoolConverter::unwrap, "BOOL")
#define FF_SETTER_STRING(clazz, name, prop) FF_SETTER(clazz, name, prop, StringTypeConverter::assertType, StringConverter::unwrap, "STRING")

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
