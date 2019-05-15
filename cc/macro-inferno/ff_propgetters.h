#include "ff_marshalling.h"

#ifndef __FF_PROPGETTERS_H__
#define __FF_PROPGETTERS_H__

/* js property getters */

#define FF_GET(ff_obj, ff_prop) Nan::Get(ff_obj, FF_NEW_STRING(ff_prop)).ToLocalChecked()

#define FF_REQUIRE_PROP(ff_obj, ff_prop)													\
	if (!FF_HAS(ff_obj, ff_prop)) {																	\
		FF_THROW("object has no property: " + std::string(ff_prop));	\
	}

#define FF_REQUIRE_PROP_TYPE(ff_obj, ff_prop, ff_ffType)																							\
	if (!ff_ffType.checkType(FF_GET(ff_obj, ff_prop))) {																								\
		FF_THROW("expected property: " + std::string(ff_prop) + " to be of type: " + ff_ffType.typeName);	\
	}

#define FF_REQUIRE_PROP_INSTANCE(ff_obj, ff_prop, ctor, clazz)																							\
	if (!FF_IS_INSTANCE(ctor, FF_GET(ff_obj, ff_prop))) {																											\
    FF_THROW("expected property: " + std::string(ff_prop) + " to be instance of: " + std::string(#clazz));	\
  }

/* get js prop, throw if undefined or invalid type */
#define FF_GET_REQUIRED(ff_obj, ff_var, ff_prop, ff_ffType)	\
	FF_REQUIRE_PROP(ff_obj, ff_prop)													\
	FF_REQUIRE_PROP_TYPE(ff_obj, ff_prop, ff_ffType)					\
	ff_var = ff_ffType.cast(FF_GET(ff_obj, ff_prop));

/* unpack ff_object, throw if undefined or not instance */
#define FF_GET_INSTANCE_REQUIRED(ff_obj, ff_var, ff_prop, ctor, unwrapper, clazz)	\
	FF_REQUIRE_PROP(ff_obj, ff_prop)																								\
	FF_REQUIRE_PROP_INSTANCE(ff_obj, ff_prop, ctor, clazz)													\
	ff_var = unwrapper(ff_obj);

/* get js prop if defined, throw if invalid type */
#define FF_GET_IFDEF(ff_obj, ff_var, ff_prop, ff_ffType, defaultValue)	\
	if (FF_HAS(ff_obj, ff_prop)) {																				\
		FF_REQUIRE_PROP_TYPE(ff_obj, ff_prop, ff_ffType)										\
	}																																			\
	ff_var = (FF_HAS(ff_obj, ff_prop) ? ff_ffType.cast(FF_GET(ff_obj, ff_prop)) : defaultValue);

/* unpack object if defined if not instance */
#define FF_GET_INSTANCE_IFDEF(ff_obj, ff_var, ff_prop, ctor, unwrapper, clazz, defaultValue)	\
	if (FF_HAS(ff_obj, ff_prop)) {																															\
		FF_REQUIRE_PROP_INSTANCE(ff_obj, ff_prop, ctor, clazz)																		\
	}																																														\
	ff_var = (FF_HAS(ff_obj, ff_prop) ? unwrapper(FF_GET(ff_obj, ff_prop)->ToObject(Nan::GetCurrentContext()).ToLocalChecked()) : defaultValue);

/* getters - native types */
#define FF_GET_BOOL_REQUIRED(ff_obj, ff_var, ff_prop) FF_GET_REQUIRED(ff_obj, ff_var, ff_prop, ff_bool)
#define FF_GET_NUMBER_REQUIRED(ff_obj, ff_var, ff_prop) FF_GET_REQUIRED(ff_obj, ff_var, ff_prop, ff_number)
#define FF_GET_UINT_REQUIRED(ff_obj, ff_var, ff_prop) FF_GET_REQUIRED(ff_obj, ff_var, ff_prop, ff_uint)
#define FF_GET_INT_REQUIRED(ff_obj, ff_var, ff_prop) FF_GET_REQUIRED(ff_obj, ff_var, ff_prop, ff_int)
#define FF_GET_STRING_REQUIRED(ff_obj, ff_var, ff_prop) FF_GET_REQUIRED(ff_obj, ff_var, ff_prop, ff_string)
#define FF_GET_ARRAY_REQUIRED(ff_obj, ff_var, ff_prop) FF_GET_REQUIRED(ff_obj, ff_var, ff_prop, ff_array_type)
#define FF_GET_OBJ_REQUIRED(ff_obj, ff_var, ff_prop) FF_GET_REQUIRED(ff_obj, ff_var, ff_prop, ff_obj_type)

#define FF_GET_BOOL_IFDEF(ff_obj, ff_var, ff_prop, defaultValue) FF_GET_IFDEF(ff_obj, ff_var, ff_prop, ff_bool, defaultValue)
#define FF_GET_NUMBER_IFDEF(ff_obj, ff_var, ff_prop, defaultValue) FF_GET_IFDEF(ff_obj, ff_var, ff_prop, ff_number, defaultValue)
#define FF_GET_UINT_IFDEF(ff_obj, ff_var, ff_prop, defaultValue) FF_GET_IFDEF(ff_obj, ff_var, ff_prop, ff_uint, defaultValue)
#define FF_GET_INT_IFDEF(ff_obj, ff_var, ff_prop, defaultValue) FF_GET_IFDEF(ff_obj, ff_var, ff_prop, ff_int, defaultValue)
#define FF_GET_STRING_IFDEF(ff_obj, ff_var, ff_prop, defaultValue) FF_GET_IFDEF(ff_obj, ff_var, ff_prop, ff_string, defaultValue)
#define FF_GET_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, defaultValue) FF_GET_IFDEF(ff_obj, ff_var, ff_prop, ff_array_type, defaultValue)
#define FF_GET_OBJ_IFDEF(ff_obj, ff_var, ff_prop, defaultValue) FF_GET_IFDEF(ff_obj, ff_var, ff_prop, ff_obj_type, defaultValue)

/* get and unpack array */
#define FF_GET_UNPACK_ARRAY(ff_obj, ff_var, ff_prop, ff_type, ff_ffType)	\
	std::vector<ff_type> ff_var;																						\
	FF_GET_UNPACK_ARRAY_TO(ff_obj, ff_var, ff_prop, ff_ffType)

#define FF_GET_UNPACK_ARRAY_TO(ff_obj, ff_var, ff_prop, ff_ffType)	\
	do {																															\
		FF_ARR ff_tmpArr;																								\
		FF_GET_REQUIRED(ff_obj, ff_tmpArr, ff_prop, ff_array_type)			\
		FF_UNPACK_ARRAY_TO(ff_var, ff_tmpArr, ff_ffType)								\
	} while (0);

#define FF_GET_UNPACK_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_ffType, ff_defaultValue) \
	if (FF_HAS(ff_obj, ff_prop)) {																													\
		FF_REQUIRE_PROP_TYPE(ff_obj, ff_prop, ff_array_type)																	\
		FF_GET_UNPACK_ARRAY_TO(ff_obj, ff_var, ff_prop, ff_ffType)														\
	}	else {																																								\
		ff_var = ff_defaultValue;																															\
	}

#define FF_GET_UNPACK_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, ff_type, ff_ffType, ff_defaultValue) \
	std::vector<ff_type> ff_var;																																	\
	FF_GET_UNPACK_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_ffType, ff_defaultValue)

#define FF_GET_UNPACK_BOOL_ARRAY(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY(ff_obj, ff_var, ff_prop, bool, ff_bool)
#define FF_GET_UNPACK_NUMBER_ARRAY(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY(ff_obj, ff_var, ff_prop, double, ff_number)
#define FF_GET_UNPACK_UINT_ARRAY(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY(ff_obj, ff_var, ff_prop, uint, ff_uint)
#define FF_GET_UNPACK_INT_ARRAY(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY(ff_obj, ff_var, ff_prop, int, ff_int)
#define FF_GET_UNPACK_STRING_ARRAY(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY(ff_obj, ff_var, ff_prop, std::string, ff_string)
#define FF_GET_UNPACK_ARRAY_ARRAY(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY(ff_obj, ff_var, ff_prop, FF_ARR, ff_array_type)
#define FF_GET_UNPACK_OBJECT_ARRAY(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY(ff_obj, ff_var, ff_prop, FF_OBJ, ff_obj_type)

#define FF_GET_UNPACK_BOOL_ARRAY_TO(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY_TO(ff_obj, ff_var, ff_prop, ff_bool)
#define FF_GET_UNPACK_NUMBER_ARRAY_TO(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY_TO(ff_obj, ff_var, ff_prop, ff_number)
#define FF_GET_UNPACK_UINT_ARRAY_TO(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY_TO(ff_obj, ff_var, ff_prop, ff_uint)
#define FF_GET_UNPACK_INT_ARRAY_TO(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY_TO(ff_obj, ff_var, ff_prop, ff_int)
#define FF_GET_UNPACK_STRING_ARRAY_TO(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY_TO(ff_obj, ff_var, ff_prop, ff_string)
#define FF_GET_UNPACK_ARRAY_ARRAY_TO(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY_TO(ff_obj, ff_var, ff_prop, ff_array_type)
#define FF_GET_UNPACK_OBJECT_ARRAY_TO(ff_obj, ff_var, ff_prop) FF_GET_UNPACK_ARRAY_TO(ff_obj, ff_var, ff_prop, ff_obj_type)

#define FF_GET_UNPACK_BOOL_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, bool, ff_bool, ff_defaultValue)
#define FF_GET_UNPACK_NUMBER_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, double, ff_number, ff_defaultValue)
#define FF_GET_UNPACK_UINT_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, uint, ff_uint, ff_defaultValue)
#define FF_GET_UNPACK_INT_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, int, ff_int, ff_defaultValue)
#define FF_GET_UNPACK_STRING_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, std::string, ff_string, ff_defaultValue)
#define FF_GET_UNPACK_ARRAY_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, FF_ARR, ff_array_type, ff_defaultValue)
#define FF_GET_UNPACK_OBJECT_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_IFDEF(ff_obj, ff_var, ff_prop, FF_OBJ, ff_obj_type, ff_defaultValue)

#define FF_GET_UNPACK_BOOL_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_bool, ff_defaultValue)
#define FF_GET_UNPACK_NUMBER_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_number, ff_defaultValue)
#define FF_GET_UNPACK_UINT_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_uint, ff_defaultValue)
#define FF_GET_UNPACK_INT_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_int, ff_defaultValue)
#define FF_GET_UNPACK_STRING_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_string, ff_defaultValue)
#define FF_GET_UNPACK_ARRAY_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_array_type, ff_defaultValue)
#define FF_GET_UNPACK_OBJECT_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_defaultValue) FF_GET_UNPACK_ARRAY_TO_IFDEF(ff_obj, ff_var, ff_prop, ff_obj_type, ff_defaultValue)

#endif