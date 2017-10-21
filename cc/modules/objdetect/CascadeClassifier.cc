#include "CascadeClassifier.h"
#include "Workers.h"

Nan::Persistent<v8::FunctionTemplate> CascadeClassifier::constructor;

NAN_MODULE_INIT(CascadeClassifier::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(CascadeClassifier::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("CascadeClassifier"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetPrototypeMethod(ctor, "detectMultiScale", DetectMultiScale);
	Nan::SetPrototypeMethod(ctor, "detectMultiScaleWithRejectLevels", DetectMultiScaleWithRejectLevels);
	Nan::SetPrototypeMethod(ctor, "detectMultiScaleAsync", DetectMultiScaleAsync);
	Nan::SetPrototypeMethod(ctor, "detectMultiScaleWithRejectLevelsAsync", DetectMultiScaleWithRejectLevelsAsync);

	target->Set(FF_NEW_STRING("CascadeClassifier"), ctor->GetFunction());
};

NAN_METHOD(CascadeClassifier::New) {
	FF_METHOD_CONTEXT("CascadeClassifier::New");

	FF_ARG_STRING(0, std::string xmlFilePath);

	CascadeClassifier* self = new CascadeClassifier();
	self->classifier = cv::CascadeClassifier(xmlFilePath);
	if (self->classifier.empty()) {
		FF_THROW("failed to load cascade.xml file: " + xmlFilePath);
	}
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

struct CascadeClassifier::DetectMultiScaleWorker {
public:
	cv::CascadeClassifier classifier;

	DetectMultiScaleWorker(cv::CascadeClassifier classifier) {
		this->classifier = classifier;
	}

	cv::Mat img;
	double scaleFactor = 1.1;
	uint minNeighbors = 3;
	uint flags = 0;
	cv::Size2d minSize;
	cv::Size2d maxSize;

	std::vector<cv::Rect> objectRects;
	std::vector<int> numDetections;

	const char* execute() {
		classifier.detectMultiScale(img, objectRects, numDetections, scaleFactor, (int)minNeighbors, (int)flags, minSize, maxSize);
		return "";
	}

	FF_VAL getReturnValue() {
		FF_OBJ ret = FF_NEW_OBJ();
		Nan::Set(ret, FF_NEW_STRING("objects"), ObjectArrayConverter<Rect, cv::Rect>::wrap(objectRects));
		Nan::Set(ret, FF_NEW_STRING("numDetections"), IntArrayConverter::wrap(numDetections));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Mat::Converter::arg(0, &img, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(1, &scaleFactor, info) ||
			UintConverter::optArg(2, &minNeighbors, info) ||
			UintConverter::optArg(3, &flags, info) ||
			Size::Converter::optArg(4, &minSize, info) ||
			Size::Converter::optArg(5, &maxSize, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[1]->ToObject();
		return (
			DoubleConverter::optProp(&scaleFactor, "scaleFactor", opts) ||
			UintConverter::optProp(&minNeighbors, "minNeighbors", opts) ||
			UintConverter::optProp(&flags, "flags", opts) ||
			Size::Converter::optProp(&minSize, "minSize", opts) ||
			Size::Converter::optProp(&maxSize, "maxSize", opts)
		);
	}
};

NAN_METHOD(CascadeClassifier::DetectMultiScale) {
	DetectMultiScaleWorker worker(CascadeClassifier::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("CascadeClassifier::DetectMultiScale", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleAsync) {
	DetectMultiScaleWorker worker(CascadeClassifier::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("CascadeClassifier::DetectMultiScaleAsync", DetectMultiScaleWorker, worker);
}


struct CascadeClassifier::DetectMultiScaleWithRejectLevelsWorker : public DetectMultiScaleWorker {
public:
	DetectMultiScaleWithRejectLevelsWorker(cv::CascadeClassifier classifier) : DetectMultiScaleWorker(classifier) {}

	std::vector<int> rejectLevels;
	std::vector<double> levelWeights;

	const char* execute() {
		classifier.detectMultiScale(img, objectRects, rejectLevels, levelWeights, scaleFactor, (int)minNeighbors, (int)flags, minSize, maxSize, true);
		return "";
	}

	FF_VAL getReturnValue() {
		FF_OBJ ret = FF_NEW_OBJ();
		Nan::Set(ret, FF_NEW_STRING("objects"), ObjectArrayConverter<Rect, cv::Rect>::wrap(objectRects));
		Nan::Set(ret, FF_NEW_STRING("rejectLevels"), IntArrayConverter::wrap(rejectLevels));
		Nan::Set(ret, FF_NEW_STRING("levelWeights"), DoubleArrayConverter::wrap(levelWeights));
		return ret;
	}
};

NAN_METHOD(CascadeClassifier::DetectMultiScaleWithRejectLevels) {
	DetectMultiScaleWithRejectLevelsWorker worker(CascadeClassifier::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("CascadeClassifier::DetectMultiScale", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleWithRejectLevelsAsync) {
	DetectMultiScaleWithRejectLevelsWorker worker(CascadeClassifier::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("CascadeClassifier::DetectMultiScaleWithRejectLevelsAsync", DetectMultiScaleWithRejectLevelsWorker, worker);
}