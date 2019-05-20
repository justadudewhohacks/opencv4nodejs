#include "ff.h"

#ifndef __FF_MARSHALLING_H__
#define __FF_MARSHALLING_H__

#define FF_TYPE(ff_name, ff_type, ff_assertType, ff_castType)	\
	FF_##ff_name##_TYPE {																				\
		bool checkType(v8::Local<v8::Value> val) {															\
			return ff_assertType(val);															\
		}																													\
		ff_type cast(v8::Local<v8::Value> val) {																\
			return ff_castType(val);																\
		}																													\
		std::string typeName = std::string(#ff_name);							\
	}

struct FF_TYPE(BOOL, bool, FF_IS_BOOL, FF_CAST_BOOL);
struct FF_TYPE(NUMBER, double, FF_IS_NUMBER, FF_CAST_NUMBER);
struct FF_TYPE(UINT, uint, FF_IS_UINT, FF_CAST_UINT);
struct FF_TYPE(INT, int, FF_IS_INT, FF_CAST_INT);
struct FF_TYPE(STRING, std::string, FF_IS_STRING, FF_CAST_STRING);
struct FF_TYPE(ARRAY, v8::Local<v8::Array>, FF_IS_ARRAY, FF_CAST_ARRAY);
struct FF_TYPE(OBJECT, v8::Local<v8::Object>, FF_IS_OBJ, FF_CAST_OBJ);

static FF_BOOL_TYPE ff_bool = FF_BOOL_TYPE();
static FF_NUMBER_TYPE ff_number = FF_NUMBER_TYPE();
static FF_UINT_TYPE ff_uint = FF_UINT_TYPE();
static FF_INT_TYPE ff_int = FF_INT_TYPE();
static FF_STRING_TYPE ff_string = FF_STRING_TYPE();
static FF_ARRAY_TYPE ff_array_type = FF_ARRAY_TYPE();
static FF_OBJECT_TYPE ff_obj_type = FF_OBJECT_TYPE();

#endif
