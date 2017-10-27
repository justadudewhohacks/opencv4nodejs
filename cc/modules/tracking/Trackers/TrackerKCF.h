#include "../Tracker.h"

#if CV_MINOR_VERSION > 0

#ifndef __FF_TRACKERKCF_H__
#define __FF_TRACKERKCF_H__

class TrackerKCF : public Tracker {
public:
	cv::Ptr<cv::TrackerKCF> tracker;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::Tracker> getTracker() {
		return tracker;
	}
};

#endif

#endif