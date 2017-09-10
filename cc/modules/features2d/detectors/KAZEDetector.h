#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_KAZEDETECTOR_H__
#define __FF_KAZEDETECTOR_H__

class KAZEDetector : public FeatureDetector {
public:
	cv::Ptr<cv::KAZE> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(KAZEDetector, GetExtended, detector->getExtended());
	static FF_GETTER(KAZEDetector, GetUpright, detector->getUpright());
	static FF_GETTER(KAZEDetector, GetThreshold, detector->getThreshold());
	static FF_GETTER(KAZEDetector, GetNOctaves, detector->getNOctaves());
	static FF_GETTER(KAZEDetector, GetNOctaveLayers, detector->getNOctaveLayers());
	static FF_GETTER(KAZEDetector, GetDiffusivity, detector->getDiffusivity());

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}
};

#endif