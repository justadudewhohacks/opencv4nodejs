#include <nan.h>
#include "FeatureDetector.h"
#include "macros.h"

#ifndef FF_BRISKDETECTOR_H_
#define FF_BRISKDETECTOR_H_

class BRISKDetector : public FeatureDetector {
public:
	cv::Ptr<cv::BRISK> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	// TODO Brisk types and fields

	//static FF_GETTER(BRISKDetector, GetThresh, 0);	
	//static FF_GETTER(BRISKDetector, GetOctaves, 0);
	//static FF_GETTER(BRISKDetector, GetPatternScale, 0);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}
};

#endif