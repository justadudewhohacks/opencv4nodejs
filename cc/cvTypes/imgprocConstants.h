#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml.hpp>

#ifndef __FF_IMGPROCCONSTANTS_H__
#define __FF_IMGPROCCONSTANTS_H__

#define FF_SET_CV_CONSTANT(obj, cvConstant) \
	FF_SET_JS_PROP(obj, cvConstant, Nan::New<v8::Integer>(cvConstant));

class ImgprocConstants {
public:
  static void Init(v8::Local<v8::Object> module);
};

#endif