#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

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
	FF::TryCatch tryCatch("TrackerMedianFlow::New");
	FF_ASSERT_CONSTRUCT_CALL();

	TrackerMedianFlow* self = new TrackerMedianFlow();
	cv::TrackerMedianFlow::Params params;
	if (FF::hasArg(info, 0) && FF::IntConverterImpl::assertType(info[0])) {
		params.pointsInGrid = info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value();
	}

#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
	self->tracker = cv::TrackerMedianFlow::create(params);
#else
	self->tracker = cv::TrackerMedianFlow::createTracker(params);
#endif

	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif
