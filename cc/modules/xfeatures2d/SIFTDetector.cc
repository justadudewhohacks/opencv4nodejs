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
	FF::TryCatch tryCatch("SIFTDetector::New");
	FF_ASSERT_CONSTRUCT_CALL();
	SIFTDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	SIFTDetector* self = new SIFTDetector();
	self->nFeatures = worker.nFeatures;
	self->nOctaveLayers = worker.nOctaveLayers;
	self->contrastThreshold = worker.contrastThreshold;
	self->edgeThreshold = worker.edgeThreshold;
	self->sigma = worker.sigma;
	try {
		self->detector = cv::xfeatures2d::SIFT::create(
			worker.nFeatures,
			worker.nOctaveLayers,
			worker.contrastThreshold,
			worker.edgeThreshold,
			worker.sigma
		);
	} catch (std::exception &e) {
		return tryCatch.throwError(e.what());
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

#endif // HAVE_XFEATURES2D
