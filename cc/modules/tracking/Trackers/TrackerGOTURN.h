#include "../Tracker.h"

#if CV_MINOR_VERSION > 1

#ifndef __FF_TRACKERGOTURN_H__
#define __FF_TRACKERGOTURN_H__

class TrackerGOTURN : public Tracker {
public:
	cv::Ptr<cv::TrackerGOTURN> tracker;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::Tracker> getTracker() {
		return tracker;
	}
};

#endif

#endif