#include "FeatureDetector.h"
#include "CatchCvExceptionWorker.h"

void FeatureDetector::Init(v8::Local<v8::FunctionTemplate> ctor) {
	Nan::SetPrototypeMethod(ctor, "detect", FeatureDetector::Detect);
	Nan::SetPrototypeMethod(ctor, "compute", FeatureDetector::Compute);
	Nan::SetPrototypeMethod(ctor, "detectAsync", FeatureDetector::DetectAsync);
	Nan::SetPrototypeMethod(ctor, "computeAsync", FeatureDetector::ComputeAsync);
};

struct FeatureDetector::DetectWorker : public CatchCvExceptionWorker {
public:
	cv::Ptr<cv::FeatureDetector> det;
	DetectWorker(cv::Ptr<cv::FeatureDetector> _det) {
		this->det = _det;
	}

	cv::Mat img;
	std::vector<cv::KeyPoint> kps;

	const char* executeCatchCvExceptionWorker() {
		det->detect(img, kps);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Mat::Converter::arg(0, &img, info);
	}


	FF_VAL getReturnValue() {
		return ObjectArrayConverter<KeyPoint, cv::KeyPoint>::wrap(kps);
	}
};

NAN_METHOD(FeatureDetector::Detect) {
	DetectWorker worker(FF_UNWRAP(info.This(), FeatureDetector)->getDetector());
	FF_WORKER_SYNC("FeatureDetector::Detect", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(FeatureDetector::DetectAsync) {
	DetectWorker worker(FF_UNWRAP(info.This(), FeatureDetector)->getDetector());
	FF_WORKER_ASYNC("FeatureDetector::DetectAsync", DetectWorker, worker);
}

struct FeatureDetector::ComputeWorker : public CatchCvExceptionWorker {
public:
	cv::Ptr<cv::FeatureDetector> det;
	ComputeWorker(cv::Ptr<cv::FeatureDetector> _det) {
		this->det = _det;
	}

	cv::Mat img;
	std::vector<cv::KeyPoint> kps;
	cv::Mat desc;

	const char* executeCatchCvExceptionWorker() {
		det->compute(img, kps, desc);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &img, info)
			|| ObjectArrayConverter<KeyPoint, cv::KeyPoint>::arg(1, &kps, info)
		);
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(desc);
	}
};

NAN_METHOD(FeatureDetector::Compute) {
	ComputeWorker worker(FF_UNWRAP(info.This(), FeatureDetector)->getDetector());
	FF_WORKER_SYNC("FeatureDetector::Compute", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(FeatureDetector::ComputeAsync) {
	ComputeWorker worker(FF_UNWRAP(info.This(), FeatureDetector)->getDetector());
	FF_WORKER_ASYNC("FeatureDetector::ComputeAsync", ComputeWorker, worker);
}