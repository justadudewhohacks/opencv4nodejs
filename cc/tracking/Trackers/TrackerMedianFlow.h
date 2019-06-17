#include "../Tracker.h"

#ifndef __FF_TRACKERMEDIANFLOW_H__
#define __FF_TRACKERMEDIANFLOW_H__

class TrackerMedianFlow : public Tracker {
public:
	cv::Ptr<cv::TrackerMedianFlow> tracker;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::Tracker> getTracker() {
		return tracker;
	}
};

#endif