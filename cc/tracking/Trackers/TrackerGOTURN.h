#include "../Tracker.h"

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)

#ifndef __FF_TRACKERGOTURN_H__
#define __FF_TRACKERGOTURN_H__

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
class TrackerGOTURN : public FF::ObjectWrapBase<TrackerGOTURN>, public Nan::ObjectWrap {
#else
class TrackerGOTURN : public Tracker {
#endif
public:
	cv::Ptr<cv::TrackerGOTURN> tracker;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
	static NAN_METHOD(Clear);
	static NAN_METHOD(Init);
	static NAN_METHOD(Update);
	static NAN_METHOD(GetModel);
#endif
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::Tracker> getTracker() {
		return tracker;
	}
};

#endif

#endif
