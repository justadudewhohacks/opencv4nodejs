#include <nan.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "macros.h"

#ifndef __FF_CVTYPES_H__
#define __FF_CVTYPES_H__

class CvTypes {
public:
  static void Init(v8::Local<v8::Object> module);
};

#endif