#include "ImgHashBase.h"

#ifndef __FF_PHASH_H__
#define __FF_PHASH_H__

class PHash : public ImgHashBase {
public:
  cv::Ptr<cv::img_hash::ImgHashBase> imgHashBase;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
  cv::Ptr<cv::img_hash::ImgHashBase> getImgHashBase() { return imgHashBase; }
};

#endif
