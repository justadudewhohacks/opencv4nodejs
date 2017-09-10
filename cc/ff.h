#include <nan.h>

#ifndef FF_FF_H_
#define FF_FF_H_

#define FF_VAL v8::Local<v8::Value>
#define FF_OBJ v8::Local<v8::Object>
#define FF_ARR v8::Local<v8::Array>
#define FF_NEW_ARR Nan::New<v8::Array>
#define FF_NEW_OBJ Nan::New<v8::Object>

#define FF_TO_STRING(s) std::string(*Nan::Utf8String(s->ToString()))

#define FF_THROW(msg) return Nan::ThrowError(FF_V8STRING(std::string(ff_methodName) + " - " + std::string(msg)));

#define FF_METHOD_CONTEXT(methodName) std::string ff_methodName = methodName;			

/* argument checking and casting */

#define FF_REQUIRE_ARG_TYPE(argN, typeName, assertType, orThrow)																		\
  if (orThrow || !info[argN]->assertType()) {																												\
    FF_THROW("expected arg " + std::to_string(argN) + " to be of type: " + std::string(typeName));	\
  }

#define FF_HAS_ARG(argN) ( argN < info.Length() )

#define FF_ARG(argN, var, type, assertType, castType)							\
  FF_REQUIRE_ARG_TYPE(argN, #type, assertType, !FF_HAS_ARG(argN))	\
  var = info[argN]->castType();

#define FF_ARG_IFDEF(argN, var, type, assertType, castType, defaultValue)	\
  FF_REQUIRE_ARG_TYPE(argN, #type, assertType, false)											\
  var = (!FF_HAS_ARG(argN) ? defaultValue : info[argN]->castType());

#define FF_ARG_OBJ(argN, var, ctor, unwrapper)																											\
  if (!FF_HAS_ARG(argN) || !FF_IS_INSTANCE(ctor, info[argN])) {																			\
    FF_THROW("expected arg " + std::to_string(argN) + " to be instance of: " + std::string(#ctor));	\
  }																																																	\
  var = unwrapper(info[argN]->ToObject());

#define FF_ARG_OBJ_IFDEF(argN, var, ctor, unwrapper, defaultValue)	\
  var = (!FF_HAS_ARG(argN) || !FF_IS_INSTANCE(ctor, info[argN]) ? defaultValue : unwrapper(info[argN]->ToObject()));

/* arguments - native types */

#define FF_ARG_UINT(argN, var) FF_ARG(argN, var, unsigned int, IsUint32, Uint32Value)
#define FF_ARG_INT(argN, var) FF_ARG(argN, var, int, IsInt32, Int32Value)
#define FF_ARG_BOOL(argN, var) FF_ARG(argN, var, bool, IsBoolean, BooleanValue)
#define FF_ARG_NUMBER(argN, var) FF_ARG(argN, var, double, IsNumber, NumberValue)
#define FF_ARG_STRING(argN, var) \
  FF_REQUIRE_ARG_TYPE(argN, "string", IsString, !FF_HAS_ARG(argN)) \
  std::string var = FF_TO_STRING(info[argN]);

#define FF_ARG_UINT_IFDEF(argN, var, defaultValue) FF_ARG_IFDEF(argN, var, unsigned int, IsUint32, Uint32Value, defaultValue)
#define FF_ARG_INT_IFDEF(argN, var, defaultValue) FF_ARG_IFDEF(argN, var, int, IsInt32, Int32Value, defaultValue)
#define FF_ARG_BOOL_IFDEF(argN, var, defaultValue) FF_ARG_IFDEF(argN, var, bool, IsBoolean, BooleanValue, defaultValue)
#define FF_ARG_NUMBER_IFDEF(argN, var, defaultValue) FF_ARG_IFDEF(argN, var, double, IsNumber, NumberValue, defaultValue)
#define FF_ARG_STRING_IFDEF(argN, var) \
  FF_REQUIRE_ARG_TYPE(argN, "string", IsString, false) \
  std::string var = FF_TO_STRING(info[argN]);

/* js property getters */
// TODO replace old ones

#define FF_HAS(obj, prop) Nan::HasOwnProperty(obj, FF_V8STRING(prop)).FromJust()
#define FF_IS_INSTANCE(ctor, obj) Nan::New(ctor)->HasInstance(obj)

#define FF_REQUIRE_PROP(obj, prop)														\
	if (!FF_HAS(obj, prop)) {																		\
		FF_THROW("object has no property: " + std::string(prop)); \
	}

#define FF_REQUIRE_PROP_TYPE(obj, prop, type, assertType)																					\
	if (!FF_GET(obj, prop)->assertType()) {																													\
		FF_THROW("expected property: " + std::string(prop) + " to be of type: " + std::string(#type));\
	}			

#define FF_REQUIRE_PROP_INSTANCE(obj, prop, ctor, clazz)																								\
	if (!FF_IS_INSTANCE(ctor, FF_GET(obj, prop))) {																												\
    FF_THROW("expected property: " + std::string(prop) + " to be instance of: " + std::string(#clazz));	\
  }

#define FF_GET(obj, prop) Nan::Get(obj, FF_V8STRING(prop)).ToLocalChecked()

/* get js prop, throw if undefined or invalid type */
#define FF_GET_REQUIRED(obj, var, prop, type, assertType, castType)	\
	FF_REQUIRE_PROP(obj, prop)																				\
	FF_REQUIRE_PROP_TYPE(obj, prop, type, assertType)									\
	var = FF_GET(obj, prop)->castType();

/* unpack object, throw if undefined or not instance */
#define FF_GET_OBJ_REQUIRED(obj, var, prop, ctor, unwrapper, clazz)	\
	FF_REQUIRE_PROP(obj, prop)																				\
	FF_REQUIRE_PROP_INSTANCE(obj, prop, ctor, clazz)									\
	var = unwrapper(obj);

/* get js prop if defined, throw if invalid type */
#define FF_GET_IFDEF(obj, var, prop, type, assertType, castType, defaultValue)	\
	if (FF_HAS(obj, prop)) {																											\
		FF_REQUIRE_PROP_TYPE(obj, prop, type, assertType)														\
	}																																							\
	var = (FF_HAS(obj, prop) ? FF_GET(obj, prop)->castType() : defaultValue);

/* unpack object if defined if not instance */
#define FF_GET_OBJ_IFDEF(obj, var, prop, ctor, unwrapper, clazz, defaultValue)	\
	if (FF_HAS(obj, prop)) {																											\
		FF_REQUIRE_PROP_INSTANCE(obj, prop, ctor, clazz)														\
	}																																							\
	var = (FF_HAS(obj, prop) ? unwrapper(FF_GET(obj, prop)->ToObject()) : defaultValue);

/* getters - native types */
#define FF_GET_UINT_REQUIRED(args, var, prop) FF_GET_REQUIRED(args, var, prop, unsigned int, IsUint32, Uint32Value)
#define FF_GET_INT_REQUIRED(args, var, prop) FF_GET_REQUIRED(args, var, prop, int, IsInt32, Int32Value)
#define FF_GET_BOOL_REQUIRED(args, var, prop) FF_GET_REQUIRED(args, var, prop, bool, IsBoolean, BooleanValue)
#define FF_GET_NUMBER_REQUIRED(args, var, prop) FF_GET_REQUIRED(args, var, prop, double, IsNumber, NumberValue)

#define FF_GET_UINT_IFDEF(args, var, prop, defaultValue) FF_GET_IFDEF(args, var, prop, unsigned int, IsUint32, Uint32Value, defaultValue)
#define FF_GET_INT_IFDEF(args, var, prop, defaultValue) FF_GET_IFDEF(args, var, prop, int, IsInt32, Int32Value, defaultValue)
#define FF_GET_BOOL_IFDEF(args, var, prop, defaultValue) FF_GET_IFDEF(args, var, prop, bool, IsBoolean, BooleanValue, defaultValue)
#define FF_GET_NUMBER_IFDEF(args, var, prop, defaultValue) FF_GET_IFDEF(args, var, prop, double, IsNumber, NumberValue, defaultValue)

#endif