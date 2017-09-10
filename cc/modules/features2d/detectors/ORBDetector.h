#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_ORBDETECTOR_H__
#define __FF_ORBDETECTOR_H__

class ORBDetector : public FeatureDetector {
public:
	cv::Ptr<cv::ORB> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(ORBDetector, GetNFeatures, detector->getMaxFeatures());
	static FF_GETTER(ORBDetector, GetScaleFactor, detector->getScaleFactor());
	static FF_GETTER(ORBDetector, GetNlevels, detector->getNLevels());
	static FF_GETTER(ORBDetector, GetEdgeThreshold, detector->getEdgeThreshold());
	static FF_GETTER(ORBDetector, GetFirstLevel, detector->getFirstLevel());
	static FF_GETTER(ORBDetector, GetWTA_K, detector->getWTA_K());
	static FF_GETTER(ORBDetector, GetScoreType, detector->getScoreType());
	static FF_GETTER(ORBDetector, GetPatchSize, detector->getPatchSize());
	static FF_GETTER(ORBDetector, GetFastThreshold, detector->getFastThreshold());

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}

};

#endif