#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include "KeyPoint.h"
#include "Mat.h"

#ifndef FF_FEATUREDETECTOR_H_
#define FF_FEATUREDETECTOR_H_

class FeatureDetector : public Nan::ObjectWrap {
public:
	virtual cv::Ptr<cv::FeatureDetector> getDetector() = 0;

	static void Init(v8::Local<v8::FunctionTemplate>);

	struct DetectWorker;
	static NAN_METHOD(Detect);
	static NAN_METHOD(DetectAsync);

	struct ComputeWorker;
	static NAN_METHOD(Compute);
	static NAN_METHOD(ComputeAsync);
};

#endif