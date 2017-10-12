#include "FeatureDetector.h"

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

class AsyncDetectWorker : public Nan::AsyncWorker {
public:
	cv::Ptr<cv::FeatureDetector> det;
	cv::Mat img;
	std::vector<cv::KeyPoint> kps;

	AsyncDetectWorker(
		Nan::Callback *callback,
		cv::Ptr<cv::FeatureDetector> det,
		cv::Mat img
	) : Nan::AsyncWorker(callback), det(det), img(img) {}
	~AsyncDetectWorker() {}

	void Execute() {
		det->detect(img, kps);
	}

	void HandleOKCallback() {
		Nan::HandleScope scope;
		FF_PACK_KEYPOINT_ARRAY(jsKps, kps);

		FF_VAL argv[] = { Nan::Null(), jsKps };
		callback->Call(2, argv);
	}
};

NAN_METHOD(FeatureDetector::DetectAsync) {
	FF_METHOD_CONTEXT("FeatureDetector::DetectAsync");

	FF_ARG_INSTANCE(0, cv::Mat img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_FUNC(1, v8::Local<v8::Function> cbFunc);

	Nan::AsyncQueueWorker(new AsyncDetectWorker(
		new Nan::Callback(cbFunc),
		FF_UNWRAP(info.This(), FeatureDetector)->getDetector(),
		img
	));
}

class AsyncComputeWorker : public Nan::AsyncWorker {
public:
	cv::Ptr<cv::FeatureDetector> det;
	cv::Mat img;
	std::vector<cv::KeyPoint> kps;
	cv::Mat desc;

	AsyncComputeWorker(
		Nan::Callback *callback,
		cv::Ptr<cv::FeatureDetector> det,
		cv::Mat img,
		std::vector<cv::KeyPoint> kps
	) : Nan::AsyncWorker(callback), det(det), img(img), kps(kps) {}
	~AsyncComputeWorker() {}

	void Execute() {
		det->compute(img, kps, desc);
	}

	void HandleOKCallback() {
		Nan::HandleScope scope;
		FF_OBJ jsDesc = FF_NEW_INSTANCE(Mat::constructor);
		FF_UNWRAP_MAT_AND_GET(jsDesc) = desc;

		FF_VAL argv[] = { Nan::Null(), jsDesc };
		callback->Call(2, argv);
	}
};

NAN_METHOD(FeatureDetector::ComputeAsync) {
	FF_METHOD_CONTEXT("FeatureDetector::ComputeAsync");

	FF_ARG_INSTANCE(0, cv::Mat img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_ARRAY(1, FF_ARR jsKps);
	FF_ARG_FUNC(2, v8::Local<v8::Function> cbFunc);
	FF_UNPACK_KEYPOINT_ARRAY(kps, jsKps);

	Nan::AsyncQueueWorker(new AsyncComputeWorker(
		new Nan::Callback(cbFunc),
		FF_UNWRAP(info.This(), FeatureDetector)->getDetector(),
		img,
		kps
	));
}