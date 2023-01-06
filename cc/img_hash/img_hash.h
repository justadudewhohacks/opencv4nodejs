#include "NativeNodeUtils.h"
#include "macros.h"
#include "opencv2/img_hash.hpp"

#ifndef __FF_IMGHASH_H__
#define __FF_IMGHASH_H__

class ImgHash {
public:
  static NAN_MODULE_INIT(Init);
};

#endif