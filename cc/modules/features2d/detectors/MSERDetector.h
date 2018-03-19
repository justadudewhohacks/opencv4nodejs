#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_MSERDETECTOR_H__
#define __FF_MSERDETECTOR_H__

class MSERDetector : public FeatureDetector {
public:
	cv::Ptr<cv::MSER> detector;
	int delta ;
	int minArea;
	int maxArea;
	double maxVariation;
	double minDiversity;
	int maxEvolution;
	double areaThreshold;
	double minMargin;
	int edgeBlurSize;

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

  
    cv::Ptr<cv::FeatureDetector> getDetector(void){
		return detector;
    }
  
	cv::Ptr<cv::MSER> getMSERDetector() {
		return detector;
	}
    
    static NAN_METHOD(DetectRegions);
	static NAN_METHOD(DetectRegionsAsync);

};

#endif