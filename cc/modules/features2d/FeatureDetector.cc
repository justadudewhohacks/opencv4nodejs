#include "FeatureDetector.h"
#include "Workers.h"

void FeatureDetector::Init(v8::Local<v8::FunctionTemplate> ctor) {
	Nan::SetPrototypeMethod(ctor, "detect", FeatureDetector::Detect);
	Nan::SetPrototypeMethod(ctor, "compute", FeatureDetector::Compute);
	Nan::SetPrototypeMethod(ctor, "detectAsync", FeatureDetector::DetectAsync);
	Nan::SetPrototypeMethod(ctor, "computeAsync", FeatureDetector::ComputeAsync);
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


NAN_METHOD(FeatureDetector::DetectAsync) {
	FF_METHOD_CONTEXT("FeatureDetector::DetectAsync");

	DetectContext ctx;
	ctx.det = FF_UNWRAP(info.This(), FeatureDetector)->getDetector();

	FF_ARG_INSTANCE(0, ctx.img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_FUNC(1, v8::Local<v8::Function> cbFunc);

	Nan::AsyncQueueWorker(new GenericAsyncWorker<DetectContext>(
		new Nan::Callback(cbFunc),
		ctx
	));
}

NAN_METHOD(FeatureDetector::ComputeAsync) {
	FF_METHOD_CONTEXT("FeatureDetector::ComputeAsync");

	ComputeContext ctx;
	ctx.det = FF_UNWRAP(info.This(), FeatureDetector)->getDetector();
	FF_ARG_INSTANCE(0, ctx.img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_ARRAY(1, FF_ARR jsKps);
	FF_UNPACK_KEYPOINT_ARRAY_TO(ctx.kps, jsKps);
	FF_ARG_FUNC(2, v8::Local<v8::Function> cbFunc);

	Nan::AsyncQueueWorker(new GenericAsyncWorker<ComputeContext>(
		new Nan::Callback(cbFunc),
		ctx
	));
}