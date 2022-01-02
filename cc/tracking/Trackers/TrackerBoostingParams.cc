#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerBoostingParams.h"

Nan::Persistent<v8::FunctionTemplate> TrackerBoostingParams::constructor;

NAN_MODULE_INIT(TrackerBoostingParams::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerBoostingParams::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerBoostingParams"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF::newString("numClassifiers"), numClassifiers_getter, numClassifiers_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerOverlap"), samplerOverlap_getter, samplerOverlap_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerSearchFactor"), samplerSearchFactor_getter, samplerSearchFactor_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("iterationInit"), iterationInit_getter, iterationInit_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("featureSetNumFeatures"), featureSetNumFeatures_getter, featureSetNumFeatures_setter);

	Nan::Set(target,FF::newString("TrackerBoostingParams"), FF::getFunction(ctor));
};


NAN_METHOD(TrackerBoostingParams::New) {
	FF::TryCatch tryCatch("TrackerBoostingParams::New");
	FF_ASSERT_CONSTRUCT_CALL();
	TrackerBoostingParams* self = new TrackerBoostingParams();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
	self->self = cv::legacy::TrackerBoosting::Params();
#else
	self->self = cv::TrackerBoosting::Params();
#endif
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif
