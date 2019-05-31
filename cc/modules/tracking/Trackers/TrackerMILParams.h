#include "macros.h"
#include <opencv2/tracking.hpp>

#ifndef __FF_TRACKERMILPARAMS_H__
#define __FF_TRACKERMILPARAMS_H__

class TrackerMILParams : public FF::ObjectWrap<TrackerMILParams, cv::TrackerMIL::Params> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "TrackerMILParams";
	}


  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER(TrackerMILParams, samplerInitInRadiusGet, self.samplerInitInRadius);
	static FF_SETTER_NUMBER(TrackerMILParams, samplerInitInRadius, self.samplerInitInRadius);
	static FF_GETTER(TrackerMILParams, samplerSearchWinSizeGet, self.samplerSearchWinSize);
	static FF_SETTER_NUMBER(TrackerMILParams, samplerSearchWinSize, self.samplerSearchWinSize);
	static FF_GETTER(TrackerMILParams, samplerTrackInRadiusGet, self.samplerTrackInRadius);
	static FF_SETTER_NUMBER(TrackerMILParams, samplerTrackInRadius, self.samplerTrackInRadius);
	static FF_GETTER(TrackerMILParams, samplerInitMaxNegNumGet, self.samplerInitMaxNegNum);
	static FF_SETTER_INT(TrackerMILParams, samplerInitMaxNegNum, self.samplerInitMaxNegNum);
	static FF_GETTER(TrackerMILParams, samplerTrackMaxPosNumGet, self.samplerTrackMaxPosNum);
	static FF_SETTER_INT(TrackerMILParams, samplerTrackMaxPosNum, self.samplerTrackMaxPosNum);
	static FF_GETTER(TrackerMILParams, samplerTrackMaxNegNumGet, self.samplerTrackMaxNegNum);
	static FF_SETTER_INT(TrackerMILParams, samplerTrackMaxNegNum, self.samplerTrackMaxNegNum);
	static FF_GETTER(TrackerMILParams, featureSetNumFeaturesGet, self.featureSetNumFeatures);
	static FF_SETTER_INT(TrackerMILParams, featureSetNumFeatures, self.featureSetNumFeatures);
};

#endif