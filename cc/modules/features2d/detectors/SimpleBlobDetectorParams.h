#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/features2d.hpp>

#ifndef __FF_SIMPLEBLOBDETECTORPARAMS_H__
#define __FF_SIMPLEBLOBDETECTORPARAMS_H__

class SimpleBlobDetectorParams : public FF::ObjectWrap <SimpleBlobDetectorParams, cv::SimpleBlobDetector::Params> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "SimpleBlobDetector";
	}

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  FF_ACCESSORS(blobColor, FF::UcharConverter);
  FF_ACCESSORS(filterByArea, FF::BoolConverter);
  FF_ACCESSORS(filterByCircularity, FF::BoolConverter);
  FF_ACCESSORS(filterByColor, FF::BoolConverter);
  FF_ACCESSORS(filterByConvexity, FF::BoolConverter);
  FF_ACCESSORS(filterByInertia, FF::BoolConverter);
  FF_ACCESSORS(minArea, FF::FloatConverter);
  FF_ACCESSORS(maxArea, FF::FloatConverter);
  FF_ACCESSORS(minCircularity, FF::FloatConverter);
  FF_ACCESSORS(maxCircularity, FF::FloatConverter);
  FF_ACCESSORS(minConvexity, FF::FloatConverter);
  FF_ACCESSORS(maxConvexity, FF::FloatConverter);
  FF_ACCESSORS(minInertiaRatio, FF::FloatConverter);
  FF_ACCESSORS(maxInertiaRatio, FF::FloatConverter);
  FF_ACCESSORS(minThreshold, FF::FloatConverter);
  FF_ACCESSORS(maxThreshold, FF::FloatConverter);
  FF_ACCESSORS(minDistBetweenBlobs, FF::FloatConverter);
  FF_ACCESSORS(minRepeatability, FF::IntConverter);
  FF_ACCESSORS(thresholdStep, FF::FloatConverter);
};

#endif
