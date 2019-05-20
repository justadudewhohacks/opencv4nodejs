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

	target->Set(FF_NEW_STRING("BackgroundSubtractorMOG2"), FF::getFunction(ctor));
};

NAN_METHOD(BackgroundSubtractorMOG2::New) {
	FF_ASSERT_CONSTRUCT_CALL(BackgroundSubtractorKNN);
	FF::TryCatch tryCatch;
	BackgroundSubtractorMOG2::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("BackgroundSubtractorMOG2::New");
		tryCatch.throwNew(err);
		return;
	}

	BackgroundSubtractorMOG2* self = new BackgroundSubtractorMOG2();
	self->subtractor = cv::createBackgroundSubtractorMOG2((int)worker.history, worker.varThreshold, worker.detectShadows);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}