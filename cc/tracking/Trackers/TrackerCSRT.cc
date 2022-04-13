#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerCSRT.h"
#include "TrackerCSRTParams.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 1)

Nan::Persistent<v8::FunctionTemplate> TrackerCSRT::constructor;

NAN_MODULE_INIT(TrackerCSRT::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerCSRT::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);
	TrackerCSRTParams::Init(target);

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerCSRT"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::Set(target,FF::newString("TrackerCSRT"), FF::getFunction(ctor));
};


NAN_METHOD(TrackerCSRT::New) {
	FF::TryCatch tryCatch("TrackerCSRT::New");
	FF_ASSERT_CONSTRUCT_CALL();

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
	cv::legacy::TrackerCSRT::Params params;
#else
	cv::TrackerCSRT::Params params;
#endif
	if (TrackerCSRTParams::Converter::optArg(0, &params, info)) {
		return tryCatch.reThrow();
	}

	TrackerCSRT* self = new TrackerCSRT();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
	self->tracker = cv::legacy::TrackerCSRT::create(params);
#else
	self->tracker = cv::TrackerCSRT::create(params);
#endif
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
