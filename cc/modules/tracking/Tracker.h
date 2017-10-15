#include "macros.h"
#include <opencv2/tracking.hpp>
#include "Mat.h"
#include "Rect.h"

#ifndef __FF_TRACKER_H__
#define __FF_TRACKER_H__

class Tracker : public Nan::ObjectWrap {
public:
	virtual cv::Ptr<cv::Tracker> getTracker() = 0;

	static void Init(v8::Local<v8::FunctionTemplate>);

	static NAN_METHOD(Clear);
	static NAN_METHOD(Init);
	static NAN_METHOD(Update);
	static NAN_METHOD(GetModel);
};

#endif