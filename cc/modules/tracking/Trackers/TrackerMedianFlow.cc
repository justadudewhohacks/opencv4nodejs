#ifdef HAVE_TRACKING

#include "TrackerMedianFlow.h"

Nan::Persistent<v8::FunctionTemplate> TrackerMedianFlow::constructor;

NAN_MODULE_INIT(TrackerMedianFlow::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerMedianFlow::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("TrackerMedianFlow"));
	instanceTemplate->SetInternalFieldCount(1);

	target->Set(FF_NEW_STRING("TrackerMedianFlow"), ctor->GetFunction());
};

NAN_METHOD(TrackerMedianFlow::New) {
	FF_METHOD_CONTEXT("TrackerMedianFlow::New");

	TrackerMedianFlow* self = new TrackerMedianFlow();
	cv::TrackerMedianFlow::Params params;
	if (FF_HAS_ARG(0) && FF_IS_INT(info[0])) {
		params.pointsInGrid = info[0]->Int32Value();
	}

#if CV_VERSION_MINOR > 2
	self->tracker = cv::TrackerMedianFlow::create(params);
#else
	self->tracker = cv::TrackerMedianFlow::createTracker(params);
#endif

	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

#endif