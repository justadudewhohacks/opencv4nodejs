#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include "KeyPoint.h"
#include "Mat.h"
#include "CatchCvExceptionWorker.h"
#include "NativeNodeUtils.h"

#ifndef FF_FEATUREDETECTOR_H_
#define FF_FEATUREDETECTOR_H_

class FeatureDetector : public FF::ObjectWrapBase<FeatureDetector>, public Nan::ObjectWrap {
public:
	virtual cv::Ptr<cv::FeatureDetector> getDetector() = 0;

	static void Init(v8::Local<v8::FunctionTemplate>);

	static NAN_METHOD(Detect);
	static NAN_METHOD(DetectAsync);
	static NAN_METHOD(Compute);
	static NAN_METHOD(ComputeAsync);
};

#endif