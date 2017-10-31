#include "macros.h"
#include <opencv2/highgui.hpp>
#include "Mat.h"

#ifndef __FF_VIDEOWRITER_H__
#define __FF_VIDEOWRITER_H__

class VideoWriter : public Nan::ObjectWrap {
public:
	cv::VideoWriter writer;
	std::string path;

  static NAN_MODULE_INIT(Init);

	struct NewWorker;
  static NAN_METHOD(New);

	struct FourccWorker;
	static NAN_METHOD(Fourcc);

	struct WriteWorker;
  static NAN_METHOD(Write);
	static NAN_METHOD(WriteAsync);

	static NAN_METHOD(Get);
	static NAN_METHOD(Set);
	static NAN_METHOD(Release);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::VideoWriter* getNativeObjectPtr() { return &writer; }
	cv::VideoWriter getNativeObject() { return writer; }

	typedef InstanceConverter<VideoWriter, cv::VideoWriter> Converter;

	static const char* getClassName() {
		return "VideoWriter";
	}
};

#endif