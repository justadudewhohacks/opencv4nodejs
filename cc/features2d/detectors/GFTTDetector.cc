#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "GFTTDetector.h"

Nan::Persistent<v8::FunctionTemplate> GFTTDetector::constructor;

NAN_MODULE_INIT(GFTTDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(GFTTDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
	constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("GFTTDetector").ToLocalChecked());
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, Nan::New("maxFeatures").ToLocalChecked(), maxFeatures_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("qualityLevel").ToLocalChecked(), qualityLevel_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("minDistance").ToLocalChecked(), minDistance_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("blockSize").ToLocalChecked(), blockSize_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("harrisDetector").ToLocalChecked(), harrisDetector_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("k").ToLocalChecked(), k_getter);

	Nan::Set(target,Nan::New("GFTTDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(GFTTDetector::New) {
	FF::TryCatch tryCatch("GFTTDetector::New");
	FF_ASSERT_CONSTRUCT_CALL();
	GFTTDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	GFTTDetector* self = new GFTTDetector();
	self->self = cv::GFTTDetector::create(worker.maxFeatures, worker.qualityLevel, worker.minDistance, worker.blockSize, worker.harrisDetector, worker.k);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

#endif
