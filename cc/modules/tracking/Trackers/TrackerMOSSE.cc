#ifdef HAVE_TRACKING

#include "TrackerMOSSE.h"

#if CV_MINOR_VERSION > 3

Nan::Persistent<v8::FunctionTemplate> TrackerMOSSE::constructor;

NAN_MODULE_INIT(TrackerMOSSE::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerMOSSE::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);
	TrackerMOSSEParams::Init(target);

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("TrackerMOSSE"));
	instanceTemplate->SetInternalFieldCount(1);

	target->Set(FF_NEW_STRING("TrackerMOSSE"), ctor->GetFunction());
};


NAN_METHOD(TrackerMOSSE::New) {
	FF_ASSERT_CONSTRUCT_CALL(TrackerMOSSE);
	FF_METHOD_CONTEXT("TrackerMOSSE::New");

	TrackerMOSSE* self = new TrackerMOSSE();
	self->tracker = cv::TrackerMOSSE::createTracker(params);
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

#endif

#endif
