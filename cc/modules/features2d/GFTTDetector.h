#include <nan.h>
#include <opencv2/features2d.hpp>
#include "../../macros.h"

class GFTTDetector : public Nan::ObjectWrap {
public:
	cv::Ptr<cv::GFTTDetector> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(GFTTDetector, GetMaxFeatures, detector->getMaxFeatures());
	static FF_GETTER(GFTTDetector, GetQualityLevel, detector->getQualityLevel());
	static FF_GETTER(GFTTDetector, GetMinDistance, detector->getMinDistance());
	static FF_GETTER(GFTTDetector, GetBlockSize, detector->getBlockSize());
	static FF_GETTER(GFTTDetector, GetUseHarrisDetector, detector->getHarrisDetector());
	static FF_GETTER(GFTTDetector, GetK, detector->getK());

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};
