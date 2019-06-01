#include "BackgroundSubtractorKNN.h"

Nan::Persistent<v8::FunctionTemplate> BackgroundSubtractorKNN::constructor;

NAN_MODULE_INIT(BackgroundSubtractorKNN::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(BackgroundSubtractorKNN::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	BackgroundSubtractor::Init(ctor);
	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("BackgroundSubtractorKNN"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF::newString("history"), GetHistory);
	Nan::SetAccessor(instanceTemplate, FF::newString("dist2Threshold"), GetDist2Threshold);
	Nan::SetAccessor(instanceTemplate, FF::newString("detectShadows"), GetDetectShadows);

	Nan::Set(target,FF::newString("BackgroundSubtractorKNN"), FF::getFunction(ctor));
};

NAN_METHOD(BackgroundSubtractorKNN::New) {
	FF::TryCatch tryCatch("BackgroundSubtractor::New");
	FF_ASSERT_CONSTRUCT_CALL();
	BackgroundSubtractorKNN::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	BackgroundSubtractorKNN* self = new BackgroundSubtractorKNN();
	self->subtractor = cv::createBackgroundSubtractorKNN((int)worker.history, worker.dist2Threshold, worker.detectShadows);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}