#ifdef HAVE_TRACKING

#include "TrackerCSRT.h"
#include "TrackerCSRTParams.h"

#if CV_MINOR_VERSION > 4 || (CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION > 0)

Nan::Persistent<v8::FunctionTemplate> TrackerCSRT::constructor;

NAN_MODULE_INIT(TrackerCSRT::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerCSRT::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);
	TrackerCSRTParams::Init(target);

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("TrackerCSRT"));
	instanceTemplate->SetInternalFieldCount(1);

	target->Set(FF_NEW_STRING("TrackerCSRT"), FF::getFunction(ctor));
};


NAN_METHOD(TrackerCSRT::New) {
	FF_ASSERT_CONSTRUCT_CALL(TrackerCSRT);
	FF_METHOD_CONTEXT("TrackerCSRT::New");

	FF_ARG_INSTANCE_IFDEF(
		0,
		cv::TrackerCSRT::Params params,
		TrackerCSRTParams::constructor,
		FF_UNWRAP_TRACKERCSRTPARAMS_AND_GET,
		cv::TrackerCSRT::Params()
	);

	TrackerCSRT* self = new TrackerCSRT();
	self->tracker = cv::TrackerCSRT::create(params);
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

#endif

#endif
