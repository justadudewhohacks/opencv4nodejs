#include "NativeNodeUtils.h"
#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_SIMPLEBLOBDETECTOR_H__
#define __FF_SIMPLEBLOBDETECTOR_H__

class SimpleBlobDetector : public FeatureDetector {
public:
	cv::Ptr<cv::SimpleBlobDetector> detector;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}
};

#endif