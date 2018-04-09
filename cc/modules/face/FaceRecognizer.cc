#ifdef HAVE_FACE

#include "FaceRecognizer.h"

void FaceRecognizer::Init(v8::Local<v8::FunctionTemplate> ctor) {
	Nan::SetPrototypeMethod(ctor, "train", Train);
	Nan::SetPrototypeMethod(ctor, "trainAsync", TrainAsync);
	Nan::SetPrototypeMethod(ctor, "predict", Predict);
	Nan::SetPrototypeMethod(ctor, "predictAsync", PredictAsync);
	Nan::SetPrototypeMethod(ctor, "save", Save);
	Nan::SetPrototypeMethod(ctor, "load", Load);
};

struct FaceRecognizer::TrainWorker : public CatchCvExceptionWorker {
public:
	cv::Ptr<cv::face::FaceRecognizer> self;
	TrainWorker(cv::Ptr<cv::face::FaceRecognizer> self) {
		this->self = self;
	}

	std::vector<cv::Mat> images;
	std::vector<int> labels;

	std::string executeCatchCvExceptionWorker() {
		self->train(images, labels);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			ObjectArrayConverter<Mat, cv::Mat>::arg(0, &images, info) ||
			IntArrayConverter::arg(1, &labels, info)
		);
	}
};

NAN_METHOD(FaceRecognizer::Train) {
	TrainWorker worker(FF_UNWRAP(info.This(), FaceRecognizer)->getFaceRecognizer());
	FF_WORKER_SYNC("FaceRecognizer::Train", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(FaceRecognizer::TrainAsync) {
	TrainWorker worker(FF_UNWRAP(info.This(), FaceRecognizer)->getFaceRecognizer());
	FF_WORKER_ASYNC("FaceRecognizer::TrainAsync", TrainWorker, worker);
}


struct FaceRecognizer::PredictWorker : public CatchCvExceptionWorker {
public:
	cv::Ptr<cv::face::FaceRecognizer> self;
	PredictWorker(cv::Ptr<cv::face::FaceRecognizer> self) {
		this->self = self;
	}

	cv::Mat image;
	int label;
	double confidence;

	std::string executeCatchCvExceptionWorker() {
		self->predict(image, label, confidence);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("label").ToLocalChecked(), Nan::New(label));
		Nan::Set(ret, Nan::New("confidence").ToLocalChecked(), Nan::New(confidence));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &image, info)
		);
	}
};

NAN_METHOD(FaceRecognizer::Predict) {
	PredictWorker worker(FF_UNWRAP(info.This(), FaceRecognizer)->getFaceRecognizer());
	FF_WORKER_SYNC("FaceRecognizer::Predict", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(FaceRecognizer::PredictAsync) {
	PredictWorker worker(FF_UNWRAP(info.This(), FaceRecognizer)->getFaceRecognizer());
	FF_WORKER_ASYNC("FaceRecognizer::PredictAsync", PredictWorker, worker);
}

NAN_METHOD(FaceRecognizer::Save) {
	FF_METHOD_CONTEXT("FaceRecognizer::Save");
	FF_ARG_STRING(0, std::string path);
	FF_UNWRAP(info.This(), FaceRecognizer)->save(path);
}

NAN_METHOD(FaceRecognizer::Load) {
	FF_METHOD_CONTEXT("FaceRecognizer::Load");
	FF_ARG_STRING(0, std::string path);
	FF_UNWRAP(info.This(), FaceRecognizer)->load(path);
}

#endif