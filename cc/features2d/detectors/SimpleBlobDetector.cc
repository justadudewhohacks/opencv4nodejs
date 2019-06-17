#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

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

	Nan::Set(target,Nan::New("SimpleBlobDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(SimpleBlobDetector::New) {
	FF::TryCatch tryCatch("SimpleBlobDetector::New");
	FF_ASSERT_CONSTRUCT_CALL();

	cv::SimpleBlobDetector::Params params;
	if (SimpleBlobDetectorParams::Converter::arg(0, &params, info)) {
		return tryCatch.reThrow();
	}

	SimpleBlobDetector* self = new SimpleBlobDetector();
	self->Wrap(info.Holder());
	self->detector = cv::SimpleBlobDetector::create(params);
  info.GetReturnValue().Set(info.Holder());
}

#endif
