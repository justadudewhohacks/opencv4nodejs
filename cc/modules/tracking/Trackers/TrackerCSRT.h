#include "../Tracker.h"

#if CV_MINOR_VERSION > 4 || (CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION > 0)

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