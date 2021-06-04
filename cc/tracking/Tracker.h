#include "macros.h"
#include <opencv2/tracking.hpp>
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
#include <opencv2/tracking/tracking_legacy.hpp>
#endif
#include "Mat.h"
#include "Rect.h"

#ifndef __FF_TRACKER_H__
#define __FF_TRACKER_H__

class Tracker : public FF::ObjectWrapBase<Tracker>, public Nan::ObjectWrap {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
	virtual cv::Ptr<cv::legacy::Tracker> getTracker() = 0;
#else
	virtual cv::Ptr<cv::Tracker> getTracker() = 0;
#endif

	static void Init(v8::Local<v8::FunctionTemplate>);

	static NAN_METHOD(Clear);
	static NAN_METHOD(Init);
	static NAN_METHOD(Update);
	static NAN_METHOD(GetModel);
};

#endif
