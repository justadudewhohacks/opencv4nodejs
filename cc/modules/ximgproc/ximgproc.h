#include <nan.h>
#include <opencv2/xImgproc.hpp>

#ifndef __FF_XIMGPROC_H__
#define __FF_XIMGPROC_H__

class XImgproc {
public:
  static NAN_MODULE_INIT(Init);
};

#endif