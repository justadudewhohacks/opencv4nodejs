#include "ff_marshalling.h"

#ifndef __FF_ARGS_H__
#define __FF_ARGS_H__

/* argument checking and casting */

#define FF_HAS_ARG(ff_argN) ( ff_argN < info.Length() )

#define FF_REQUIRE_ARG_TYPE(ff_argN, ff_type, orThrow)																						\
  if (orThrow || !ff_type.checkType(info[ff_argN])) {																						\
    FF_THROW("expected arg " + std::to_string(ff_argN) + " to be of type: " + ff_type.typeName);	\
  }

#define FF_ARG(ff_argN, ff_var, ff_type)											\
  FF_REQUIRE_ARG_TYPE(ff_argN, ff_type, !FF_HAS_ARG(ff_argN))	\
  ff_var = ff_type.cast(info[ff_argN]);

#define FF_ARG_IFDEF(ff_argN, ff_var, ff_type, ff_defaultValue)								\
  if(FF_HAS_ARG(ff_argN)) { FF_REQUIRE_ARG_TYPE(ff_argN, ff_type, false) }	\
  ff_var = (!FF_HAS_ARG(ff_argN) ? ff_defaultValue : ff_type.cast(info[ff_argN]));

#define FF_ARG_INSTANCE(ff_argN, ff_var, ctor, unwrapper)																									\
  if (!FF_HAS_ARG(ff_argN) || !FF_IS_INSTANCE(ctor, info[ff_argN])) {																			\
    FF_THROW("expected arg " + std::to_string(ff_argN) + " to be instance of: " + std::string(#ctor));	\
  }																																																	\
  ff_var = unwrapper(info[ff_argN]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());

#define FF_ARG_INSTANCE_IFDEF(ff_argN, ff_var, ctor, unwrapper, ff_defaultValue)	\
  ff_var = (!FF_HAS_ARG(ff_argN) || !FF_IS_INSTANCE(ctor, info[ff_argN]) ? ff_defaultValue : unwrapper(info[ff_argN]->ToObject(Nan::GetCurrentContext()).ToLocalChecked()));

/* aliases */
#define FF_ARG_BOOL(ff_argN, ff_var) FF_ARG(ff_argN, ff_var, ff_bool)
#define FF_ARG_NUMBER(ff_argN, ff_var) FF_ARG(ff_argN, ff_var, ff_number)
#define FF_ARG_UINT(ff_argN, ff_var) FF_ARG(ff_argN, ff_var, ff_uint)
#define FF_ARG_INT(ff_argN, ff_var) FF_ARG(ff_argN, ff_var, ff_int)
#define FF_ARG_STRING(ff_argN, ff_var) FF_ARG(ff_argN, ff_var, ff_string)
#define FF_ARG_ARRAY(ff_argN, ff_var) FF_ARG(ff_argN, ff_var, ff_array_type)
#define FF_ARG_OBJ(ff_argN, ff_var) FF_ARG(ff_argN, ff_var, ff_obj_type)

#define FF_ARG_BOOL_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_IFDEF(ff_argN, ff_var, ff_bool, ff_defaultValue)
#define FF_ARG_NUMBER_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_IFDEF(ff_argN, ff_var, ff_number, ff_defaultValue)
#define FF_ARG_UINT_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_IFDEF(ff_argN, ff_var, ff_uint, ff_defaultValue)
#define FF_ARG_INT_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_IFDEF(ff_argN, ff_var, ff_int, ff_defaultValue)
#define FF_ARG_STRING_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_IFDEF(ff_argN, ff_var, ff_string, ff_defaultValue)
#define FF_ARG_ARRAY_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_IFDEF(ff_argN, ff_var, ff_array_type, ff_defaultValue)
#define FF_ARG_OBJ_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_IFDEF(ff_argN, ff_var, ff_obj_type, ff_defaultValue)

/* unpack array args */
#define FF_ARG_UNPACK_ARRAY_TO(ff_argN, vec, ffType)	\
	do {																								\
		FF_ARR ff_tmpArr;																	\
		FF_ARG_ARRAY(ff_argN, ff_tmpArr)									\
		FF_UNPACK_ARRAY_TO(vec, ff_tmpArr, ffType)				\
	} while (0);

#define FF_ARG_UNPACK_ARRAY(ff_argN, ff_var, type, ffType)	\
	std::vector<type> ff_var;																	\
	FF_ARG_UNPACK_ARRAY_TO(ff_argN, ff_var, ffType)

#define FF_ARG_UNPACK_ARRAY_TO_IFDEF(ff_argN, ff_var, ffType, ff_defaultValue)	\
	if(FF_HAS_ARG(ff_argN)) {																											\
		FF_REQUIRE_ARG_TYPE(ff_argN, ff_array_type, false)													\
		FF_ARG_UNPACK_ARRAY_TO(ff_argN, ff_var, ffType)															\
	}	else {																																			\
		ff_var = ff_defaultValue;																										\
	}

#define FF_ARG_UNPACK_ARRAY_IFDEF(ff_argN, ff_var, type, ffType, ff_defaultValue)		\
	std::vector<type> ff_var;																													\
	FF_ARG_UNPACK_ARRAY_TO_IFDEF(ff_argN, ff_var, ffType, ff_defaultValue)

#define FF_ARG_UNPACK_BOOL_ARRAY(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY(ff_argN, ff_var, bool, ff_bool)
#define FF_ARG_UNPACK_NUMBER_ARRAY(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY(ff_argN, ff_var, double, ff_number)
#define FF_ARG_UNPACK_UINT_ARRAY(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY(ff_argN, ff_var, uint, ff_uint)
#define FF_ARG_UNPACK_INT_ARRAY(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY(ff_argN, ff_var, int, ff_int)
#define FF_ARG_UNPACK_STRING_ARRAY(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY(ff_argN, ff_var, std::string, ff_string)
#define FF_ARG_UNPACK_ARRAY_ARRAY(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY(ff_argN, ff_var, FF_ARR, ff_array_type)
#define FF_ARG_UNPACK_OBJECT_ARRAY(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY(ff_argN, ff_var, FF_OBJ, ff_obj_type)

#define FF_ARG_UNPACK_BOOL_ARRAY_TO(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY_TO(ff_argN, ff_var, ff_bool)
#define FF_ARG_UNPACK_NUMBER_ARRAY_TO(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY_TO(ff_argN, ff_var, ff_number)
#define FF_ARG_UNPACK_UINT_ARRAY_TO(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY_TO(ff_argN, ff_var, ff_uint)
#define FF_ARG_UNPACK_INT_ARRAY_TO(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY_TO(ff_argN, ff_var, ff_int)
#define FF_ARG_UNPACK_STRING_ARRAY_TO(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY_TO(ff_argN, ff_var, ff_string)
#define FF_ARG_UNPACK_ARRAY_ARRAY_TO(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY_TO(ff_argN, ff_var, ff_array_type)
#define FF_ARG_UNPACK_OBJECT_ARRAY_TO(ff_argN, ff_var) FF_ARG_UNPACK_ARRAY_TO(ff_argN, ff_var, ff_obj_type)

#define FF_ARG_UNPACK_BOOL_ARRAY_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_IFDEF(ff_argN, ff_var, bool, ff_bool, ff_defaultValue)
#define FF_ARG_UNPACK_NUMBER_ARRAY_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_IFDEF(ff_argN, ff_var, double, ff_number, ff_defaultValue)
#define FF_ARG_UNPACK_UINT_ARRAY_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_IFDEF(ff_argN, ff_var, uint, ff_uint, ff_defaultValue)
#define FF_ARG_UNPACK_INT_ARRAY_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_IFDEF(ff_argN, ff_var, int, ff_int, ff_defaultValue)
#define FF_ARG_UNPACK_STRING_ARRAY_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_IFDEF(ff_argN, ff_var, std::string, ff_string, ff_defaultValue)
#define FF_ARG_UNPACK_ARRAY_ARRAY_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_IFDEF(ff_argN, ff_var, FF_ARR, ff_array_type, ff_defaultValue)
#define FF_ARG_UNPACK_OBJECT_ARRAY_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_IFDEF(ff_argN, ff_var, FF_OBJ, ff_obj_type, ff_defaultValue)

#define FF_ARG_UNPACK_BOOL_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_bool, ff_defaultValue)
#define FF_ARG_UNPACK_NUMBER_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_number, ff_defaultValue)
#define FF_ARG_UNPACK_UINT_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_uint, ff_defaultValue)
#define FF_ARG_UNPACK_INT_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_int, ff_defaultValue)
#define FF_ARG_UNPACK_STRING_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_string, ff_defaultValue)
#define FF_ARG_UNPACK_ARRAY_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_array_type, ff_defaultValue)
#define FF_ARG_UNPACK_OBJECT_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_defaultValue) FF_ARG_UNPACK_ARRAY_TO_IFDEF(ff_argN, ff_var, ff_obj_type, ff_defaultValue)

#endif