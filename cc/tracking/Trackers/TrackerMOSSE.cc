#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerMOSSE.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

Nan::Persistent<v8::FunctionTemplate> TrackerMOSSE::constructor;

NAN_MODULE_INIT(TrackerMOSSE::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerMOSSE::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerMOSSE"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::Set(target,FF::newString("TrackerMOSSE"), FF::getFunction(ctor));
};


NAN_METHOD(TrackerMOSSE::New) {
	FF::TryCatch tryCatch("TrackerMOSSE::New");
	FF_ASSERT_CONSTRUCT_CALL();

	TrackerMOSSE* self = new TrackerMOSSE();
	self->tracker = cv::TrackerMOSSE::create();
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
