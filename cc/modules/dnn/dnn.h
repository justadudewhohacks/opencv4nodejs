#include "NativeNodeUtils.h"
#include "opencv2/dnn.hpp"
#include "CatchCvExceptionWorker.h"
#include "Net.h"
#include "Mat.h"

#ifndef __FF_DNN_H__
#define __FF_DNN_H__

class Dnn {
public:
  static NAN_MODULE_INIT(Init);

  static NAN_METHOD(ReadNetFromTensorflow);
  static NAN_METHOD(ReadNetFromTensorflowAsync);
  static NAN_METHOD(ReadNetFromCaffe);
  static NAN_METHOD(ReadNetFromCaffeAsync);
  static NAN_METHOD(BlobFromImage);
  static NAN_METHOD(BlobFromImageAsync);
  static NAN_METHOD(BlobFromImages);
  static NAN_METHOD(BlobFromImagesAsync);
#if CV_VERSION_MINOR > 3
  static NAN_METHOD(ReadNetFromDarknet);
  static NAN_METHOD(ReadNetFromDarknetAsync);
  static NAN_METHOD(NMSBoxes);
#endif
};

#endif
