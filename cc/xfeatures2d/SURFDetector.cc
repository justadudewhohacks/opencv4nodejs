#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XFEATURES2D

#include "SURFDetector.h"

Nan::Persistent<v8::FunctionTemplate> SURFDetector::constructor;

NAN_MODULE_INIT(SURFDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SURFDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
	constructor.Reset(ctor);
	instanceTemplate->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("SURFDetector").ToLocalChecked());

	Nan::SetAccessor(instanceTemplate, Nan::New("hessianThreshold").ToLocalChecked(), hessianThreshold_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaves").ToLocalChecked(), nOctaves_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaveLayers").ToLocalChecked(), nOctaveLayers_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("extended").ToLocalChecked(), extended_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("upright").ToLocalChecked(), upright_getter);

  Nan::Set(target,Nan::New("SURFDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(SURFDetector::New) {
	constructorBinding<Constructor>(info);
}


#endif // HAVE_OPENCV_XFEATURES2D
