#ifdef HAVE_TRACKING

#include "TrackerMILParams.h"

Nan::Persistent<v8::FunctionTemplate> TrackerMILParams::constructor;

NAN_MODULE_INIT(TrackerMILParams::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerMILParams::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("TrackerMILParams"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("samplerInitInRadius"), samplerInitInRadiusGet, samplerInitInRadiusSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("samplerSearchWinSize"), samplerSearchWinSizeGet, samplerSearchWinSizeSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("samplerTrackInRadius"), samplerTrackInRadiusGet, samplerTrackInRadiusSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("samplerInitMaxNegNum"), samplerInitMaxNegNumGet, samplerInitMaxNegNumSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("samplerTrackMaxPosNum"), samplerTrackMaxPosNumGet, samplerTrackMaxPosNumSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("samplerTrackMaxNegNum"), samplerTrackMaxNegNumGet, samplerTrackMaxNegNumSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("featureSetNumFeatures"), featureSetNumFeaturesGet, featureSetNumFeaturesSet);

	target->Set(FF_NEW_STRING("TrackerMILParams"), ctor->GetFunction());
};

NAN_METHOD(TrackerMILParams::New) {
	FF_METHOD_CONTEXT("TrackerMILParams::New");
	TrackerMILParams* self = new TrackerMILParams();
	self->params = cv::TrackerMIL::Params();
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

#endif