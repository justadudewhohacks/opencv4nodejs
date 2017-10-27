#ifdef HAVE_TRACKING

#include "TrackerMIL.h"
#include "TrackerMILParams.h"

Nan::Persistent<v8::FunctionTemplate> TrackerMIL::constructor;

NAN_MODULE_INIT(TrackerMIL::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerMIL::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);
	TrackerMILParams::Init(target);

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("TrackerMIL"));
	instanceTemplate->SetInternalFieldCount(1);

	target->Set(FF_NEW_STRING("TrackerMIL"), ctor->GetFunction());
};


NAN_METHOD(TrackerMIL::New) {
	FF_METHOD_CONTEXT("TrackerMIL::New");

	FF_ARG_INSTANCE_IFDEF(
		0,
		cv::TrackerMIL::Params params,
		TrackerMILParams::constructor,
		FF_UNWRAP_TRACKERMILPARAMS_AND_GET,
		cv::TrackerMIL::Params()
	);

	TrackerMIL* self = new TrackerMIL();
#if CV_VERSION_MINOR > 2
	self->tracker = cv::TrackerMIL::create(params);
#else
	self->tracker = cv::TrackerMIL::createTracker(params);
#endif
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

#endif