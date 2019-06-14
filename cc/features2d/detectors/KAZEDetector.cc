#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "KAZEDetector.h"

Nan::Persistent<v8::FunctionTemplate> KAZEDetector::constructor;

NAN_MODULE_INIT(KAZEDetector::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(KAZEDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
	constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("KAZEDetector").ToLocalChecked());
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, Nan::New("extended").ToLocalChecked(), extended_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("upright").ToLocalChecked(), upright_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("threshold").ToLocalChecked(), threshold_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaves").ToLocalChecked(), nOctaves_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaveLayers").ToLocalChecked(), nOctaveLayers_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("diffusivity").ToLocalChecked(), diffusivity_getter);

	Nan::Set(target, Nan::New("KAZEDetector").ToLocalChecked(), FF::getFunction(ctor));
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
	DiffusivityType::init(target);
#endif
};

NAN_METHOD(KAZEDetector::New) {
	NewBinding().construct(info);
}

#endif