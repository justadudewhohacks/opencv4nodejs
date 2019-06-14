#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XFEATURES2D

#include "SIFTDetector.h"

Nan::Persistent<v8::FunctionTemplate> SIFTDetector::constructor;

NAN_MODULE_INIT(SIFTDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SIFTDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SIFTDetector").ToLocalChecked());

	Nan::SetAccessor(instanceTemplate, Nan::New("nFeatures").ToLocalChecked(), nFeatures_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaveLayers").ToLocalChecked(), nOctaveLayers_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("contrastThreshold").ToLocalChecked(), contrastThreshold_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("edgeThreshold").ToLocalChecked(), edgeThreshold_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("sigma").ToLocalChecked(), sigma_getter);

  Nan::Set(target,Nan::New("SIFTDetector").ToLocalChecked(), FF::getFunction(ctor));
};


NAN_METHOD(SIFTDetector::New) {
	constructorBinding<Constructor>(info);
}

#endif // HAVE_OPENCV_XFEATURES2D
