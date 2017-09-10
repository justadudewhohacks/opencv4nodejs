#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_AKAZEDETECTOR_H__
#define __FF_AKAZEDETECTOR_H__

class AKAZEDetector : public FeatureDetector {
public:
	cv::Ptr<cv::AKAZE> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(AKAZEDetector, GetDescriptorType, detector->getDescriptorType());
	static FF_GETTER(AKAZEDetector, GetDescriptorSize, detector->getDescriptorSize());
	static FF_GETTER(AKAZEDetector, GetDescriptorChannels, detector->getDescriptorChannels());
	static FF_GETTER(AKAZEDetector, GetThreshold, detector->getThreshold());
	static FF_GETTER(AKAZEDetector, GetNOctaves, detector->getNOctaves());
	static FF_GETTER(AKAZEDetector, GetNOctaveLayers, detector->getNOctaveLayers());
	static FF_GETTER(AKAZEDetector, GetDiffusity, detector->getDiffusivity());

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}
};

#endif