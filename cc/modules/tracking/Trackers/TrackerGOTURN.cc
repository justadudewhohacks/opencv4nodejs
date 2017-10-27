#ifdef HAVE_TRACKING

#include "TrackerGOTURN.h"

#if CV_MINOR_VERSION > 1

Nan::Persistent<v8::FunctionTemplate> TrackerGOTURN::constructor;

NAN_MODULE_INIT(TrackerGOTURN::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerGOTURN::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("TrackerGOTURN"));
	instanceTemplate->SetInternalFieldCount(1);

	target->Set(FF_NEW_STRING("TrackerGOTURN"), ctor->GetFunction());
};


NAN_METHOD(TrackerGOTURN::New) {
	FF_METHOD_CONTEXT("TrackerGOTURN::New");

	TrackerGOTURN* self = new TrackerGOTURN();
#if CV_VERSION_MINOR > 2
	self->tracker = cv::TrackerGOTURN::create();
#else
	self->tracker = cv::TrackerGOTURN::createTracker();
#endif

	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

#endif

#endif