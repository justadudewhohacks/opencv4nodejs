#include "../Tracker.h"

#ifndef __FF_TRACKERMEDIANFLOW_H__
#define __FF_TRACKERMEDIANFLOW_H__

class TrackerMedianFlow : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
	cv::Ptr<cv::legacy::TrackerMedianFlow> tracker;
#else
	cv::Ptr<cv::TrackerMedianFlow> tracker;
#endif

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
	cv::Ptr<cv::legacy::Tracker> getTracker() {
#else
	cv::Ptr<cv::Tracker> getTracker() {
#endif
		return tracker;
	}
};

#endif
