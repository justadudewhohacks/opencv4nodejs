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

  target->Set(Nan::New("SIFTDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(SIFTDetector::New) {
	FF_METHOD_CONTEXT("SIFTDetector::New");
	SIFTDetector* self = new SIFTDetector();

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

	FF_GET_INT_IFDEF(optArgs, self->nFeatures, "nFeatures", 0);
	FF_GET_INT_IFDEF(optArgs, self->nOctaveLayers, "nOctaveLayers", 3);
	FF_GET_NUMBER_IFDEF(optArgs, self->contrastThreshold, "contrastThreshold", 0.04);
	FF_GET_NUMBER_IFDEF(optArgs, self->edgeThreshold, "edgeThreshold", 10);
	FF_GET_NUMBER_IFDEF(optArgs, self->sigma, "sigma", 1.6);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(0, self->nFeatures, self->nFeatures);
		FF_ARG_INT_IFDEF(1, self->nOctaveLayers, self->nOctaveLayers);
		FF_ARG_NUMBER_IFDEF(2, self->contrastThreshold, self->contrastThreshold);
		FF_ARG_NUMBER_IFDEF(3, self->edgeThreshold, self->edgeThreshold);
		FF_ARG_NUMBER_IFDEF(4, self->sigma, self->sigma);
	}

	self->Wrap(info.Holder());
	self->detector = cv::xfeatures2d::SIFT::create(
		self->nFeatures, 
		self->nOctaveLayers, 
		self->contrastThreshold, 
		self->edgeThreshold, 
		self->sigma
	);
  FF_RETURN(info.Holder());
}

#endif // HAVE_XFEATURES2D