#include "NativeNodeUtils.h"

#ifndef __FF_MACROS_H__
#define __FF_MACROS_H__

/* define getters, custom expression for accessing properties of "self" */
#define FF_GETTER_CUSTOM(ff_property_name, ff_property_converter, ff_access_property_expr) \
	static ff_property_converter::Type getProperty_##ff_property_name(ClassType* self) { \
		return self->ff_access_property_expr; \
	} \
	static NAN_GETTER(ff_property_name##_getter) { \
		getter<ff_property_converter>(info, getProperty_##ff_property_name); \
	}

/* define getters */
#define FF_GETTER(ff_property_name, ff_property_converter) \
	FF_GETTER_CUSTOM(ff_property_name, ff_property_converter, self.ff_property_name)

/* define accessors, custom expression for accessing properties of "self" */
#define FF_ACCESSORS_CUSTOM(ff_property_name, ff_property_converter, ff_access_property_expr) \
	FF_GETTER_CUSTOM(ff_property_name, ff_property_converter, ff_access_property_expr); \
	static void setProperty_##ff_property_name(ClassType* self, ff_property_converter::Type val) { \
		self->ff_access_property_expr = val; \
	} \
	static NAN_SETTER(ff_property_name##_setter) { \
		setter<ff_property_converter>(#ff_property_name, info, value, setProperty_##ff_property_name); \
	}

/* define accessors */
#define FF_ACCESSORS(ff_property_name, ff_property_converter) \
	FF_ACCESSORS_CUSTOM(ff_property_name, ff_property_converter, self.ff_property_name)

/* define accessors, self is pointer type */
#define FF_ACCESSORS_PTR(ff_property_name, ff_property_converter) \
	FF_ACCESSORS_CUSTOM(ff_property_name, ff_property_converter, self->ff_property_name)

#define FF_SET_JS_PROP(obj, prop, val) Nan::Set(obj, FF::newString(#prop), val)

#define FF_SET_CV_CONSTANT(obj, cvConstant) \
	FF_SET_JS_PROP(obj, cvConstant, Nan::New<v8::Integer>(cvConstant));

#define FF_ASSERT_CONSTRUCT_CALL() \
  if (!info.IsConstructCall()) { \
    return tryCatch.throwError("constructor has to be called with \"new\" keyword"); \
  }

#endif
