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
	static NAN_METHOD(ReadAsync);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	struct ReadContext {
	public:
		cv::Mat frame;
		cv::VideoCapture cap;

		const char* execute() {
			cap.read(frame);
			return "";
		}

		FF_VAL getReturnValue() {
			FF_OBJ jsMat = FF_NEW_INSTANCE(Mat::constructor);
			FF_UNWRAP_MAT_AND_GET(jsMat) = frame;
			return jsMat;
		}
	};
};

#endif