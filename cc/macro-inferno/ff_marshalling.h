#include "ff.h"

#ifndef __FF_MARSHALLING_H__
#define __FF_MARSHALLING_H__

#define FF_TYPE(ff_name, ff_type, ff_assertType, ff_castType)	\
	FF_##ff_name##_TYPE {																				\
		bool checkType(FF_VAL val) {															\
			return ff_assertType(val);															\
		}																													\
		ff_type cast(FF_VAL val) {																\
			return ff_castType(val);																\
		}																													\
		std::string typeName = std::string(#ff_name);							\
	}

struct FF_TYPE(BOOL, bool, FF_IS_BOOL, FF_CAST_BOOL);
struct FF_TYPE(NUMBER, double, FF_IS_NUMBER, FF_CAST_NUMBER);
struct FF_TYPE(UINT, uint, FF_IS_UINT, FF_CAST_UINT);
struct FF_TYPE(INT, int, FF_IS_INT, FF_CAST_INT);
struct FF_TYPE(STRING, std::string, FF_IS_STRING, FF_CAST_STRING);
struct FF_TYPE(ARRAY, FF_ARR, FF_IS_ARRAY, FF_CAST_ARRAY);
struct FF_TYPE(OBJECT, FF_OBJ, FF_IS_OBJ, FF_CAST_OBJ);

static FF_BOOL_TYPE ff_bool = FF_BOOL_TYPE();
static FF_NUMBER_TYPE ff_number = FF_NUMBER_TYPE();
static FF_UINT_TYPE ff_uint = FF_UINT_TYPE();
static FF_INT_TYPE ff_int = FF_INT_TYPE();
static FF_STRING_TYPE ff_string = FF_STRING_TYPE();
static FF_ARRAY_TYPE ff_array_type = FF_ARRAY_TYPE();
static FF_OBJECT_TYPE ff_obj_type = FF_OBJECT_TYPE();

#define FF_UNPACK_ARRAY(ff_var, ff_arr, ff_type, ffType)	\
	std::vector<ff_type> ff_var;														\
	FF_UNPACK_ARRAY_TO(ff_var, ff_arr, ffType);

#define FF_UNPACK_ARRAY_TO(ff_vec, ff_arr, ffType)																																						\
	for (uint i = 0; i < ff_arr->Length(); i++) {																																								\
		FF_VAL ff_val = ff_arr->Get(i);																																														\
		if (!ffType.checkType(ff_val)) {																																													\
			FF_THROW("expected array element to be of type: " + std::string(ffType.typeName) + ", at index: " + std::to_string(i));	\
		}																																																													\
		ff_vec.push_back(ffType.cast(ff_val));																																										\
	}

#define FF_PACK_ARRAY_(ff_var, ff_vec, create)	\
	FF_ARR ff_var = FF_NEW_ARRAY(ff_vec.size());	\
	for (unsigned long i = 0; i < ff_vec.size(); i++) {			\
		ff_var->Set(i, create(ff_vec.at(i)));				\
	}

#define FF_UNPACK_UINT_ARRAY(ff_var, ff_arr) FF_UNPACK_ARRAY(ff_var, ff_arr, uint, ff_uint)
#define FF_UNPACK_INT_ARRAY(ff_var, ff_arr) FF_UNPACK_ARRAY(ff_var, ff_arr, int, ff_int)
#define FF_UNPACK_BOOL_ARRAY(ff_var, ff_arr) FF_UNPACK_ARRAY(ff_var, ff_arr, bool, ff_bool)
#define FF_UNPACK_NUMBER_ARRAY(ff_var, ff_arr) FF_UNPACK_ARRAY(ff_var, ff_arr, double, ff_number)
#define FF_UNPACK_STRING_ARRAY(ff_var, ff_arr) FF_UNPACK_ARRAY(ff_var, ff_arr, std::string, ff_string)

#define FF_UNPACK_UINT_ARRAY_TO(ff_vec, ff_arr) FF_UNPACK_ARRAY_TO(ff_vec, ff_arr, ff_uint)
#define FF_UNPACK_INT_ARRAY_TO(ff_vec, ff_arr) FF_UNPACK_ARRAY_TO(ff_vec, ff_arr, ff_int)
#define FF_UNPACK_BOOL_ARRAY_TO(ff_vec, ff_arr) FF_UNPACK_ARRAY_TO(ff_vec, ff_arr, ff_bool)
#define FF_UNPACK_NUMBER_ARRAY_TO(ff_vec, ff_arr) FF_UNPACK_ARRAY_TO(ff_vec, ff_arr, ff_number)
#define FF_UNPACK_STRING_ARRAY_TO(ff_vec, ff_arr) FF_UNPACK_ARRAY_TO(ff_vec, ff_arr, ff_string)

#define FF_IDENTITY_FUNC(arg) arg
#define FF_PACK_ARRAY(ff_var, ff_vec) FF_PACK_ARRAY_(ff_var, ff_vec, Nan::New)
#define FF_PACK_STRING_ARRAY(ff_var, ff_vec) FF_PACK_ARRAY_(ff_var, ff_vec, FF_NEW_STRING)
#define FF_PACK_ARRAY_ARRAY(ff_var, ff_vec) FF_PACK_ARRAY_(ff_var, ff_vec, FF_IDENTITY_FUNC)
#define FF_PACK_OBJ_ARRAY(ff_var, ff_vec) FF_PACK_ARRAY_(ff_var, ff_vec, FF_IDENTITY_FUNC)

#endif
