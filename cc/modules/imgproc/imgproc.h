#include <nan.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "macros.h"

#ifndef __FF_IMGPROC_H__
#define __FF_IMGPROC_H__

class Imgproc {
public:
  static NAN_MODULE_INIT(Init);
};

#endif