#include "../Tracker.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 1)

#ifndef __FF_TRACKERCSRT_H__
#define __FF_TRACKERCSRT_H__

class TrackerCSRT : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
	cv::Ptr<cv::legacy::TrackerCSRT> tracker;
#else
	cv::Ptr<cv::TrackerCSRT> tracker;
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

#endif
