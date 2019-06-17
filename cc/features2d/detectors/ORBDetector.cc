#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

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

	Nan::Set(target, Nan::New("ORBDetector").ToLocalChecked(), FF::getFunction(ctor));
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
	ScoreType::init(target);
#endif
};

NAN_METHOD(ORBDetector::New) {
	NewBinding().construct(info);
}

#endif