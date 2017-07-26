#include <nan.h>
#include "../macros.h"
#include "matTypes.h"
#include <opencv2/imgproc.hpp>
#include <iostream>

#ifndef FF_MAT_H_
#define FF_MAT_H_

class Mat : public Nan::ObjectWrap {
public:
  cv::Mat mat;

  static NAN_MODULE_INIT(Init);

	static FF_GETTER(Mat, GetRows, mat.rows);
	static FF_GETTER(Mat, GetCols, mat.cols);
	static FF_GETTER(Mat, GetType, mat.type());

  static NAN_METHOD(New);
	static NAN_METHOD(GetData);
  static NAN_METHOD(Rescale);
  static NAN_METHOD(Resize);
  static NAN_METHOD(ResizeToMax);
  static NAN_METHOD(Row);

  static Nan::Persistent<v8::FunctionTemplate> Mat::constructor;

  void setNativeProps(cv::Mat);
};

#endif