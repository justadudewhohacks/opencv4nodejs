#include "HOGDescriptor.h"
#include "Mat.h"
#include "Rect.h"
#include "Point.h"

Nan::Persistent<v8::FunctionTemplate> HOGDescriptor::constructor;

NAN_MODULE_INIT(HOGDescriptor::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(HOGDescriptor::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF_V8STRING("HOGDescriptor"));
	instanceTemplate->SetInternalFieldCount(1);
	
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("winSize"), winSize);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("blockSize"), blockSize);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("blockStride"), blockStride);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("cellSize"), cellSize);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("nbins"), nbins);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("derivAperture"), derivAperture);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("histogramNormType"), histogramNormType);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("nlevels"), nlevels);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("winSigma"), winSigma);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("L2HysThreshold"), L2HysThreshold);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("gammaCorrection"), gammaCorrection);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("signedGradient"), signedGradient);

	Nan::SetPrototypeMethod(ctor, "compute", Compute);

	target->Set(FF_V8STRING("HOGDescriptor"), ctor->GetFunction());
};

NAN_METHOD(HOGDescriptor::New) {
	HOGDescriptor* self = new HOGDescriptor();
	cv::Size winSize = cv::Size(64, 128), blockSize = cv::Size(16, 16), blockStride = cv::Size(8, 8), cellSize = cv::Size(8, 8);
	int nbins = 9, derivAperture = 1;
	int histogramNormType = cv::HOGDescriptor::L2Hys;
	int nlevels = cv::HOGDescriptor::DEFAULT_NLEVELS;
	double winSigma = -1, L2HysThreshold = 0.2;
	bool gammaCorrection = false, signedGradient = false;

	if (info[0]->IsObject()) {
		FF_REQUIRE_ARGS_OBJ("HOGDescriptor::New");
		FF_DESTRUCTURE_JSOBJ_IFDEF(args, winSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size);
		FF_DESTRUCTURE_JSOBJ_IFDEF(args, blockSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size);
		FF_DESTRUCTURE_JSOBJ_IFDEF(args, blockStride, Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size);
		FF_DESTRUCTURE_JSOBJ_IFDEF(args, cellSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, nbins, IsUint32, Uint32Value);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, derivAperture, IsUint32, Uint32Value);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, histogramNormType, IsUint32, Uint32Value);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, nlevels, IsUint32, Uint32Value);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, winSigma, IsNumber,NumberValue);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, L2HysThreshold, IsNumber, NumberValue);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, gammaCorrection, IsBoolean, BooleanValue);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, signedGradient, IsBoolean, BooleanValue);
	}

	self->hog = cv::HOGDescriptor(
		winSize, 
		blockSize, 
		blockStride,
		cellSize, 
		nbins, 
		derivAperture, 
		winSigma,
		histogramNormType,
		L2HysThreshold,
		gammaCorrection,
		nlevels,
		signedGradient
	);

	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

NAN_METHOD(HOGDescriptor::Compute) {
	FF_REQUIRE_ARGS_OBJ("HOGDescriptor::Detect");

	cv::Mat img;
	FF_DESTRUCTURE_JSOBJ_REQUIRED(args, img, Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat);

	cv::Size winStride = cv::Size(), padding = cv::Size();
	FF_DESTRUCTURE_JSOBJ_IFDEF(args, winStride, Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size);
	FF_DESTRUCTURE_JSOBJ_IFDEF(args, padding, Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size);

	std::vector<cv::Point2i> locations; 
	if (FF_HAS_JS_PROP(args, locations)) {
		v8::Local<v8::Array> jsLocations;
		FF_GET_JSARR_REQUIRED(args, jsLocations, locations);
		Point::unpackJSPoint2Array(locations, jsLocations);
	}

	std::vector<float> descriptors;
	FF_UNWRAP(info.This(), HOGDescriptor)->hog.compute(
		img,
		descriptors,
		winStride,
		padding,
		locations
	);
	info.GetReturnValue().Set(FF::stdVecToJSArray<double>(descriptors));
};
