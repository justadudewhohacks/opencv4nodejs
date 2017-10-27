#ifdef HAVE_TRACKING

#include "TrackerBoosting.h"
#include "TrackerBoostingParams.h"

Nan::Persistent<v8::FunctionTemplate> TrackerBoosting::constructor;

NAN_MODULE_INIT(TrackerBoosting::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerBoosting::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);
	TrackerBoostingParams::Init(target);

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("TrackerBoosting"));
	instanceTemplate->SetInternalFieldCount(1);

	target->Set(FF_NEW_STRING("TrackerBoosting"), ctor->GetFunction());
};


NAN_METHOD(TrackerBoosting::New) {
	FF_METHOD_CONTEXT("TrackerBoosting::New");

	FF_ARG_INSTANCE_IFDEF(
		0,
		cv::TrackerBoosting::Params params,
		TrackerBoostingParams::constructor,
		FF_UNWRAP_TRACKERBOOSTINGPARAMS_AND_GET,
		cv::TrackerBoosting::Params()
	);

	TrackerBoosting* self = new TrackerBoosting();
#if CV_VERSION_MINOR > 2
	self->tracker = cv::TrackerBoosting::create(params);
#else
	self->tracker = cv::TrackerBoosting::createTracker(params);
#endif
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

#endif