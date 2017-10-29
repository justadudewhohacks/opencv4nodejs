#include "SimpleBlobDetector.h"
#include "SimpleBlobDetectorParams.h"

Nan::Persistent<v8::FunctionTemplate> SimpleBlobDetector::constructor;

NAN_MODULE_INIT(SimpleBlobDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SimpleBlobDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	SimpleBlobDetectorParams::Init(target);
	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("SimpleBlobDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

  target->Set(Nan::New("SimpleBlobDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(SimpleBlobDetector::New) {
	FF_METHOD_CONTEXT("SimpleBlobDetector::New");

	FF_ARG_INSTANCE(
		0,
		cv::SimpleBlobDetector::Params params,
		SimpleBlobDetectorParams::constructor,
		FF_UNWRAP_SIMPLEBLOBDETECTORPARAMS_AND_GET
	);

	SimpleBlobDetector* self = new SimpleBlobDetector();
	self->Wrap(info.Holder());
	self->detector = cv::SimpleBlobDetector::create(params);
  FF_RETURN(info.Holder());
}