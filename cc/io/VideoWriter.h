#include "macros.h"
#include <opencv2/highgui.hpp>
#include "Mat.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_VIDEOWRITER_H__
#define __FF_VIDEOWRITER_H__

class VideoWriter : public FF::ObjectWrap<VideoWriter, cv::VideoWriter> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "VideoWriter";
	}

	std::string path;

	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(New);
	static NAN_METHOD(Fourcc);
	static NAN_METHOD(Write);
	static NAN_METHOD(WriteAsync);
	static NAN_METHOD(Get);
	static NAN_METHOD(GetAsync);
	static NAN_METHOD(Set);
	static NAN_METHOD(SetAsync);
	static NAN_METHOD(Release);
};

#endif