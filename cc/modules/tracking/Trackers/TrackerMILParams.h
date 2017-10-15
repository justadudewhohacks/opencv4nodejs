#include "macros.h"
#include <opencv2/tracking.hpp>

#ifndef __FF_TRACKERMILPARAMS_H__
#define __FF_TRACKERMILPARAMS_H__

class TrackerMILParams : public Nan::ObjectWrap {
public:
	cv::TrackerMIL::Params params;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER(TrackerMILParams, samplerInitInRadiusGet, params.samplerInitInRadius);
	static FF_SETTER_NUMBER(TrackerMILParams, samplerInitInRadius, params.samplerInitInRadius);
	static FF_GETTER(TrackerMILParams, samplerSearchWinSizeGet, params.samplerSearchWinSize);
	static FF_SETTER_NUMBER(TrackerMILParams, samplerSearchWinSize, params.samplerSearchWinSize);
	static FF_GETTER(TrackerMILParams, samplerTrackInRadiusGet, params.samplerTrackInRadius);
	static FF_SETTER_NUMBER(TrackerMILParams, samplerTrackInRadius, params.samplerTrackInRadius);
	static FF_GETTER(TrackerMILParams, samplerInitMaxNegNumGet, params.samplerInitMaxNegNum);
	static FF_SETTER_INT(TrackerMILParams, samplerInitMaxNegNum, params.samplerInitMaxNegNum);
	static FF_GETTER(TrackerMILParams, samplerTrackMaxPosNumGet, params.samplerTrackMaxPosNum);
	static FF_SETTER_INT(TrackerMILParams, samplerTrackMaxPosNum, params.samplerTrackMaxPosNum);
	static FF_GETTER(TrackerMILParams, samplerTrackMaxNegNumGet, params.samplerTrackMaxNegNum);
	static FF_SETTER_INT(TrackerMILParams, samplerTrackMaxNegNum, params.samplerTrackMaxNegNum);
	static FF_GETTER(TrackerMILParams, featureSetNumFeaturesGet, params.featureSetNumFeatures);
	static FF_SETTER_INT(TrackerMILParams, featureSetNumFeatures, params.featureSetNumFeatures);

	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#define FF_UNWRAP_TRACKERMILPARAMS(obj) FF_UNWRAP(obj, TrackerMILParams)
#define FF_UNWRAP_TRACKERMILPARAMS_AND_GET(obj) FF_UNWRAP_TRACKERMILPARAMS(obj)->params

#endif