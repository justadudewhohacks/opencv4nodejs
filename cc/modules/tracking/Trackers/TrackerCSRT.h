#include "../Tracker.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 1)

#ifndef __FF_TRACKERCSRT_H__
#define __FF_TRACKERCSRT_H__

class TrackerCSRT : public Tracker {
public:
	cv::Ptr<cv::TrackerCSRT> tracker;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::Tracker> getTracker() {
		return tracker;
	}
};

#endif

#endif