#include <nan.h>
#include "../macros.h"
#include "matTypes.h"
#include "Size.h"
#include <opencv2/imgproc.hpp>
#include <iostream>

#ifndef FF_MAT_H_
#define FF_MAT_H_

class Mat : public Nan::ObjectWrap {
public:
  cv::Mat mat;

  static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static FF_GETTER(Mat, GetRows, mat.rows);
	static FF_GETTER(Mat, GetCols, mat.cols);
	static FF_GETTER(Mat, GetType, mat.type());

	static NAN_METHOD(GetData);
	static NAN_METHOD(Row);
	static NAN_METHOD(Copy);
	static NAN_METHOD(CopyTo);
	static NAN_METHOD(ConvertTo);

	static NAN_METHOD(Add);
	static NAN_METHOD(Sub);
	static NAN_METHOD(And);
	static NAN_METHOD(Or);
	static NAN_METHOD(Mul);
	static NAN_METHOD(Div);

	/* #IFDEF IMGPROC */
  static NAN_METHOD(Rescale);
  static NAN_METHOD(Resize);
  static NAN_METHOD(ResizeToMax);
	static NAN_METHOD(Threshold);
	static NAN_METHOD(CvtColor);
	static NAN_METHOD(BgrToGray);
	static NAN_METHOD(WarpPerspective);
	static NAN_METHOD(Dilate);
	static NAN_METHOD(Erode);
	/* #ENDIF IMGPROC */

	static void dilateOrErode(Nan::NAN_METHOD_ARGS_TYPE, char*, bool);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  void setNativeProps(cv::Mat);
};

#endif