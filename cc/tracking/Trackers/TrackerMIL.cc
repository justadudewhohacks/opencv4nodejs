#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerMIL.h"
#include "TrackerMILParams.h"

Nan::Persistent<v8::FunctionTemplate> TrackerMIL::constructor;

NAN_MODULE_INIT(TrackerMIL::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerMIL::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);
	TrackerMILParams::Init(target);

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerMIL"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::Set(target,FF::newString("TrackerMIL"), FF::getFunction(ctor));
};


NAN_METHOD(TrackerMIL::New) {
	FF::TryCatch tryCatch("TrackerMIL::New");
	FF_ASSERT_CONSTRUCT_CALL();

	cv::TrackerMIL::Params params;
	if (TrackerMILParams::Converter::optArg(0, &params, info)) {
		return tryCatch.reThrow();
	}

	TrackerMIL* self = new TrackerMIL();
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
	self->tracker = cv::TrackerMIL::create(params);
#else
	self->tracker = cv::TrackerMIL::createTracker(params);
#endif
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif
