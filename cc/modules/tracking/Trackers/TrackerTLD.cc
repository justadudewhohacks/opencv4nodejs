#ifdef HAVE_TRACKING

#include "TrackerTLD.h"

Nan::Persistent<v8::FunctionTemplate> TrackerTLD::constructor;

NAN_MODULE_INIT(TrackerTLD::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerTLD::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("TrackerTLD"));
	instanceTemplate->SetInternalFieldCount(1);

	target->Set(FF_NEW_STRING("TrackerTLD"), ctor->GetFunction());
};


NAN_METHOD(TrackerTLD::New) {
	FF_METHOD_CONTEXT("TrackerTLD::New");

	TrackerTLD* self = new TrackerTLD();
#if CV_VERSION_MINOR > 2
	self->tracker = cv::TrackerTLD::create();
#else
	self->tracker = cv::TrackerTLD::createTracker();
#endif
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

#endif