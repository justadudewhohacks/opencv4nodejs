#ifdef HAVE_TRACKING

#include "TrackerKCF.h"
#include "TrackerKCFParams.h"

#if CV_MINOR_VERSION > 0

Nan::Persistent<v8::FunctionTemplate> TrackerKCF::constructor;

NAN_MODULE_INIT(TrackerKCF::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerKCF::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	Tracker::Init(ctor);
	TrackerKCFParams::Init(target);

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerKCF"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::Set(target,FF::newString("TrackerKCF"), FF::getFunction(ctor));
};


NAN_METHOD(TrackerKCF::New) {
	FF::TryCatch tryCatch("TrackerKCF::New");
	FF_ASSERT_CONSTRUCT_CALL();

	cv::TrackerKCF::Params params;
	if (TrackerKCFParams::Converter::optArg(0, &params, info)) {
		return tryCatch.reThrow();
	}

	TrackerKCF* self = new TrackerKCF();
#if CV_VERSION_MINOR > 2
	self->tracker = cv::TrackerKCF::create(params);
#else
	self->tracker = cv::TrackerKCF::createTracker(params);
#endif
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
