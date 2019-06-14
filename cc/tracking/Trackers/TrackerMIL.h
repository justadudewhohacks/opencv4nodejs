#include "../Tracker.h"

#ifndef __FF_TRACKERMIL_H__
#define __FF_TRACKERMIL_H__

class TrackerMIL : public Tracker {
public:
	cv::Ptr<cv::TrackerMIL> tracker;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::Tracker> getTracker() {
		return tracker;
	}
};

#endif