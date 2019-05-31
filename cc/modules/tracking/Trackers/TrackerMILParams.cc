#ifdef HAVE_TRACKING

#include "TrackerMILParams.h"

Nan::Persistent<v8::FunctionTemplate> TrackerMILParams::constructor;

NAN_MODULE_INIT(TrackerMILParams::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerMILParams::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerMILParams"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF::newString("samplerInitInRadius"), samplerInitInRadiusGet, samplerInitInRadiusSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerSearchWinSize"), samplerSearchWinSizeGet, samplerSearchWinSizeSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerTrackInRadius"), samplerTrackInRadiusGet, samplerTrackInRadiusSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerInitMaxNegNum"), samplerInitMaxNegNumGet, samplerInitMaxNegNumSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerTrackMaxPosNum"), samplerTrackMaxPosNumGet, samplerTrackMaxPosNumSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerTrackMaxNegNum"), samplerTrackMaxNegNumGet, samplerTrackMaxNegNumSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("featureSetNumFeatures"), featureSetNumFeaturesGet, featureSetNumFeaturesSet);

	Nan::Set(target,FF::newString("TrackerMILParams"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerMILParams::New) {
	FF_ASSERT_CONSTRUCT_CALL(TrackerMILParams);
	FF_METHOD_CONTEXT("TrackerMILParams::New");
	TrackerMILParams* self = new TrackerMILParams();
	self->self = cv::TrackerMIL::Params();
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif
