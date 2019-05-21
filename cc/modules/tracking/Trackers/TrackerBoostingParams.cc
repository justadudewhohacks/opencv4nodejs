#ifdef HAVE_TRACKING

#include "TrackerBoostingParams.h"

Nan::Persistent<v8::FunctionTemplate> TrackerBoostingParams::constructor;

NAN_MODULE_INIT(TrackerBoostingParams::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerBoostingParams::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerBoostingParams"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF::newString("numClassifiers"), numClassifiersGet, numClassifiersSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerOverlap"), samplerOverlapGet, samplerOverlapSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerSearchFactor"), samplerSearchFactorGet, samplerSearchFactorSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("iterationInit"), iterationInitGet, iterationInitSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("featureSetNumFeatures"), featureSetNumFeaturesGet, featureSetNumFeaturesSet);

	Nan::Set(target,FF::newString("TrackerBoostingParams"), FF::getFunction(ctor));
};


NAN_METHOD(TrackerBoostingParams::New) {
	FF_ASSERT_CONSTRUCT_CALL(TrackerBoostingParams);
	FF_METHOD_CONTEXT("TrackerBoostingParams::New");
	TrackerBoostingParams* self = new TrackerBoostingParams();
	self->params = cv::TrackerBoosting::Params();
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif
