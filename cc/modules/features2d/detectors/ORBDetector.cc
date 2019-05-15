#include "ORBDetector.h"

Nan::Persistent<v8::FunctionTemplate> ORBDetector::constructor;

NAN_MODULE_INIT(ORBDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(ORBDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("ORBDetector").ToLocalChecked());

	Nan::SetAccessor(instanceTemplate, Nan::New("nfeatures").ToLocalChecked(), ORBDetector::GetNFeatures);
	Nan::SetAccessor(instanceTemplate, Nan::New("scaleFactor").ToLocalChecked(), ORBDetector::GetScaleFactor);
	Nan::SetAccessor(instanceTemplate, Nan::New("nlevels").ToLocalChecked(), ORBDetector::GetNlevels);
	Nan::SetAccessor(instanceTemplate, Nan::New("edgeThreshold").ToLocalChecked(), ORBDetector::GetEdgeThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("firstLevel").ToLocalChecked(), ORBDetector::GetFirstLevel);
	Nan::SetAccessor(instanceTemplate, Nan::New("WTA_K").ToLocalChecked(), ORBDetector::GetWTA_K);
	Nan::SetAccessor(instanceTemplate, Nan::New("scoreType").ToLocalChecked(), ORBDetector::GetScoreType);
	Nan::SetAccessor(instanceTemplate, Nan::New("patchSize").ToLocalChecked(), ORBDetector::GetPatchSize);
	Nan::SetAccessor(instanceTemplate, Nan::New("fastThreshold").ToLocalChecked(), ORBDetector::GetFastThreshold);

  target->Set(Nan::New("ORBDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(ORBDetector::New) {
	FF_ASSERT_CONSTRUCT_CALL(ORBDetector);
	FF::TryCatch tryCatch;
	ORBDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("ORBDetector::New");
		tryCatch.throwNew(err);
		return;
	}

	ORBDetector* self = new ORBDetector();
	self->detector = cv::ORB::create(worker.nfeatures, worker.scaleFactor, worker.nlevels, worker.edgeThreshold, worker.firstLevel, worker.WTA_K, worker.scoreType, worker.patchSize, worker.fastThreshold);
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
}