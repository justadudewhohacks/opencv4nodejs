#include "BackgroundSubtractorKNN.h"

Nan::Persistent<v8::FunctionTemplate> BackgroundSubtractorKNN::constructor;

NAN_MODULE_INIT(BackgroundSubtractorKNN::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(BackgroundSubtractorKNN::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	BackgroundSubtractor::Init(ctor);
	constructor.Reset(ctor);
	ctor->SetClassName(FF_V8STRING("BackgroundSubtractorKNN"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF_V8STRING("history"), GetHistory);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("dist2Threshold"), GetDist2Threshold);
	Nan::SetAccessor(instanceTemplate, FF_V8STRING("detectShadows"), GetDetectShadows);

	target->Set(FF_V8STRING("BackgroundSubtractorKNN"), ctor->GetFunction());
};

NAN_METHOD(BackgroundSubtractorKNN::New) {
	BackgroundSubtractorKNN* self = new BackgroundSubtractorKNN();
	int history = 500;
	double dist2Threshold = 400;
	bool detectShadows = true;
	if (info.Length() > 0) {
		FF_REQUIRE_ARGS_OBJ("BackgroundSubtractorKNN::New");
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, history, IsUint32, Uint32Value);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, dist2Threshold, IsNumber, NumberValue);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, history, IsBoolean, BooleanValue);
	}
	self->subtractor = cv::createBackgroundSubtractorKNN(history, dist2Threshold, detectShadows);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};