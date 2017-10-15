#ifdef HAVE_TRACKING

#include "TrackerBoostingParams.h"

Nan::Persistent<v8::FunctionTemplate> TrackerBoostingParams::constructor;

NAN_MODULE_INIT(TrackerBoostingParams::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerBoostingParams::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("TrackerBoostingParams"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("numClassifiers"), numClassifiersGet, numClassifiersSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("samplerOverlap"), samplerOverlapGet, samplerOverlapSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("samplerSearchFactor"), samplerSearchFactorGet, samplerSearchFactorSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("iterationInit"), iterationInitGet, iterationInitSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("featureSetNumFeatures"), featureSetNumFeaturesGet, featureSetNumFeaturesSet);

	target->Set(FF_NEW_STRING("TrackerBoostingParams"), ctor->GetFunction());
};


NAN_METHOD(TrackerBoostingParams::New) {
	FF_METHOD_CONTEXT("TrackerBoostingParams::New");
	TrackerBoostingParams* self = new TrackerBoostingParams();
	self->params = cv::TrackerBoosting::Params();
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

#endif