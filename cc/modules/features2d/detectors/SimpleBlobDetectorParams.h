#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/features2d.hpp>

#ifndef __FF_SIMPLEBLOBDETECTORPARAMS_H__
#define __FF_SIMPLEBLOBDETECTORPARAMS_H__

class SimpleBlobDetectorParams : public Nan::ObjectWrap {
public:
	cv::SimpleBlobDetector::Params params;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER(SimpleBlobDetectorParams, blobColorGet, params.blobColor);
  static FF_SETTER_UINT(SimpleBlobDetectorParams, blobColor, params.blobColor);
  static FF_GETTER(SimpleBlobDetectorParams, filterByAreaGet, params.filterByArea);
  static FF_SETTER_BOOL(SimpleBlobDetectorParams, filterByArea, params.filterByArea);
  static FF_GETTER(SimpleBlobDetectorParams, filterByCircularityGet, params.filterByCircularity);
  static FF_SETTER_BOOL(SimpleBlobDetectorParams, filterByCircularity, params.filterByCircularity);
  static FF_GETTER(SimpleBlobDetectorParams, filterByColorGet, params.filterByColor);
  static FF_SETTER_BOOL(SimpleBlobDetectorParams, filterByColor, params.filterByColor);
  static FF_GETTER(SimpleBlobDetectorParams, filterByConvexityGet, params.filterByConvexity);
  static FF_SETTER_BOOL(SimpleBlobDetectorParams, filterByConvexity, params.filterByConvexity);
  static FF_GETTER(SimpleBlobDetectorParams, filterByInertiaGet, params.filterByInertia);
  static FF_SETTER_BOOL(SimpleBlobDetectorParams, filterByInertia, params.filterByInertia);
	static FF_GETTER(SimpleBlobDetectorParams, maxAreaGet, params.maxArea);
	static FF_SETTER_NUMBER(SimpleBlobDetectorParams, maxArea, params.maxArea);
	static FF_GETTER(SimpleBlobDetectorParams, maxCircularityGet, params.maxCircularity);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, maxCircularity, params.maxCircularity);
	static FF_GETTER(SimpleBlobDetectorParams, maxConvexityGet, params.maxConvexity);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, maxConvexity, params.maxConvexity);
	static FF_GETTER(SimpleBlobDetectorParams, maxInertiaRatioGet, params.maxInertiaRatio);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, maxInertiaRatio, params.maxInertiaRatio);
	static FF_GETTER(SimpleBlobDetectorParams, maxThresholdGet, params.maxThreshold);
	static FF_SETTER_NUMBER(SimpleBlobDetectorParams, maxThreshold, params.maxThreshold);
	static FF_GETTER(SimpleBlobDetectorParams, minAreaGet, params.minArea);
	static FF_SETTER_NUMBER(SimpleBlobDetectorParams, minArea, params.minArea);
  static FF_GETTER(SimpleBlobDetectorParams, minCircularityGet, params.minCircularity);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, minCircularity, params.minCircularity);
  static FF_GETTER(SimpleBlobDetectorParams, minConvexityGet, params.minConvexity);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, minConvexity, params.minConvexity);
  static FF_GETTER(SimpleBlobDetectorParams, minDistBetweenBlobsGet, params.minDistBetweenBlobs);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, minDistBetweenBlobs, params.minDistBetweenBlobs);
  static FF_GETTER(SimpleBlobDetectorParams, minInertiaRatioGet, params.minInertiaRatio);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, minInertiaRatio, params.minInertiaRatio);
	static NAN_GETTER(minRepeatabilityGet) { 
		info.GetReturnValue().Set((int)Nan::ObjectWrap::Unwrap<SimpleBlobDetectorParams>(info.This())->params.minRepeatability);
	}
  static FF_SETTER_INT(SimpleBlobDetectorParams, minRepeatability, params.minRepeatability);
  static FF_GETTER(SimpleBlobDetectorParams, minThresholdGet, params.minThreshold);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, minThreshold, params.minThreshold);
  static FF_GETTER(SimpleBlobDetectorParams, thresholdStepGet, params.thresholdStep);
  static FF_SETTER_NUMBER(SimpleBlobDetectorParams, thresholdStep, params.thresholdStep);

	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#define FF_UNWRAP_SIMPLEBLOBDETECTORPARAMS(obj) FF_UNWRAP(obj, SimpleBlobDetectorParams)
#define FF_UNWRAP_SIMPLEBLOBDETECTORPARAMS_AND_GET(obj) FF_UNWRAP_SIMPLEBLOBDETECTORPARAMS(obj)->params

#endif
