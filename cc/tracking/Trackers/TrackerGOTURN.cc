#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerGOTURN.h"

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)

Nan::Persistent<v8::FunctionTemplate> TrackerGOTURN::constructor;

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)

NAN_METHOD(TrackerGOTURN::Clear) {
}

NAN_METHOD(TrackerGOTURN::Init) {
	FF::TryCatch tryCatch("TrackerGOTURN::Init");
	cv::Mat image;
	cv::Rect2d boundingBox;
	if (
		Mat::Converter::arg(0, &image, info) ||
		Rect::Converter::arg(1, &boundingBox, info)
		) {
		return tryCatch.reThrow();
	}

	TrackerGOTURN::unwrapThis(info)->getTracker()->init(image, boundingBox);
}

NAN_METHOD(TrackerGOTURN::Update) {
	FF::TryCatch tryCatch("TrackerGOTURN::Update");
	cv::Mat image;
	if (Mat::Converter::arg(0, &image, info)) {
		return tryCatch.reThrow();
	}

	cv::Rect rect;
	bool ret = false;

	try {
		ret = TrackerGOTURN::unwrapThis(info)->getTracker()->update(image, rect);
	}
	catch (std::exception &e) {
		return tryCatch.throwError(e.what());
	}

	if (ret) {
		info.GetReturnValue().Set(Rect::Converter::wrap(rect));
	} else {
		info.GetReturnValue().Set(Nan::Null());
	}
}

NAN_METHOD(TrackerGOTURN::GetModel) {
	// TBD
}

#endif

NAN_MODULE_INIT(TrackerGOTURN::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerGOTURN::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
	Nan::SetPrototypeMethod(ctor, "clear", TrackerGOTURN::Clear);
	Nan::SetPrototypeMethod(ctor, "init", TrackerGOTURN::Init);
	Nan::SetPrototypeMethod(ctor, "update", TrackerGOTURN::Update);
	Nan::SetPrototypeMethod(ctor, "getModel", TrackerGOTURN::GetModel);
#else
	Tracker::Init(ctor);
#endif
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
