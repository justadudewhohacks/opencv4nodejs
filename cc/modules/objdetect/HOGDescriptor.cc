#include "HOGDescriptor.h"
#include "Mat.h"
#include "Rect.h"
#include "Point.h"
#include "DetectionROI.h"
#include "Workers.h"

Nan::Persistent<v8::FunctionTemplate> HOGDescriptor::constructor;

NAN_MODULE_INIT(HOGDescriptor::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(HOGDescriptor::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("HOGDescriptor"));
	instanceTemplate->SetInternalFieldCount(1);
	
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("winSize"), winSize);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("blockSize"), blockSize);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("blockStride"), blockStride);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("cellSize"), cellSize);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("nbins"), nbins);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("derivAperture"), derivAperture);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("histogramNormType"), histogramNormType);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("nlevels"), nlevels);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("winSigma"), winSigma);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("L2HysThreshold"), L2HysThreshold);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("gammaCorrection"), gammaCorrection);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("signedGradient"), signedGradient);

	Nan::SetMethod(ctor, "getDaimlerPeopleDetector", GetDaimlerPeopleDetector);
	Nan::SetMethod(ctor, "getDefaultPeopleDetector", GetDefaultPeopleDetector);

	Nan::SetPrototypeMethod(ctor, "compute", Compute);
	Nan::SetPrototypeMethod(ctor, "computeAsync", ComputeAsync);
	Nan::SetPrototypeMethod(ctor, "computeGradient", ComputeGradient);
	Nan::SetPrototypeMethod(ctor, "computeGradientAsync", ComputeGradientAsync);
	Nan::SetPrototypeMethod(ctor, "detect", Detect);
	Nan::SetPrototypeMethod(ctor, "detectAsync", DetectAsync);
	Nan::SetPrototypeMethod(ctor, "detectROI", DetectROI);
	Nan::SetPrototypeMethod(ctor, "detectROIAsync", DetectROIAsync);
	Nan::SetPrototypeMethod(ctor, "detectMultiScale", DetectMultiScale);
	Nan::SetPrototypeMethod(ctor, "detectMultiScaleAsync", DetectMultiScaleAsync);
	Nan::SetPrototypeMethod(ctor, "detectMultiScaleROI", DetectMultiScaleROI);
	Nan::SetPrototypeMethod(ctor, "detectMultiScaleROIAsync", DetectMultiScaleROIAsync);
	Nan::SetPrototypeMethod(ctor, "groupRectangles", GroupRectangles);
	Nan::SetPrototypeMethod(ctor, "groupRectanglesAsync", GroupRectanglesAsync);
	Nan::SetPrototypeMethod(ctor, "checkDetectorSize", CheckDetectorSize);
	Nan::SetPrototypeMethod(ctor, "setSVMDetector", SetSVMDetector);
	Nan::SetPrototypeMethod(ctor, "save", Save);
	Nan::SetPrototypeMethod(ctor, "load", Load);

	target->Set(FF_NEW_STRING("HOGDescriptor"), ctor->GetFunction());
};

