#include "FeatureDetector.h"

void FeatureDetector::Init(v8::Local<v8::FunctionTemplate> ctor) {
	Nan::SetPrototypeMethod(ctor, "detect", FeatureDetector::Detect);
	Nan::SetPrototypeMethod(ctor, "compute", FeatureDetector::Compute);
};

NAN_METHOD(FeatureDetector::Detect) {
	FF_METHOD_CONTEXT("FeatureDetector::Detect");

	FF_ARG_INSTANCE(0, cv::Mat img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

	std::vector<cv::KeyPoint> kps;
	FF_UNWRAP(info.This(), FeatureDetector)->getDetector()->detect(
		img, 
		kps
	);
	FF_PACK_KEYPOINT_ARRAY(jsKps, kps);
	FF_RETURN(jsKps);
}

NAN_METHOD(FeatureDetector::Compute) {
	FF_METHOD_CONTEXT("FeatureDetector::Compute");

	FF_ARG_INSTANCE(0, cv::Mat img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_ARRAY(1, FF_ARR jsKps);
	FF_UNPACK_KEYPOINT_ARRAY(kps, jsKps);

	FF_OBJ jsDesc = FF_NEW_INSTANCE(Mat::constructor);
	FF_UNWRAP(info.This(), FeatureDetector)->getDetector()->compute(
		img, 
		kps, 
		FF_UNWRAP_MAT_AND_GET(jsDesc)
	);
	FF_RETURN(jsDesc);
}