#include "HOGDescriptor.h"
#include "Mat.h"
#include "Rect.h"
#include "Point.h"
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

	Nan::SetPrototypeMethod(ctor, "compute", Compute);
	Nan::SetPrototypeMethod(ctor, "computeAsync", ComputeAsync);

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