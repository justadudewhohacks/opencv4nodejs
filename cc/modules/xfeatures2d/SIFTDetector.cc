#ifdef HAVE_XFEATURES2D

#include "SIFTDetector.h"

Nan::Persistent<v8::FunctionTemplate> SIFTDetector::constructor;

NAN_MODULE_INIT(SIFTDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SIFTDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SIFTDetector").ToLocalChecked());

	Nan::SetAccessor(instanceTemplate, Nan::New("nFeatures").ToLocalChecked(), SIFTDetector::GetNFeatures);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaveLayers").ToLocalChecked(), SIFTDetector::GeNOctaveLayers);
	Nan::SetAccessor(instanceTemplate, Nan::New("contrastThreshold").ToLocalChecked(), SIFTDetector::GetContrastThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("edgeThreshold").ToLocalChecked(), SIFTDetector::GetEdgeThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("sigma").ToLocalChecked(), SIFTDetector::GetSigma);

  Nan::Set(target,Nan::New("SIFTDetector").ToLocalChecked(), FF::getFunction(ctor));
};


NAN_METHOD(SIFTDetector::New) {
	FF_ASSERT_CONSTRUCT_CALL(SIFTDetector);
	FF::TryCatch tryCatch;
	SIFTDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("SIFTDetector::New");
		tryCatch.throwNew(err);
		return;
	}

	SIFTDetector* self = new SIFTDetector();
	self->Wrap(info.Holder());
	self->nFeatures = worker.nFeatures;
	self->nOctaveLayers = worker.nOctaveLayers;
	self->contrastThreshold = worker.contrastThreshold;
	self->edgeThreshold = worker.edgeThreshold;
	self->sigma = worker.sigma;
	self->detector = cv::xfeatures2d::SIFT::create(
		worker.nFeatures,
		worker.nOctaveLayers,
		worker.contrastThreshold,
		worker.edgeThreshold,
		worker.sigma
	);
	info.GetReturnValue().Set(info.Holder());
}

#endif // HAVE_XFEATURES2D
