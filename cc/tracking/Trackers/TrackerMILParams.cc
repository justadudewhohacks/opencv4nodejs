#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerMILParams.h"

Nan::Persistent<v8::FunctionTemplate> TrackerMILParams::constructor;

NAN_MODULE_INIT(TrackerMILParams::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerMILParams::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerMILParams"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF::newString("samplerInitInRadius"), samplerInitInRadius_getter, samplerInitInRadius_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerSearchWinSize"), samplerSearchWinSize_getter, samplerSearchWinSize_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerTrackInRadius"), samplerTrackInRadius_getter, samplerTrackInRadius_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerInitMaxNegNum"), samplerInitMaxNegNum_getter, samplerInitMaxNegNum_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerTrackMaxPosNum"), samplerTrackMaxPosNum_getter, samplerTrackMaxPosNum_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("samplerTrackMaxNegNum"), samplerTrackMaxNegNum_getter, samplerTrackMaxNegNum_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("featureSetNumFeatures"), featureSetNumFeatures_getter, featureSetNumFeatures_setter);

	Nan::Set(target,FF::newString("TrackerMILParams"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerMILParams::New) {
	FF::TryCatch tryCatch("TrackerMILParams::New");
	FF_ASSERT_CONSTRUCT_CALL();
	TrackerMILParams* self = new TrackerMILParams();
	self->self = cv::TrackerMIL::Params();
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif
