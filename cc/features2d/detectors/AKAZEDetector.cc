#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "AKAZEDetector.h"

Nan::Persistent<v8::FunctionTemplate> AKAZEDetector::constructor;

NAN_MODULE_INIT(AKAZEDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(AKAZEDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
	constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("AKAZEDetector").ToLocalChecked());
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, Nan::New("descriptorType").ToLocalChecked(), descriptorType_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("descriptorSize").ToLocalChecked(), descriptorSize_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("descriptorChannels").ToLocalChecked(), descriptorChannels_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("threshold").ToLocalChecked(), threshold_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaves").ToLocalChecked(), nOctaves_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaveLayers").ToLocalChecked(), nOctaveLayers_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("diffusivity").ToLocalChecked(), diffusivity_getter);

	Nan::Set(target,Nan::New("AKAZEDetector").ToLocalChecked(), FF::getFunction(ctor));
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
	DescriptorType::init(target);
#endif
};

NAN_METHOD(AKAZEDetector::New) {
	NewBinding().construct(info);
}

#endif