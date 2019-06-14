#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_CORE_CONSTANTS_H__
#define __FF_CORE_CONSTANTS_H__

#define FF_SET_CONST_WITH_VALUE(obj, constant, val) \
	FF_SET_JS_PROP(obj, constant, val);

class CoreConstants {
public:
  static void Init(v8::Local<v8::Object> module);
};

#endif