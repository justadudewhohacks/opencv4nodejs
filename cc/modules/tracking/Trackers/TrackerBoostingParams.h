#include "macros.h"
#include <opencv2/tracking.hpp>

#ifndef __FF_TRACKERBOOSTINGPARAMS_H__
#define __FF_TRACKERBOOSTINGPARAMS_H__

class TrackerBoostingParams : public FF::ObjectWrap<TrackerBoostingParams, cv::TrackerBoosting::Params> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "TrackerBoostingParams";
	}

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	FF_ACCESSORS(numClassifiers, FF::IntConverter);
	FF_ACCESSORS(samplerOverlap, FF::FloatConverter);
	FF_ACCESSORS(samplerSearchFactor, FF::FloatConverter);
	FF_ACCESSORS(iterationInit, FF::IntConverter);
	FF_ACCESSORS(featureSetNumFeatures, FF::IntConverter);
};

#endif