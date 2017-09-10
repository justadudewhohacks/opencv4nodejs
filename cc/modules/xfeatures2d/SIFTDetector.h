#include "macros.h"
#include <opencv2/xfeatures2d.hpp>
#include "features2d/FeatureDetector.h"

#ifndef __FF_SIFTDETECTOR_H__
#define __FF_SIFTDETECTOR_H__

class SIFTDetector : public FeatureDetector {
public:
	cv::Ptr<cv::xfeatures2d::SIFT> detector;
	int nFeatures = 0;
	int nOctaveLayers = 3;
	double contrastThreshold = 0.04;
	double edgeThreshold = 10;
	double sigma = 1.6;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(SIFTDetector, GetNFeatures, nFeatures);
	static FF_GETTER(SIFTDetector, GeNOctaveLayers, nOctaveLayers);
	static FF_GETTER(SIFTDetector, GetContrastThreshold, contrastThreshold);
	static FF_GETTER(SIFTDetector, GetEdgeThreshold, edgeThreshold);
	static FF_GETTER(SIFTDetector, GetSigma, sigma);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}
};

#endif