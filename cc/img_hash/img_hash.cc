#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMG_HASH

#include "img_hash.h"
#include "PHash.h"

NAN_MODULE_INIT(ImgHash::Init) {
  PHash::Init(target);
};

#endif
