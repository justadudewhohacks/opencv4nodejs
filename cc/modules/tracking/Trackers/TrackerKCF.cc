#ifdef HAVE_TRACKING

#include "TrackerKCF.h"
#include "TrackerKCFParams.h"

#if CV_MINOR_VERSION > 0

Nan::Persistent<v8::FunctionTemplate> TrackerKCF::constructor;

NAN_MODULE_INIT(TrackerKCF::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerKCF::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);
	TrackerKCFParams::Init(target);

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("TrackerKCF"));
	instanceTemplate->SetInternalFieldCount(1);

	target->Set(FF_NEW_STRING("TrackerKCF"), ctor->GetFunction());
};


NAN_METHOD(TrackerKCF::New) {
	FF_METHOD_CONTEXT("TrackerKCF::New");

	FF_ARG_INSTANCE_IFDEF(
		0,
		cv::TrackerKCF::Params params,
		TrackerKCFParams::constructor,
		FF_UNWRAP_TRACKERKCFPARAMS_AND_GET,
		cv::TrackerKCF::Params()
	);

	TrackerKCF* self = new TrackerKCF();
#if CV_VERSION_MINOR > 2
	self->tracker = cv::TrackerKCF::create(params);
#else
	self->tracker = cv::TrackerKCF::createTracker(params);
#endif
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

#endif

#endif