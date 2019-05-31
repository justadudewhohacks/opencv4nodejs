#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/highgui.hpp>
#include "Mat.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_VIDEOCAPTURE_H__
#define __FF_VIDEOCAPTURE_H__

class VideoCapture : public FF::ObjectWrap<VideoCapture, cv::VideoCapture> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "VideoCapture";
	}

	std::string path;

	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(New);
	static NAN_METHOD(Read);
	static NAN_METHOD(Reset);
	static NAN_METHOD(ReadAsync);
	static NAN_METHOD(Get);
	static NAN_METHOD(GetAsync);
	static NAN_METHOD(Set);
	static NAN_METHOD(SetAsync);
	static NAN_METHOD(Release);
};

#endif