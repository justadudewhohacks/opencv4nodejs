#include "Mat.h"
#include <opencv2/ximgproc.hpp>

#ifndef __FF_MATXIMGPROC_H__
#define __FF_MATXIMGPROC_H__

class MatXimgproc {
public:
  static void Init(v8::Local<v8::FunctionTemplate> ctor);

  static NAN_METHOD(GuidedFilter);
  static NAN_METHOD(GuidedFilterAsync);

};

#endif