#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#ifndef __FF_IMGPROC_CONSTANTS_H__
#define __FF_IMGPROC_CONSTANTS_H__

class ImgprocConstants {
public:
  static void Init(v8::Local<v8::Object> module);
};

#endif