#include "macros.h"
#include <opencv2/xfeatures2d.hpp>
#include "features2d/FeatureDetector.h"

#ifndef __FF_SURFDETECTOR_H__
#define __FF_SURFDETECTOR_H__

class SURFDetector : public FeatureDetector {
public:
	cv::Ptr<cv::xfeatures2d::SURF> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(SURFDetector, GetHessianThreshold, detector->getHessianThreshold());
	static FF_GETTER(SURFDetector, GetNOctaves, detector->getNOctaves());
	static FF_GETTER(SURFDetector, GetNOctaveLayers, detector->getNOctaveLayers());
	static FF_GETTER(SURFDetector, GetExtended, detector->getExtended());
	static FF_GETTER(SURFDetector, GetUpright, detector->getUpright());

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}

};

#endif