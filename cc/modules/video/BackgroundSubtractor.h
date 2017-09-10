#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>

#ifndef __FF_BACKGROUNDSUBTRACTOR_H__
#define __FF_BACKGROUNDSUBTRACTOR_H__

class BackgroundSubtractor : public Nan::ObjectWrap {
public:
	virtual cv::Ptr<cv::BackgroundSubtractor> getSubtractor() = 0;
	cv::Mat fgMask;

	static void Init(v8::Local<v8::FunctionTemplate>);
	static NAN_METHOD(SetBackgroundImage);
	static NAN_METHOD(Apply);
};

#endif