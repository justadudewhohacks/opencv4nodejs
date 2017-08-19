#include "matUtils.h"
#include <iostream>

#ifndef FF_MACROS_H_
#define FF_MACROS_H_

#define FF_V8STRING(s) \
	Nan::New(s).ToLocalChecked()

#define FF_NEW(ctor) \
	Nan::NewInstance(Nan::New(ctor)->GetFunction()).ToLocalChecked()

#define FF_CAST_ARRAY(val) \
	v8::Local<v8::Array>::Cast(val)

#define FF_CAST_OBJ(val) \
	Nan::To<v8::Object>(val).ToLocalChecked()

#define FF_JS_VAL_TO_STRING(s) \
	std::string(*Nan::Utf8String(s->ToString()))

#define FF_GETTER(clazz, name, value)	\
	NAN_GETTER(name) { info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<clazz>(info.This())->value); }

#define FF_SET_JS_PROP(obj, prop, val) \
	Nan::Set(obj, FF_V8STRING(#prop), val)

#define FF_HAS_JS_PROP(obj, prop) \
	Nan::HasOwnProperty(obj, FF_V8STRING(#prop)).FromJust()

/* unchecked js prop getters */

#define FF_GET_JSPROP(obj, prop) \
	Nan::Get(obj, FF_V8STRING(#prop)).ToLocalChecked()

#define FF_GET_JSPROP_NUMBER(obj, prop) \
	FF_GET_JSPROP(obj, prop)->NumberValue()

#define FF_GET_JSPROP_OBJECT(obj, prop) \
	FF_GET_JSPROP(obj, prop)->ToObject()

#define FF_GET_JSPROP_FLOAT(obj, prop) \
	(float)FF_GET_JSPROP_NUMBER(obj, prop)

#define FF_GET_JSPROP_DOUBLE(obj, prop) \
	(double)FF_GET_JSPROP_NUMBER(obj, prop)

#define FF_GET_JSPROP_INT(obj, prop) \
	(int)FF_GET_JSPROP(obj, prop)->IntegerValue()

#define FF_GET_JSPROP_UINT(obj, prop) \
	(uint)FF_GET_JSPROP(obj, prop)->Uint32Value()

#define FF_GET_JSPROP_STRING(obj, prop) \
	FF_JS_VAL_TO_STRING(FF_GET_JSPROP(obj, prop)->ToString())


/* checked js prop getters */

#define FF_GET_JSPROP_REQUIRED(obj, var, prop, castType)																	\
	if (!FF_HAS_JS_PROP(obj, prop)) {																												\
		return Nan::ThrowError(FF_V8STRING("Object has no property: " + std::string(#prop)));	\
	}																																												\
	var = FF_GET_JSPROP(obj, prop)->castType();																																										

#define FF_DESTRUCTURE_JSPROP_REQUIRED(obj, prop, castType)	\
	FF_GET_JSPROP_REQUIRED(obj, prop, prop, castType)

#define FF_GET_TYPECHECKED_JSPROP(obj, var, prop, assertType, castType)			\
	if (!FF_GET_JSPROP(obj, prop)->assertType()) {														\
		return Nan::ThrowError(FF_V8STRING(																			\
			"Invalid type for " + std::string(#prop) + " :"												\
			+ FF_GET_JSPROP_STRING(obj, prop)																			\
			+ ", expected: " + #assertType																				\
		));																																			\
	}																																					\
	var = FF_GET_JSPROP(obj, prop)->castType();															

#define FF_GET_TYPECHECKED_JSPROP_REQUIRED(obj, var, prop, assertType, castType)					\
	if (!FF_HAS_JS_PROP(obj, prop)) {																												\
		return Nan::ThrowError(FF_V8STRING("Object has no property: " + std::string(#prop)));	\
	}																																												\
	FF_GET_TYPECHECKED_JSPROP(obj, var, prop, assertType, castType)

#define FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(obj, prop, assertType, castType)	\
	FF_GET_TYPECHECKED_JSPROP_REQUIRED(obj, prop, prop, assertType, castType)

#define FF_GET_TYPECHECKED_JSPROP_IFDEF(obj, var, prop, assertType, castType)	\
	if (FF_HAS_JS_PROP(obj, prop)) {																						\
		FF_GET_TYPECHECKED_JSPROP(obj, var, prop, assertType, castType)						\
	}

#define FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(obj, prop, assertType, castType)	\
	FF_GET_TYPECHECKED_JSPROP_IFDEF(obj, prop, prop, assertType, castType)

#define FF_ASSERT_EQUALS(expected, have, what, atmsg)															\
	if (expected != have) {																													\
		return Nan::ThrowError(FF_V8STRING(std::string(what) + " mismatch, expected "	\
			+ std::to_string(expected) + ", have " + std::to_string(have) + atmsg));		\
	}

#define FF_TRY(work)																					\
	try {																												\
		work																											\
	} catch (std::exception &e) {																\
		return info.GetReturnValue().Set(Nan::Error(e.what()));		\
	} catch (...) {																							\
		return info.GetReturnValue().Set(Nan::Error("SEGFAULT"));	\
	}

#define FF_TRY_CATCH(work)					\
	try {															\
		work														\
	} catch (std::exception &e) {			\
		Nan::ThrowError(e.what());			\
	} catch (...) {										\
		Nan::ThrowError("SEGFAULT");		\
	}	

#define FF_REQUIRE_ARGS_OBJ(methodName)																												\
	if (!info[0]->IsObject()) {																																	\
		return Nan::ThrowError(FF_V8STRING(std::string(methodName) + " - args object required"));	\
	}																																														\
	v8::Local<v8::Object> args = info[0]->ToObject()

#define FF_IS_INSTANCE(ctor, obj)		\
	Nan::New(ctor)->HasInstance(obj)

#define FF_GET_JSOBJ_REQUIRED(args, var, prop, objCtor, unwrapper, clazz)	\
	do {																																		\
		v8::Local<v8::Object> obj;																						\
		FF_GET_JSPROP_REQUIRED(args, obj, prop, ToObject);										\
		FF_REQUIRE_INSTANCE(objCtor, obj, FF_V8STRING(std::string(#prop)			\
			+ " is not an instance of " + std::string(#clazz)));								\
		var = unwrapper(obj);																									\
	} while (0);																														\

#define FF_GET_JSARR_REQUIRED(args, var, prop)							\
	do {																											\
		v8::Local<v8::Value> val = FF_GET_JSPROP(args, prop);		\
		if (!val->IsArray()) {																	\
			return Nan::ThrowError(FF_V8STRING("expected "				\
				+ std::string(#prop) + "to be an array"));					\
		}																												\
		var = FF_CAST_ARRAY(val);																\
	} while (0);																												

#define FF_GET_JSARR_REQUIRED_WITH_LENGTH(args, var, prop, length)	\
	FF_GET_JSARR_REQUIRED(args, var, prop)														\
	if (!var->Length() == length) {																		\
		return Nan::ThrowError(FF_V8STRING("expected "									\
			+ std::string(#prop) + "to be an array of length "						\
			+ std::to_string(length)));																		\
	}


#define FF_DESTRUCTURE_JSOBJ_REQUIRED(args, prop, objCtor, unwrapper, clazz)	\
	FF_GET_JSOBJ_REQUIRED(args, prop, prop, objCtor, unwrapper, clazz)

#define FF_REQUIRE_INSTANCE(objCtor, obj, err)	\
	if (!FF_IS_INSTANCE(objCtor, obj)) {					\
			return Nan::ThrowError(err);							\
	}

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

#define FF_UNWRAP_SIZE(obj)	FF_UNWRAP(obj, Size)
#define FF_UNWRAP_SIZE_AND_GET(obj)	FF_UNWRAP_SIZE(obj)->size

#endif