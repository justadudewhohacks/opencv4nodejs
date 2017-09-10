#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_AGASTDETECTOR_H__
#define __FF_AGASTDETECTOR_H__

class AGASTDetector : public FeatureDetector {
public:
	cv::Ptr<cv::AgastFeatureDetector> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(AGASTDetector, GetThreshold, detector->getThreshold());
	static FF_GETTER(AGASTDetector, GetNonmaxSuppression, detector->getNonmaxSuppression());
	static FF_GETTER(AGASTDetector, GetType, detector->getType());

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}
};

#endif