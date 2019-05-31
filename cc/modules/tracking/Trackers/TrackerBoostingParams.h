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

	static FF_GETTER(TrackerBoostingParams, numClassifiersGet, self.numClassifiers);
	static FF_SETTER_INT(TrackerBoostingParams, numClassifiers, self.numClassifiers);
	static FF_GETTER(TrackerBoostingParams, samplerOverlapGet, self.samplerOverlap);
	static FF_SETTER_NUMBER(TrackerBoostingParams, samplerOverlap, self.samplerOverlap);
	static FF_GETTER(TrackerBoostingParams, samplerSearchFactorGet, self.samplerSearchFactor);
	static FF_SETTER_NUMBER(TrackerBoostingParams, samplerSearchFactor, self.samplerSearchFactor);
	static FF_GETTER(TrackerBoostingParams, iterationInitGet, self.iterationInit);
	static FF_SETTER_INT(TrackerBoostingParams, iterationInit, self.iterationInit);
	static FF_GETTER(TrackerBoostingParams, featureSetNumFeaturesGet, self.featureSetNumFeatures);
	static FF_SETTER_INT(TrackerBoostingParams, featureSetNumFeatures, self.featureSetNumFeatures);
};

#endif