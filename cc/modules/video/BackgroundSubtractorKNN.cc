#include "BackgroundSubtractorKNN.h"

Nan::Persistent<v8::FunctionTemplate> BackgroundSubtractorKNN::constructor;

NAN_MODULE_INIT(BackgroundSubtractorKNN::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(BackgroundSubtractorKNN::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	BackgroundSubtractor::Init(ctor);
	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("BackgroundSubtractorKNN"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("history"), GetHistory);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("dist2Threshold"), GetDist2Threshold);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("detectShadows"), GetDetectShadows);

	target->Set(FF_NEW_STRING("BackgroundSubtractorKNN"), ctor->GetFunction());
};

NAN_METHOD(BackgroundSubtractorKNN::New) {
	FF_METHOD_CONTEXT("BackgroundSubtractorKNN::New");

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

	FF_GET_UINT_IFDEF(optArgs, uint history, "history", 500);
	FF_GET_NUMBER_IFDEF(optArgs, double dist2Threshold, "dist2Threshold", 400);
	FF_GET_BOOL_IFDEF(optArgs, bool detectShadows, "detectShadows", true);
	if (!hasOptArgsObj) {
		FF_ARG_UINT_IFDEF(0, history, history);
		FF_ARG_NUMBER_IFDEF(1, dist2Threshold, dist2Threshold);
		FF_ARG_BOOL_IFDEF(2, detectShadows, detectShadows);
	}

	BackgroundSubtractorKNN* self = new BackgroundSubtractorKNN();
	self->subtractor = cv::createBackgroundSubtractorKNN((int)history, dist2Threshold, detectShadows);
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};