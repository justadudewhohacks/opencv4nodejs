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

	target->Set(FF_NEW_STRING("BackgroundSubtractorKNN"), FF::getFunction(ctor));
};

NAN_METHOD(BackgroundSubtractorKNN::New) {
	FF_ASSERT_CONSTRUCT_CALL(BackgroundSubtractorKNN);
	FF::TryCatch tryCatch;
	BackgroundSubtractorKNN::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("BackgroundSubtractorKNN::New");
		tryCatch.throwNew(err);
		return;
	}

	BackgroundSubtractorKNN* self = new BackgroundSubtractorKNN();
	self->subtractor = cv::createBackgroundSubtractorKNN((int)worker.history, worker.dist2Threshold, worker.detectShadows);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}