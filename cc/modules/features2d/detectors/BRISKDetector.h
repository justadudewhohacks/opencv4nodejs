#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_BRISKDETECTOR_H__
#define __FF_BRISKDETECTOR_H__

class BRISKDetector : public FeatureDetector {
public:
	cv::Ptr<cv::BRISK> detector;

	int thresh = 30;
	int octaves = 3;
	double patternScale = 1.0;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(BRISKDetector, GetThresh, thresh);
	static FF_GETTER(BRISKDetector, GetOctaves, octaves);
	static FF_GETTER(BRISKDetector, GetPatternScale, patternScale);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}
};

#endif