NAN_METHOD(HOGDescriptor::New) {
	FF_METHOD_CONTEXT("HOGDescriptor::New");

	// optional args
	bool hasOptArgsObj = FF_ARG_IS_OBJECT(0) && !FF_IS_INSTANCE(Size::constructor, info[1]);
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

	FF_GET_INSTANCE_IFDEF(optArgs, cv::Size2d winSize, "winSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d(64, 128));
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Size2d blockSize, "blockSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d(16, 16));
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Size2d blockStride, "blockStride", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d(8, 8));
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Size2d cellSize, "cellSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d(8, 8));
	FF_GET_UINT_IFDEF(optArgs, uint nbins, "nbins", 9);
	FF_GET_INT_IFDEF(optArgs, int derivAperture, "derivAperture", 1);
	FF_GET_NUMBER_IFDEF(optArgs, double winSigma, "winSigma", -1);
	FF_GET_UINT_IFDEF(optArgs, uint histogramNormType, "histogramNormType", cv::HOGDescriptor::L2Hys);
	FF_GET_NUMBER_IFDEF(optArgs, double L2HysThreshold, "L2HysThreshold", 0.2);
	FF_GET_BOOL_IFDEF(optArgs, bool gammaCorrection, "gammaCorrection", false);
	FF_GET_UINT_IFDEF(optArgs, uint nlevels, "nlevels", cv::HOGDescriptor::DEFAULT_NLEVELS);
	FF_GET_BOOL_IFDEF(optArgs, bool signedGradient, "signedGradient", false);
	if (!hasOptArgsObj) {
		FF_ARG_INSTANCE_IFDEF(0, winSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, winSize);
		FF_ARG_INSTANCE_IFDEF(1, blockSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, blockSize);
		FF_ARG_INSTANCE_IFDEF(2, blockStride, Size::constructor, FF_UNWRAP_SIZE_AND_GET, blockStride);
		FF_ARG_INSTANCE_IFDEF(3, cellSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, cellSize);
		FF_ARG_UINT_IFDEF(4, nbins, nbins);
		FF_ARG_INT_IFDEF(5, derivAperture, derivAperture);
		FF_ARG_NUMBER_IFDEF(6, winSigma, winSigma);
		FF_ARG_UINT_IFDEF(7, histogramNormType, histogramNormType);
		FF_ARG_NUMBER_IFDEF(8, L2HysThreshold, L2HysThreshold);
		FF_ARG_BOOL_IFDEF(9, gammaCorrection, gammaCorrection);
		FF_ARG_UINT_IFDEF(10, nlevels, nlevels);
		FF_ARG_BOOL_IFDEF(11, signedGradient, signedGradient);
	}

	HOGDescriptor* self = new HOGDescriptor();
	self->hog = cv::HOGDescriptor(
		winSize, 
		blockSize, 
		blockStride,
		cellSize, 
		(int)nbins, 
		derivAperture, 
		winSigma,
		(int)histogramNormType,
		L2HysThreshold,
		gammaCorrection,
		(int)nlevels,
		signedGradient
	);

	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

struct HOGDescriptor::ComputeWorker {
public:
	cv::HOGDescriptor hog;

	ComputeWorker(cv::HOGDescriptor hog) {
		this->hog = hog;
	}

	cv::Mat img;
	cv::Size2d winStride;
	cv::Size2d padding;
	std::vector<cv::Point2i> locations;

	std::vector<float> descriptors;

	const char* execute() {
		hog.compute(img, descriptors, winStride, padding, locations);
		return "";
	}

	FF_VAL getReturnValue() {
		return FloatArrayConverter::wrap(descriptors);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Mat::Converter::arg(0, &img, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Size::Converter::optArg(1, &winStride, info) ||
			Size::Converter::optArg(2, &padding, info) ||
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2i>::optArg(3, &locations, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1) && !FF_IS_INSTANCE(Size::constructor, info[1]->ToObject());
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[1]->ToObject();
		return (
			Size::Converter::optProp(&winStride, "winStride", opts) ||
			Size::Converter::optProp(&padding, "padding", opts) ||
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2i>::optProp(&locations, "locations", opts)
		);
	}
};

NAN_METHOD(HOGDescriptor::Compute) {
	ComputeWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("HOGDescriptor::Compute", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(HOGDescriptor::ComputeAsync) {
	ComputeWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("HOGDescriptor::ComputeAsync", ComputeWorker, worker);
}


struct HOGDescriptor::ComputeGradientWorker : public SimpleWorker {
public:
	cv::HOGDescriptor self;
	ComputeGradientWorker(cv::HOGDescriptor self) {
		this->self = self;
	}

	cv::Mat img;
	cv::Size2d paddingTL = cv::Size2d();
	cv::Size2d paddingBR = cv::Size2d();

	cv::Mat grad;
	cv::Mat angleOfs;

	const char* execute() {
		self.computeGradient(img, grad, angleOfs, paddingTL, paddingBR);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("grad").ToLocalChecked(), Mat::Converter::wrap(grad));
		Nan::Set(ret, Nan::New("angleOfs").ToLocalChecked(), Mat::Converter::wrap(angleOfs));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &img, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Size::Converter::optArg(1, &paddingTL, info) ||
			Size::Converter::optArg(2, &paddingBR, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[1]->ToObject();
		return (
			Size::Converter::optProp(&paddingTL, "paddingTL", opts) ||
			Size::Converter::optProp(&paddingBR, "paddingBR", opts)
			);
	}
};

NAN_METHOD(HOGDescriptor::ComputeGradient) {
	ComputeGradientWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("HOGDescriptor::ComputeGradient", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(HOGDescriptor::ComputeGradientAsync) {
	ComputeGradientWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("HOGDescriptor::ComputeGradientAsync", ComputeGradientWorker, worker);
}


struct HOGDescriptor::DetectWorker : public SimpleWorker {
public:
	cv::HOGDescriptor self;
	DetectWorker(cv::HOGDescriptor self) {
		this->self = self;
	}

	cv::Mat img;
	double hitThreshold = 0;
	cv::Size2d winStride = cv::Size2d();
	cv::Size2d padding = cv::Size2d();
	std::vector<cv::Point> searchLocations;

	std::vector<cv::Point> foundLocations;
	std::vector<double> weights;

	const char* execute() {
		self.detect(img, foundLocations, weights, hitThreshold, winStride, padding, searchLocations);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("foundLocations").ToLocalChecked(), ObjectArrayConverter<Point2, cv::Point2d, cv::Point>::wrap(foundLocations));
		Nan::Set(ret, Nan::New("weights").ToLocalChecked(), DoubleArrayConverter::wrap(weights));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &img, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(1, &hitThreshold, info) ||
			Size::Converter::optArg(2, &winStride, info) ||
			Size::Converter::optArg(3, &padding, info) ||
			ObjectArrayConverter<Point, cv::Point2d, cv::Point>::optArg(4, &searchLocations, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[1]->ToObject();
		return (
			DoubleConverter::optProp(&hitThreshold, "hitThreshold", opts) ||
			Size::Converter::optProp(&winStride, "winStride", opts) ||
			Size::Converter::optProp(&padding, "padding", opts) ||
			ObjectArrayConverter<Point, cv::Point2d, cv::Point>::optProp(&searchLocations, "searchLocations", opts)
		);
	}
};

NAN_METHOD(HOGDescriptor::Detect) {
	DetectWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("HOGDescriptor::Detect", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(HOGDescriptor::DetectAsync) {
	DetectWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("HOGDescriptor::DetectAsync", DetectWorker, worker);
}


struct HOGDescriptor::DetectROIWorker : public SimpleWorker {
public:
	cv::HOGDescriptor self;
	DetectROIWorker(cv::HOGDescriptor self) {
		this->self = self;
	}

	cv::Mat img;
	std::vector<cv::Point> locations;
	double hitThreshold = 0;
	cv::Size2d winStride = cv::Size2d();
	cv::Size2d padding = cv::Size2d();

	std::vector<cv::Point> foundLocations;
	std::vector<double> confidences;

	const char* execute() {
		self.detectROI(img, locations, foundLocations, confidences, hitThreshold, winStride, padding);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("foundLocations").ToLocalChecked(), ObjectArrayConverter<Point, cv::Point2d, cv::Point>::wrap(foundLocations));
		Nan::Set(ret, Nan::New("confidences").ToLocalChecked(), DoubleArrayConverter::wrap(confidences));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &img, info) ||
			ObjectArrayConverter<Point, cv::Point2d, cv::Point>::arg(1, &locations, info)
			);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(2, &hitThreshold, info) ||
			Size::Converter::optArg(3, &winStride, info) ||
			Size::Converter::optArg(4, &padding, info)
			);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(2);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[2]->ToObject();
		return (
			DoubleConverter::optProp(&hitThreshold, "hitThreshold", opts) ||
			Size::Converter::optProp(&winStride, "winStride", opts) ||
			Size::Converter::optProp(&padding, "padding", opts)
			);
	}
};

NAN_METHOD(HOGDescriptor::DetectROI) {
	DetectROIWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("HOGDescriptor::DetectROI", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(HOGDescriptor::DetectROIAsync) {
	DetectROIWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("HOGDescriptor::DetectROIAsync", DetectROIWorker, worker);
}


struct HOGDescriptor::DetectMultiScaleWorker : public SimpleWorker {
public:
	cv::HOGDescriptor self;
	DetectMultiScaleWorker(cv::HOGDescriptor self) {
		this->self = self;
	}

	cv::Mat img;
	double hitThreshold = 0;
	cv::Size2d winStride = cv::Size2d();
	cv::Size2d padding = cv::Size2d();
	double scale = 1.05;
	double finalThreshold = 2.0;
	bool useMeanshiftGrouping = false;

	std::vector<cv::Rect> foundLocations;
	std::vector<double> foundWeights;


	const char* execute() {
		self.detectMultiScale(img, foundLocations, foundWeights, hitThreshold, winStride, padding, scale, finalThreshold, useMeanshiftGrouping);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("foundLocations").ToLocalChecked(), ObjectArrayConverter<Rect, cv::Rect2d, cv::Rect>::wrap(foundLocations));
		Nan::Set(ret, Nan::New("foundWeights").ToLocalChecked(), DoubleArrayConverter::wrap(foundWeights));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &img, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(1, &hitThreshold, info) ||
			Size::Converter::optArg(2, &winStride, info) ||
			Size::Converter::optArg(3, &padding, info) ||
			DoubleConverter::optArg(4, &scale, info) ||
			DoubleConverter::optArg(5, &finalThreshold, info) ||
			BoolConverter::optArg(6, &useMeanshiftGrouping, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[1]->ToObject();
		return (
			DoubleConverter::optProp(&hitThreshold, "hitThreshold", opts) ||
			Size::Converter::optProp(&winStride, "winStride", opts) ||
			Size::Converter::optProp(&padding, "padding", opts) ||
			DoubleConverter::optProp(&scale, "scale", opts) ||
			DoubleConverter::optProp(&finalThreshold, "finalThreshold", opts) ||
			BoolConverter::optProp(&useMeanshiftGrouping, "useMeanshiftGrouping", opts)
		);
	}
};

NAN_METHOD(HOGDescriptor::DetectMultiScale) {
	DetectMultiScaleWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("HOGDescriptor::DetectMultiScale", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(HOGDescriptor::DetectMultiScaleAsync) {
	DetectMultiScaleWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("HOGDescriptor::DetectMultiScaleAsync", DetectMultiScaleWorker, worker);
}


struct HOGDescriptor::DetectMultiScaleROIWorker : public SimpleWorker {
public:
	cv::HOGDescriptor self;
	DetectMultiScaleROIWorker(cv::HOGDescriptor self) {
		this->self = self;
	}

	cv::Mat img;
	std::vector<cv::DetectionROI> locations;
	double hitThreshold = 0;
	int groupThreshold = 0;

	std::vector<cv::Rect> foundLocations;

	const char* execute() {
		self.detectMultiScaleROI(img, foundLocations, locations, hitThreshold, groupThreshold);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return ObjectArrayConverter<Rect, cv::Rect2d, cv::Rect>::wrap(foundLocations);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &img, info) ||
			ObjectArrayConverter<DetectionROI, cv::DetectionROI>::arg(1, &locations, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(2, &hitThreshold, info) ||
			IntConverter::optArg(3, &groupThreshold, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(2);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[2]->ToObject();
		return (
			DoubleConverter::optProp(&hitThreshold, "hitThreshold", opts) ||
			IntConverter::optProp(&groupThreshold, "groupThreshold", opts)
		);
	}
};

NAN_METHOD(HOGDescriptor::DetectMultiScaleROI) {
	DetectMultiScaleROIWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("HOGDescriptor::DetectMultiScaleROI", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(HOGDescriptor::DetectMultiScaleROIAsync) {
	DetectMultiScaleROIWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("HOGDescriptor::DetectMultiScaleROIAsync", DetectMultiScaleROIWorker, worker);
}

struct HOGDescriptor::GroupRectanglesWorker : public SimpleWorker {
public:
	cv::HOGDescriptor self;
	GroupRectanglesWorker(cv::HOGDescriptor self) {
		this->self = self;
	}

	std::vector<cv::Rect> rectList;
	std::vector<double> weights;
	int groupThreshold;
	double eps;


	const char* execute() {
		self.groupRectangles(rectList, weights, groupThreshold, eps);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			ObjectArrayConverter<Rect, cv::Rect2d, cv::Rect>::arg(0, &rectList, info) ||
			DoubleArrayConverter::arg(1, &weights, info) ||
			IntConverter::arg(2, &groupThreshold, info) ||
			DoubleConverter::arg(3, &eps, info)
		);
	}
};

NAN_METHOD(HOGDescriptor::GroupRectangles) {
	GroupRectanglesWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("HOGDescriptor::GroupRectangles", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(HOGDescriptor::GroupRectanglesAsync) {
	GroupRectanglesWorker worker(HOGDescriptor::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("HOGDescriptor::GroupRectanglesAsync", GroupRectanglesWorker, worker);
}


NAN_METHOD(HOGDescriptor::GetDaimlerPeopleDetector) {
	std::vector<float> detector = cv::HOGDescriptor::getDaimlerPeopleDetector();
	FF_RETURN(FloatArrayConverter::wrap(detector));
}

NAN_METHOD(HOGDescriptor::GetDefaultPeopleDetector) {
	std::vector<float> detector = cv::HOGDescriptor::getDefaultPeopleDetector();
	FF_RETURN(FloatArrayConverter::wrap(detector));
}

NAN_METHOD(HOGDescriptor::CheckDetectorSize) {
	FF_RETURN(Nan::New(HOGDescriptor::Converter::unwrap(info.This()).checkDetectorSize()));
}

NAN_METHOD(HOGDescriptor::SetSVMDetector) {
	FF_METHOD_CONTEXT("SetSVMDetector");
	std::vector<float> detector;
	if (!FF_HAS_ARG(0) || !FloatArrayConverter::unwrap(&detector, info[0])) {
		FF_THROW("expected detector to be an Array of type Number");
	}

	HOGDescriptor::Converter::unwrap(info.This()).setSVMDetector(detector);
}

NAN_METHOD(HOGDescriptor::Save) {
	FF_METHOD_CONTEXT("HOGDescriptor::Save");
	FF_ARG_STRING(0, std::string path);
	FF_UNWRAP(info.This(), HOGDescriptor)->hog.save(path);
}

NAN_METHOD(HOGDescriptor::Load) {
	FF_METHOD_CONTEXT("HOGDescriptor::Load");
	FF_ARG_STRING(0, std::string path);
	FF_UNWRAP(info.This(), HOGDescriptor)->hog.load(path);
}