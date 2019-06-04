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

	FF_ACCESSORS(samplerInitInRadius, FF::FloatConverter);
	FF_ACCESSORS(samplerSearchWinSize, FF::FloatConverter);
	FF_ACCESSORS(samplerTrackInRadius, FF::FloatConverter);
	FF_ACCESSORS(samplerInitMaxNegNum, FF::IntConverter);
	FF_ACCESSORS(samplerTrackMaxPosNum, FF::IntConverter);
	FF_ACCESSORS(samplerTrackMaxNegNum, FF::IntConverter);
	FF_ACCESSORS(featureSetNumFeatures, FF::IntConverter);

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);
};

#endif