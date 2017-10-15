#include "macros.h"
#include <opencv2/tracking.hpp>

#ifndef __FF_TRACKERBOOSTINGPARAMS_H__
#define __FF_TRACKERBOOSTINGPARAMS_H__

class TrackerBoostingParams : public Nan::ObjectWrap {
public:
	cv::TrackerBoosting::Params params;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER(TrackerBoostingParams, numClassifiersGet, params.numClassifiers);
	static FF_SETTER_INT(TrackerBoostingParams, numClassifiers, params.numClassifiers);
	static FF_GETTER(TrackerBoostingParams, samplerOverlapGet, params.samplerOverlap);
	static FF_SETTER_NUMBER(TrackerBoostingParams, samplerOverlap, params.samplerOverlap);
	static FF_GETTER(TrackerBoostingParams, samplerSearchFactorGet, params.samplerSearchFactor);
	static FF_SETTER_NUMBER(TrackerBoostingParams, samplerSearchFactor, params.samplerSearchFactor);
	static FF_GETTER(TrackerBoostingParams, iterationInitGet, params.iterationInit);
	static FF_SETTER_INT(TrackerBoostingParams, iterationInit, params.iterationInit);
	static FF_GETTER(TrackerBoostingParams, featureSetNumFeaturesGet, params.featureSetNumFeatures);
	static FF_SETTER_INT(TrackerBoostingParams, featureSetNumFeatures, params.featureSetNumFeatures);


	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#define FF_UNWRAP_TRACKERBOOSTINGPARAMS(obj) FF_UNWRAP(obj, TrackerBoostingParams)
#define FF_UNWRAP_TRACKERBOOSTINGPARAMS_AND_GET(obj) FF_UNWRAP_TRACKERBOOSTINGPARAMS(obj)->params

#endif