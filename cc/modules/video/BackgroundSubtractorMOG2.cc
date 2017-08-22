#include "BackgroundSubtractorMOG2.h"

Nan::Persistent<v8::FunctionTemplate> BackgroundSubtractorMOG2::constructor;

NAN_MODULE_INIT(BackgroundSubtractorMOG2::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(BackgroundSubtractorMOG2::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	BackgroundSubtractor::Init(ctor);
	constructor.Reset(ctor);
	ctor->SetClassName(FF_V8STRING("BackgroundSubtractorMOG2"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF_V8STRING("history"), GetHistory);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("varThreshold"), GetVarThreshold);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("detectShadows"), GetDetectShadows);

	target->Set(FF_V8STRING("BackgroundSubtractorMOG2"), ctor->GetFunction());
};

NAN_METHOD(BackgroundSubtractorMOG2::New) {
	BackgroundSubtractorMOG2* self = new BackgroundSubtractorMOG2();
	int history = 500; 
	double varThreshold = 16;
	bool detectShadows = true;
	if (info.Length() > 0) {
		FF_REQUIRE_ARGS_OBJ("BackgroundSubtractorMOG2::New");
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, history, IsUint32, Uint32Value);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, varThreshold, IsNumber, NumberValue);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, history, IsBoolean, BooleanValue);
	}
	self->subtractor = cv::createBackgroundSubtractorMOG2(history, varThreshold, detectShadows);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};