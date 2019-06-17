#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerTLD.h"

Nan::Persistent<v8::FunctionTemplate> TrackerTLD::constructor;

NAN_MODULE_INIT(TrackerTLD::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerTLD::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerTLD"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::Set(target,FF::newString("TrackerTLD"), FF::getFunction(ctor));
};


NAN_METHOD(TrackerTLD::New) {
	FF::TryCatch tryCatch("TrackerTLD::New");
	FF_ASSERT_CONSTRUCT_CALL();

	TrackerTLD* self = new TrackerTLD();
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
	self->tracker = cv::TrackerTLD::create();
#else
	self->tracker = cv::TrackerTLD::createTracker();
#endif
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif
