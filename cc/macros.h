#include <macro-inferno.h>
#include <iostream>

#ifndef __FF_MACROS_H__
#define __FF_MACROS_H__

#define FF_NEW_INSTANCE(ctor) Nan::NewInstance(Nan::New(ctor)->GetFunction()).ToLocalChecked()

#define FF_GETTER(clazz, name, value)	\
	NAN_GETTER(name) { info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<clazz>(info.This())->value); }

#define FF_GETTER_JSOBJ(clazz, name, value, unwrapper, ctor)	\
	NAN_GETTER(name) {																					\
		v8::Local<v8::Object> jsObj = FF_NEW_INSTANCE(ctor);			\
		unwrapper(jsObj) = FF_UNWRAP(info.This(), clazz)->value;	\
		info.GetReturnValue().Set(jsObj);													\
	}

#define FF_SET_JS_PROP(obj, prop, val) Nan::Set(obj, FF_NEW_STRING(#prop), val)

/* unchecked js prop getters */

#define FF_GET_JSPROP(obj, prop) Nan::Get(obj, FF_NEW_STRING(#prop)).ToLocalChecked()
#define FF_GET_JSPROP_NUMBER(obj, prop) FF_GET_JSPROP(obj, prop)->NumberValue()
#define FF_GET_JSPROP_OBJECT(obj, prop) FF_GET_JSPROP(obj, prop)->ToObject()
#define FF_GET_JSPROP_FLOAT(obj, prop) (float)FF_GET_JSPROP_NUMBER(obj, prop)
#define FF_GET_JSPROP_DOUBLE(obj, prop) (double)FF_GET_JSPROP_NUMBER(obj, prop)
#define FF_GET_JSPROP_INT(obj, prop) (int)FF_GET_JSPROP(obj, prop)->IntegerValue()
#define FF_GET_JSPROP_UINT(obj, prop) (uint)FF_GET_JSPROP(obj, prop)->Uint32Value()
#define FF_GET_JSPROP_STRING(obj, prop) FF_CAST_STRING(FF_GET_JSPROP(obj, prop)->ToString())


/* checked js prop getters */

#define FF_GET_JSPROP_REQUIRED(obj, var, prop, castType)																	\
	if (!FF_HAS(obj, #prop)) {																												\
		return Nan::ThrowError(FF_NEW_STRING("Object has no property: " + std::string(#prop)));	\
	}																																												\
	var = FF_GET_JSPROP(obj, prop)->castType();

#define FF_DESTRUCTURE_JSPROP_REQUIRED(obj, prop, castType)	\
	FF_GET_JSPROP_REQUIRED(obj, prop, prop, castType)

#define FF_GET_TYPECHECKED_JSPROP(obj, var, prop, assertType, castType)			\
	if (!FF_GET_JSPROP(obj, prop)->assertType()) {														\
		return Nan::ThrowError(FF_NEW_STRING(																			\
			"Invalid type for " + std::string(#prop) + " :"												\
			+ FF_GET_JSPROP_STRING(obj, prop)																			\
			+ ", expected: " + #assertType																				\
		));																																			\
	}																																					\
	var = FF_GET_JSPROP(obj, prop)->castType();

#define FF_GET_TYPECHECKED_JSPROP_REQUIRED(obj, var, prop, assertType, castType)					\
	if (!FF_HAS(obj, #prop)) {																												\
		return Nan::ThrowError(FF_NEW_STRING("Object has no property: " + std::string(#prop)));	\
	}																																												\
	FF_GET_TYPECHECKED_JSPROP(obj, var, prop, assertType, castType)

#define FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(obj, prop, assertType, castType)	\
	FF_GET_TYPECHECKED_JSPROP_REQUIRED(obj, prop, prop, assertType, castType)

#define FF_GET_TYPECHECKED_JSPROP_IFDEF(obj, var, prop, assertType, castType)	\
	if (FF_HAS(obj, #prop)) {																						\
		FF_GET_TYPECHECKED_JSPROP(obj, var, prop, assertType, castType)						\
	}

#define FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(obj, prop, assertType, castType)	\
	FF_GET_TYPECHECKED_JSPROP_IFDEF(obj, prop, prop, assertType, castType)

#define FF_ASSERT_EQUALS(expected, have, what, atmsg)															\
	if (expected != have) {																													\
		return Nan::ThrowError(FF_NEW_STRING(std::string(what) + " mismatch, expected "	\
			+ std::to_string(expected) + ", have " + std::to_string(have) + atmsg));		\
	}

#define FF_REQUIRE_ARGS_OBJ(methodName)																												\
	if (!info[0]->IsObject()) {																																	\
		return Nan::ThrowError(FF_NEW_STRING(std::string(methodName) + " - args object required"));	\
	}																																														\
	v8::Local<v8::Object> args = info[0]->ToObject()

#define FF_GET_JSOBJ_REQUIRED(args, var, prop, objCtor, unwrapper, clazz)	\
	do {																																		\
		v8::Local<v8::Object> obj;																						\
		FF_GET_JSPROP_REQUIRED(args, obj, prop, ToObject);										\
		FF_REQUIRE_INSTANCE(objCtor, obj, FF_NEW_STRING(std::string(#prop)			\
			+ " is not an instance of " + std::string(#clazz)));								\
		var = unwrapper(obj);																									\
	} while (0);																														\

#define FF_GET_JSOBJ_IFDEF(obj, var, prop, objCtor, unwrapper, clazz)	\
	if (FF_HAS(obj, #prop)) {																			\
		FF_GET_JSOBJ_REQUIRED(obj, var, prop, objCtor, unwrapper, clazz)		\
	}

#define FF_DESTRUCTURE_JSOBJ_IFDEF(obj, prop, objCtor, unwrapper, clazz)	\
	if (FF_HAS(obj, #prop)) {																				\
		FF_GET_JSOBJ_REQUIRED(obj, prop, prop, objCtor, unwrapper, clazz)		\
	}

#define FF_GET_JSARR_REQUIRED_WITH_LENGTH(args, var, prop, length)	\
	FF_GET_ARRAY_REQUIRED(args, var, #prop)														\
	if (!var->Length() == length) {																		\
		return Nan::ThrowError(FF_NEW_STRING("expected "								\
			+ std::string(#prop) + "to be an array of length "						\
			+ std::to_string(length)));																		\
	}


#define FF_DESTRUCTURE_JSOBJ_REQUIRED(args, prop, objCtor, unwrapper, clazz)	\
	FF_GET_JSOBJ_REQUIRED(args, prop, prop, objCtor, unwrapper, clazz)

#define FF_REQUIRE_INSTANCE(objCtor, obj, err)	\
	if (!FF_IS_INSTANCE(objCtor, obj)) {					\
			return Nan::ThrowError(err);							\
	}

#define FF_UNPACK_JSOBJ_REQUIRED(obj, var, objCtor, err)	\
	FF_GET_JSPROP_REQUIRED(args, obj, prop, ToObject);			\
	FF_REQUIRE_INSTANCE(objCtor, obj, FF_NEW_STRING(err);		\
	var = unwrapper(obj);

#define FF_GET_UNPACK_UCHAR_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, uchar, ff_uint, ff_defaultValue)
#define FF_ARG_UNPACK_UCHAR_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_uint, ff_defaultValue)

#define FF_ARG_UNPACK_FLOAT_ARRAY(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY(ff_argN, ff_var, float, ff_number);
#define FF_GET_UNPACK_FLOAT_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, float, ff_number, ff_defaultValue)
#define FF_ARG_UNPACK_FLOAT_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_number, ff_defaultValue)

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

#define FF_UNWRAP_PARAMGRID(obj) FF_UNWRAP(obj, ParamGrid)
#define FF_UNWRAP_PARAMGRID_AND_GET(obj) FF_UNWRAP_PARAMGRID(obj)->paramGrid

#define FF_UNWRAP_TERMCRITERA(obj) FF_UNWRAP(obj, TermCriteria)
#define FF_UNWRAP_TERMCRITERA_AND_GET(obj) FF_UNWRAP_TERMCRITERA(obj)->termCriteria


namespace FF {
	template<typename toType, typename type>
	static inline v8::Local<v8::Array> stdVecToJSArray(std::vector<type> vec) {
		v8::Local<v8::Array> jsArray = Nan::New<v8::Array>(vec.size());
		for (int i = 0; i < jsArray->Length(); i++) {
			jsArray->Set(i, Nan::New((toType)vec.at(i)));
		}
		return jsArray;
	}
}

#endif