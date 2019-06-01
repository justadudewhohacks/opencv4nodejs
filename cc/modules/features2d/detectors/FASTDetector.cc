#include "FASTDetector.h"

Nan::Persistent<v8::FunctionTemplate> FASTDetector::constructor;

NAN_MODULE_INIT(FASTDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(FASTDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("FASTDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, Nan::New("threshold").ToLocalChecked(), FASTDetector::GetThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("nonmaxSuppression").ToLocalChecked(), FASTDetector::GetNonmaxSuppression);
	Nan::SetAccessor(instanceTemplate, Nan::New("type").ToLocalChecked(), FASTDetector::GetType);

  Nan::Set(target,Nan::New("FASTDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(FASTDetector::New) {
	FF::TryCatch tryCatch("FASTDetector::New");
	FF_ASSERT_CONSTRUCT_CALL();
	FASTDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	FASTDetector* self = new FASTDetector();
	self->detector = cv::FastFeatureDetector::create(
		worker.threshold,
		worker.nonmaxSuppression,
		worker.type
	);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}