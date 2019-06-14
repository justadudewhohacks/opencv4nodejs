#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerBoosting.h"
#include "TrackerBoostingParams.h"

Nan::Persistent<v8::FunctionTemplate> TrackerBoosting::constructor;

NAN_MODULE_INIT(TrackerBoosting::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerBoosting::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);
	TrackerBoostingParams::Init(target);

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerBoosting"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::Set(target,FF::newString("TrackerBoosting"), FF::getFunction(ctor));
};


NAN_METHOD(TrackerBoosting::New) {
	FF::TryCatch tryCatch("TrackerBoosting::New");
	FF_ASSERT_CONSTRUCT_CALL();

	cv::TrackerBoosting::Params params;
	if (TrackerBoostingParams::Converter::optArg(0, &params, info)) {
		return tryCatch.reThrow();
	}

	TrackerBoosting* self = new TrackerBoosting();
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
	self->tracker = cv::TrackerBoosting::create(params);
#else
	self->tracker = cv::TrackerBoosting::createTracker(params);
#endif
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif
