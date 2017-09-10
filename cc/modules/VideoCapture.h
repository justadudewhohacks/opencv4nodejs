#include "macros.h"
#include <opencv2/highgui.hpp>
#include "Mat.h"

#ifndef __FF_VIDEOCAPTURE_H__
#define __FF_VIDEOCAPTURE_H__

class VideoCapture : public Nan::ObjectWrap {
public:
	cv::VideoCapture cap;
	std::string path;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static NAN_METHOD(Read);
	static NAN_METHOD(Reset);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

};

#endif