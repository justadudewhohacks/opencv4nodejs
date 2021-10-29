#include "NativeNodeUtils.h"
#include "Mat.h"
#include "Point.h"
#include "Rect.h"
#include "macros.h"
#include <iostream>
#include <opencv2/img_hash.hpp>


#ifndef __FF_IMGHASHBASE_H__
#define __FF_IMGHASHBASE_H__

class ImgHashBase : public FF::ObjectWrapBase<ImgHashBase>, public Nan::ObjectWrap {
public:
  virtual cv::Ptr<cv::img_hash::ImgHashBase> getImgHashBase() = 0;

  static void Init(v8::Local<v8::FunctionTemplate>);

  static NAN_METHOD(Compare);
  static NAN_METHOD(CompareAsync);
  static NAN_METHOD(Compute);
  static NAN_METHOD(ComputeAsync);
};

#endif
