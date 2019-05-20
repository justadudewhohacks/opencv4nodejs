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

	target->Set(FF_NEW_STRING("TrackerMIL"), FF::getFunction(ctor));
};


NAN_METHOD(TrackerMIL::New) {
	FF_ASSERT_CONSTRUCT_CALL(TrackerMIL);
	FF::TryCatch tryCatch;

	cv::TrackerMIL::Params params;
	if (TrackerMILParams::Converter::optArg(0, &params, info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("TrackerMIL::New");
		tryCatch.throwNew(err);
		return;
	}

	TrackerMIL* self = new TrackerMIL();
#if CV_VERSION_MINOR > 2
	self->tracker = cv::TrackerMIL::create(params);
#else
	self->tracker = cv::TrackerMIL::createTracker(params);
#endif
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif
