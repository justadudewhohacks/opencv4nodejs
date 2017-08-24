#include "CascadeClassifier.h"
#include "Mat.h"
#include "Rect.h"

Nan::Persistent<v8::FunctionTemplate> CascadeClassifier::constructor;

NAN_MODULE_INIT(CascadeClassifier::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(CascadeClassifier::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF_V8STRING("CascadeClassifier"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetPrototypeMethod(ctor, "detectMultiScale", DetectMultiScale);

	target->Set(FF_V8STRING("CascadeClassifier"), ctor->GetFunction());
};

NAN_METHOD(CascadeClassifier::New) {
	if (!info[0]->IsString()) {
		return Nan::ThrowError("CascadeClassifier::New - expected arg0 to be path to a cascade.xml file");
	}
	CascadeClassifier* self = new CascadeClassifier();
	self->classifier = cv::CascadeClassifier(FF_JS_VAL_TO_STRING(info[0]));
	if (self->classifier.empty()) {
		return Nan::ThrowError("CascadeClassifier::New - failed to load cascade.xml file");
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

NAN_METHOD(CascadeClassifier::DetectMultiScale) {
	FF_REQUIRE_ARGS_OBJ("CascadeClassifier::DetectMultiScale");

	cv::Mat image;
	FF_DESTRUCTURE_JSOBJ_REQUIRED(args, image, Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat);

	double scaleFactor = 1.1;
	int minNeighbors = 3, flags = 0;
	bool outputRejectLevels = false;
	cv::Size minSize = cv::Size(), maxSize = cv::Size();
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, scaleFactor, IsNumber, NumberValue);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, minNeighbors, IsUint32, Uint32Value);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, flags, IsUint32, Uint32Value);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, outputRejectLevels, IsBoolean, BooleanValue);
	if (FF_HAS_JS_PROP(args, minSize)) {
		FF_DESTRUCTURE_JSOBJ_REQUIRED(args, minSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size);
	}
	if (FF_HAS_JS_PROP(args, maxSize)) {
		FF_DESTRUCTURE_JSOBJ_REQUIRED(args, maxSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size);
	}

	v8::Local<v8::Object> ret = Nan::New<v8::Object>();
	std::vector<cv::Rect> objects;
	std::vector<int> rejectLevels;
	std::vector<int> numDetections;
	std::vector<double> levelWeights;
	CascadeClassifier* self = FF_UNWRAP(info.This(), CascadeClassifier);
	if (outputRejectLevels) {
		self->classifier.detectMultiScale(
			image, 
			objects, 
			rejectLevels, 
			levelWeights, 
			scaleFactor, 
			minNeighbors, 
			flags, 
			minSize, 
			maxSize, 
			outputRejectLevels
		);

		v8::Local<v8::Array> jsRejectLevels = Nan::New<v8::Array>(rejectLevels.size());
		v8::Local<v8::Array> jsLevelWeights = Nan::New<v8::Array>(levelWeights.size());
		for (int i = 0; i < rejectLevels.size(); i++) {
			jsRejectLevels->Set(i, Nan::New(rejectLevels.at(i)));
		}
		for (int i = 0; i < levelWeights.size(); i++) {
			jsLevelWeights->Set(i, Nan::New(levelWeights.at(i)));
		}
		Nan::Set(ret, FF_V8STRING("rejectLevels"), jsRejectLevels);
		Nan::Set(ret, FF_V8STRING("levelWeights"), jsLevelWeights);
	}
	else {
		self->classifier.detectMultiScale(
			image,
			objects,
			numDetections,
			scaleFactor,
			minNeighbors,
			flags,
			minSize,
			maxSize
		);

		v8::Local<v8::Array> jsNumDetections = Nan::New<v8::Array>(numDetections.size());
		for (int i = 0; i < numDetections.size(); i++) {
			jsNumDetections->Set(i, Nan::New(numDetections.at(i)));
		}
		Nan::Set(ret, FF_V8STRING("numDetections"), jsNumDetections);
	}

	v8::Local<v8::Array> jsObjects = Nan::New<v8::Array>(objects.size());
	for (int i = 0; i < objects.size(); i++) {
		v8::Local<v8::Object> jsObject = FF_NEW(Rect::constructor);
		FF_UNWRAP(jsObject, Rect)->rect = objects.at(i);
		jsObjects->Set(i, jsObject);
	}
	Nan::Set(ret, FF_V8STRING("objects"), jsObjects);
	info.GetReturnValue().Set(ret);
};
