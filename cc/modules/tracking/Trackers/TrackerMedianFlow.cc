#ifdef HAVE_TRACKING

#include "TrackerMedianFlow.h"

Nan::Persistent<v8::FunctionTemplate> TrackerMedianFlow::constructor;

NAN_MODULE_INIT(TrackerMedianFlow::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerMedianFlow::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerMedianFlow"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::Set(target,FF::newString("TrackerMedianFlow"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerMedianFlow::New) {
	FF_ASSERT_CONSTRUCT_CALL(TrackerMedianFlow);
	FF_METHOD_CONTEXT("TrackerMedianFlow::New");

	TrackerMedianFlow* self = new TrackerMedianFlow();
	cv::TrackerMedianFlow::Params params;
	if (FF::hasArg(info, 0) && IntConverter::assertType(info[0])) {
		params.pointsInGrid = info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value();
	}

#if CV_VERSION_MINOR > 2
	self->tracker = cv::TrackerMedianFlow::create(params);
#else
	self->tracker = cv::TrackerMedianFlow::createTracker(params);
#endif

	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif
