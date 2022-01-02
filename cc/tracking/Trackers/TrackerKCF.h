#include "../Tracker.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

#ifndef __FF_TRACKERKCF_H__
#define __FF_TRACKERKCF_H__

class TrackerKCF : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
	cv::Ptr<cv::legacy::TrackerKCF> tracker;
#else
	cv::Ptr<cv::TrackerKCF> tracker;
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
