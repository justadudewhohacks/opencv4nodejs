#include "../Tracker.h"

#ifndef __FF_TRACKERBOOSTING_H__
#define __FF_TRACKERBOOSTING_H__

class TrackerBoosting : public Tracker {
public:
	cv::Ptr<cv::TrackerBoosting> tracker;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::Tracker> getTracker() {
		return tracker;
	}
};

#endif