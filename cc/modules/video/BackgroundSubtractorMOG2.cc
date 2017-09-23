#include "BackgroundSubtractorMOG2.h"

Nan::Persistent<v8::FunctionTemplate> BackgroundSubtractorMOG2::constructor;

NAN_MODULE_INIT(BackgroundSubtractorMOG2::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(BackgroundSubtractorMOG2::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	BackgroundSubtractor::Init(ctor);
	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("BackgroundSubtractorMOG2"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("history"), GetHistory);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("varThreshold"), GetVarThreshold);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("detectShadows"), GetDetectShadows);

	target->Set(FF_NEW_STRING("BackgroundSubtractorMOG2"), ctor->GetFunction());
};

NAN_METHOD(BackgroundSubtractorMOG2::New) {
	FF_METHOD_CONTEXT("BackgroundSubtractorMOG2::New");

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

	FF_GET_UINT_IFDEF(optArgs, uint history, "history", 500);
	FF_GET_NUMBER_IFDEF(optArgs, double varThreshold, "varThreshold", 16);
	FF_GET_BOOL_IFDEF(optArgs, bool detectShadows, "detectShadows", true);
	if (!hasOptArgsObj) {
		FF_ARG_UINT_IFDEF(0, history, history);
		FF_ARG_NUMBER_IFDEF(1, varThreshold, varThreshold);
		FF_ARG_BOOL_IFDEF(2, detectShadows, detectShadows);
	}

	BackgroundSubtractorMOG2* self = new BackgroundSubtractorMOG2();
	self->subtractor = cv::createBackgroundSubtractorMOG2((int)history, varThreshold, detectShadows);
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};