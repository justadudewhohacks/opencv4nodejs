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

  target->Set(Nan::New("SimpleBlobDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(SimpleBlobDetector::New) {
	FF_ASSERT_CONSTRUCT_CALL(SimpleBlobDetector);
	FF::TryCatch tryCatch;

	cv::SimpleBlobDetector::Params params;
	if (SimpleBlobDetectorParams::Converter::arg(0, &params, info)) {
		tryCatch.throwNew(tryCatch.formatCatchedError("SimpleBlobDetector::New"));
		return;
	}

	SimpleBlobDetector* self = new SimpleBlobDetector();
	self->Wrap(info.Holder());
	self->detector = cv::SimpleBlobDetector::create(params);
  info.GetReturnValue().Set(info.Holder());
}
