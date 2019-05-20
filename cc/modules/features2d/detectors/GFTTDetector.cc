#include "GFTTDetector.h"

Nan::Persistent<v8::FunctionTemplate> GFTTDetector::constructor;

NAN_MODULE_INIT(GFTTDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(GFTTDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("GFTTDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, Nan::New("maxCorners").ToLocalChecked(), GFTTDetector::GetMaxFeatures);
	Nan::SetAccessor(instanceTemplate, Nan::New("qualityLevel").ToLocalChecked(), GFTTDetector::GetQualityLevel);
	Nan::SetAccessor(instanceTemplate, Nan::New("minDistance").ToLocalChecked(), GFTTDetector::GetMinDistance);
	Nan::SetAccessor(instanceTemplate, Nan::New("blockSize").ToLocalChecked(), GFTTDetector::GetBlockSize);
	Nan::SetAccessor(instanceTemplate, Nan::New("useHarrisDetector").ToLocalChecked(), GFTTDetector::GetUseHarrisDetector);
	Nan::SetAccessor(instanceTemplate, Nan::New("k").ToLocalChecked(), GFTTDetector::GetK);

  target->Set(Nan::New("GFTTDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(GFTTDetector::New) {
	FF_ASSERT_CONSTRUCT_CALL(GFTTDetector);
	FF::TryCatch tryCatch;
	GFTTDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("GFTTDetector::New");
		tryCatch.throwNew(err);
		return;
	}

	GFTTDetector* self = new GFTTDetector();
	self->detector = cv::GFTTDetector::create(worker.maxCorners, worker.qualityLevel, worker.minDistance, worker.blockSize, worker.useHarrisDetector, worker.k);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}
