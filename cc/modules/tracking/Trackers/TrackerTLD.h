#include "../Tracker.h"

#ifndef __FF_TRACKERTLD_H__
#define __FF_TRACKERTLD_H__

class TrackerTLD : public Tracker {
public:
	cv::Ptr<cv::TrackerTLD> tracker;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::Tracker> getTracker() {
		return tracker;
	}
};

#endif