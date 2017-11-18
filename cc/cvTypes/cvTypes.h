#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>


#ifndef __FF_CVTYPES_H__
#define __FF_CVTYPES_H__

#define FF_SET_CONST_WITH_VALUE(obj, constant, val) \
	FF_SET_JS_PROP(obj, constant, val);

class CvTypes {
public:
  static void Init(v8::Local<v8::Object> module);
};

#endif