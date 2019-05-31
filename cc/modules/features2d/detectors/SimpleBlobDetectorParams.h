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

	static FF_GETTER(SimpleBlobDetectorParams, blobColorGet, self.blobColor);
  static FF_SETTER_UINT(SimpleBlobDetectorParams, blobColor, self.blobColor);
  static FF_GETTER(SimpleBlobDetectorParams, filterByAreaGet, self.filterByArea);
  static FF_SETTER_BOOL(SimpleBlobDetectorParams, filterByArea, self.filterByArea);
  static FF_GETTER(SimpleBlobDetectorParams, filterByCircularityGet, self.filterByCircularity);
  static FF_SETTER_BOOL(SimpleBlobDetectorParams, filterByCircularity, self.filterByCircularity);
  static FF_GETTER(SimpleBlobDetectorParams, filterByColorGet, self.filterByColor);
  static FF_SETTER_BOOL(SimpleBlobDetectorParams, filterByColor, self.filterByColor);
  static FF_GETTER(SimpleBlobDetectorParams, filterByConvexityGet, self.filterByConvexity);
  static FF_SETTER_BOOL(SimpleBlobDetectorParams, filterByConvexity, self.filterByConvexity);
  static FF_GETTER(SimpleBlobDetectorParams, filterByInertiaGet, self.filterByInertia);
  static FF_SETTER_BOOL(SimpleBlobDetectorParams, filterByInertia, self.filterByInertia);
	static FF_GETTER(SimpleBlobDetectorParams, maxAreaGet, self.maxArea);
	static FF_SETTER_NUMBER(SimpleBlobDetectorParams, maxArea, self.maxArea);
	static FF_GETTER(SimpleBlobDetectorParams, maxCircularityGet, self.maxCircularity);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, maxCircularity, self.maxCircularity);
	static FF_GETTER(SimpleBlobDetectorParams, maxConvexityGet, self.maxConvexity);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, maxConvexity, self.maxConvexity);
	static FF_GETTER(SimpleBlobDetectorParams, maxInertiaRatioGet, self.maxInertiaRatio);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, maxInertiaRatio, self.maxInertiaRatio);
	static FF_GETTER(SimpleBlobDetectorParams, maxThresholdGet, self.maxThreshold);
	static FF_SETTER_NUMBER(SimpleBlobDetectorParams, maxThreshold, self.maxThreshold);
	static FF_GETTER(SimpleBlobDetectorParams, minAreaGet, self.minArea);
	static FF_SETTER_NUMBER(SimpleBlobDetectorParams, minArea, self.minArea);
  static FF_GETTER(SimpleBlobDetectorParams, minCircularityGet, self.minCircularity);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, minCircularity, self.minCircularity);
  static FF_GETTER(SimpleBlobDetectorParams, minConvexityGet, self.minConvexity);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, minConvexity, self.minConvexity);
  static FF_GETTER(SimpleBlobDetectorParams, minDistBetweenBlobsGet, self.minDistBetweenBlobs);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, minDistBetweenBlobs, self.minDistBetweenBlobs);
  static FF_GETTER(SimpleBlobDetectorParams, minInertiaRatioGet, self.minInertiaRatio);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, minInertiaRatio, self.minInertiaRatio);
	static NAN_GETTER(minRepeatabilityGet) { 
		info.GetReturnValue().Set((int)Nan::ObjectWrap::Unwrap<SimpleBlobDetectorParams>(info.This())->self.minRepeatability);
	}
  static FF_SETTER_INT(SimpleBlobDetectorParams, minRepeatability, self.minRepeatability);
  static FF_GETTER(SimpleBlobDetectorParams, minThresholdGet, self.minThreshold);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, minThreshold, self.minThreshold);
  static FF_GETTER(SimpleBlobDetectorParams, thresholdStepGet, self.thresholdStep);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, thresholdStep, self.thresholdStep);
};

#endif
