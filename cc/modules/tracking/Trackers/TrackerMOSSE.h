#include "../Tracker.h"

#if CV_MINOR_VERSION > 3

#ifndef __FF_TRACKERMOSSE_H__
#define __FF_TRACKERMOSSE_H__

class TrackerMOSSE : public Tracker {
public:
	cv::Ptr<cv::TrackerMOSSE> tracker;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::Tracker> getTracker() {
		return tracker;
	}
};

#endif

#endif