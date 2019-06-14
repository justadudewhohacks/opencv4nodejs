#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerGOTURN.h"

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)

Nan::Persistent<v8::FunctionTemplate> TrackerGOTURN::constructor;

NAN_MODULE_INIT(TrackerGOTURN::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerGOTURN::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerGOTURN"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::Set(target,FF::newString("TrackerGOTURN"), FF::getFunction(ctor));
};


NAN_METHOD(TrackerGOTURN::New) {
	FF::TryCatch tryCatch("TrackerGOTURN::New");
	FF_ASSERT_CONSTRUCT_CALL();

	TrackerGOTURN* self = new TrackerGOTURN();
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
	self->tracker = cv::TrackerGOTURN::create();
#else
	self->tracker = cv::TrackerGOTURN::createTracker();
#endif

	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
