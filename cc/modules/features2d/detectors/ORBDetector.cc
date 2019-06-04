#include "ORBDetector.h"

Nan::Persistent<v8::FunctionTemplate> ORBDetector::constructor;

NAN_MODULE_INIT(ORBDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(ORBDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("ORBDetector").ToLocalChecked());

	Nan::SetAccessor(instanceTemplate, Nan::New("maxFeatures").ToLocalChecked(), maxFeatures_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("scaleFactor").ToLocalChecked(), scaleFactor_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("nLevels").ToLocalChecked(), nLevels_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("edgeThreshold").ToLocalChecked(), edgeThreshold_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("firstLevel").ToLocalChecked(), firstLevel_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("WTA_K").ToLocalChecked(), WTA_K_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("scoreType").ToLocalChecked(), scoreType_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("patchSize").ToLocalChecked(), patchSize_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("fastThreshold").ToLocalChecked(), fastThreshold_getter);

	Nan::Set(target,Nan::New("ORBDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(ORBDetector::New) {
	FF::TryCatch tryCatch("ORBDetector::New");
	FF_ASSERT_CONSTRUCT_CALL();
	ORBDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	ORBDetector* self = new ORBDetector();
	self->self = cv::ORB::create(worker.maxFeatures, worker.scaleFactor, worker.nLevels, worker.edgeThreshold, worker.firstLevel, worker.WTA_K, worker.scoreType, worker.patchSize, worker.fastThreshold);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}