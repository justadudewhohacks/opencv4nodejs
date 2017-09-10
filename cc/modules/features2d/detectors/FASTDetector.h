#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_FASTDETECTOR_H__
#define __FF_FASTDETECTOR_H__

class FASTDetector : public FeatureDetector {
public:
	cv::Ptr<cv::FastFeatureDetector> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(FASTDetector, GetThreshold, detector->getThreshold());
	static FF_GETTER(FASTDetector, GetNonmaxSuppression, detector->getNonmaxSuppression());
	static FF_GETTER(FASTDetector, GetType, detector->getType());

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}
};

#endif