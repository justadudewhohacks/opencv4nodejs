#include "macros.h"
#include <opencv2/xfeatures2d.hpp>
#include "features2d/FeatureDetector.h"

#ifndef __FF_SIFTDETECTOR_H__
#define __FF_SIFTDETECTOR_H__

class SIFTDetector : public FeatureDetector {
public:
	cv::Ptr<cv::xfeatures2d::SIFT> detector;
	int nFeatures;
	int nOctaveLayers;
	double contrastThreshold;
	double edgeThreshold;
	double sigma;

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