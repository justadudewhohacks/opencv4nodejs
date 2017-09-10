#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_MSERDETECTOR_H__
#define __FF_MSERDETECTOR_H__

class MSERDetector : public FeatureDetector {
public:
	cv::Ptr<cv::MSER> detector;
	int delta = 5;
	int minArea = 60;
	int maxArea = 14400;
	double maxVariation = 0.25;
	double minDiversity = .2;
	int maxEvolution = 200;
	double areaThreshold = 1.01;
	double minMargin = 0.003;
	int edgeBlurSize = 5;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(MSERDetector, GetDelta, delta);
	static FF_GETTER(MSERDetector, GetMinArea, minArea);
	static FF_GETTER(MSERDetector, GetMaxArea, maxArea);
	static FF_GETTER(MSERDetector, GetMaxVariation, maxVariation);
	static FF_GETTER(MSERDetector, GetMinDiversity, minDiversity);
	static FF_GETTER(MSERDetector, GetMaxEvolution, maxEvolution);
	static FF_GETTER(MSERDetector, GetAreaThreshold, areaThreshold);
	static FF_GETTER(MSERDetector, GetMinMargin, minMargin);
	static FF_GETTER(MSERDetector, GetEdgeBlurSize, edgeBlurSize);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}
};

#endif