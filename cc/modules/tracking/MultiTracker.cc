#ifdef HAVE_TRACKING

#include "MultiTracker.h"

#if CV_MINOR_VERSION > 0

Nan::Persistent<v8::FunctionTemplate> MultiTracker::constructor;

NAN_MODULE_INIT(MultiTracker::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(MultiTracker::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("MultiTracker"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetPrototypeMethod(ctor, "addMIL", MultiTracker::AddMIL);
	Nan::SetPrototypeMethod(ctor, "addBOOSTING", MultiTracker::AddBOOSTING);
	Nan::SetPrototypeMethod(ctor, "addMEDIANFLOW", MultiTracker::AddMEDIANFLOW);
	Nan::SetPrototypeMethod(ctor, "addTLD", MultiTracker::AddTLD);
	Nan::SetPrototypeMethod(ctor, "addKCF", MultiTracker::AddKCF);
#if CV_MINOR_VERSION > 3
	Nan::SetPrototypeMethod(ctor, "addMOSSE", MultiTracker::AddTLD);
#endif
#if CV_MINOR_VERSION > 4 || (CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION > 0)
	Nan::SetPrototypeMethod(ctor, "addCSRT", MultiTracker::AddKCF);
#endif
	Nan::SetPrototypeMethod(ctor, "update", MultiTracker::Update);

	target->Set(FF_NEW_STRING("MultiTracker"), FF::getFunction(ctor));
};

NAN_METHOD(MultiTracker::New) {
	FF_ASSERT_CONSTRUCT_CALL(MultiTracker);
	FF_METHOD_CONTEXT("MultiTracker::New");
	MultiTracker* self = new MultiTracker();
	self->tracker = cv::MultiTracker();
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

NAN_METHOD(MultiTracker::AddMIL) {
	FF::TryCatch tryCatch;
	cv::Mat image;
	cv::Rect2d boundingBox;
	if (
		Mat::Converter::arg(0, &image, info) ||
		Rect::Converter::arg(1, &boundingBox, info)
	) {
		tryCatch.throwNew(tryCatch.formatCatchedError("MultiTracker::AddMIL"));
		return;
	}
#if CV_MINOR_VERSION > 2
	cv::Ptr<cv::Tracker> type = cv::TrackerMIL::create();
#else
	const std::string type("MIL");
#endif
	bool ret = FF_UNWRAP(info.This(), MultiTracker)->tracker.add(type, image, boundingBox);
	info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(MultiTracker::AddBOOSTING) {
	FF::TryCatch tryCatch;
	cv::Mat image;
	cv::Rect2d boundingBox;
	if (
		Mat::Converter::arg(0, &image, info) ||
		Rect::Converter::arg(1, &boundingBox, info)
		) {
		tryCatch.throwNew(tryCatch.formatCatchedError("MultiTracker::AddBOOSTING"));
		return;
	}
#if CV_MINOR_VERSION > 2
	cv::Ptr<cv::Tracker> type = cv::TrackerBoosting::create();
#else
	const std::string type("BOOSTING");
#endif
	bool ret = FF_UNWRAP(info.This(), MultiTracker)->tracker.add(type, image, boundingBox);
	info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(MultiTracker::AddMEDIANFLOW) {
	FF::TryCatch tryCatch;
	cv::Mat image;
	cv::Rect2d boundingBox;
	if (
		Mat::Converter::arg(0, &image, info) ||
		Rect::Converter::arg(1, &boundingBox, info)
		) {
		tryCatch.throwNew(tryCatch.formatCatchedError("MultiTracker::AddMEDIANFLOW"));
		return;
	}
#if CV_MINOR_VERSION > 2
	cv::Ptr<cv::Tracker> type = cv::TrackerMedianFlow::create();
#else
	const std::string type("MEDIANFLOW");
#endif
	bool ret = FF_UNWRAP(info.This(), MultiTracker)->tracker.add(type, image, boundingBox);
	info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(MultiTracker::AddTLD) {
	FF::TryCatch tryCatch;
	cv::Mat image;
	cv::Rect2d boundingBox;
	if (
		Mat::Converter::arg(0, &image, info) ||
		Rect::Converter::arg(1, &boundingBox, info)
		) {
		tryCatch.throwNew(tryCatch.formatCatchedError("MultiTracker::AddTLD"));
		return;
	}
#if CV_MINOR_VERSION > 2
	cv::Ptr<cv::Tracker> type = cv::TrackerTLD::create();
#else
	const std::string type("TLD");
#endif
	bool ret = FF_UNWRAP(info.This(), MultiTracker)->tracker.add(type, image, boundingBox);
	info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(MultiTracker::AddKCF) {
	FF::TryCatch tryCatch;
	cv::Mat image;
	cv::Rect2d boundingBox;
	if (
		Mat::Converter::arg(0, &image, info) ||
		Rect::Converter::arg(1, &boundingBox, info)
		) {
		tryCatch.throwNew(tryCatch.formatCatchedError("MultiTracker::AddKCF"));
		return;
	}
#if CV_MINOR_VERSION > 2
	cv::Ptr<cv::Tracker> type = cv::TrackerKCF::create();
#else
	const std::string type("KCF");
#endif
	bool ret = FF_UNWRAP(info.This(), MultiTracker)->tracker.add(type, image, boundingBox);
	info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(MultiTracker::Update) {
	FF::TryCatch tryCatch;
	cv::Mat image;
	if (Mat::Converter::arg(0, &image, info)) {
		tryCatch.throwNew(tryCatch.formatCatchedError("MultiTracker::Update"));
		return;
	}

	std::vector<cv::Rect2d> rects;
	FF_UNWRAP(info.This(), MultiTracker)->tracker.update(image, rects);

	v8::Local<v8::Array> jsRects = Nan::New<v8::Array>(rects.size());
	for (unsigned long i = 0; i < rects.size(); i++) {
		v8::Local<v8::Object> jsRect = FF::newInstance(Nan::New(Rect::constructor));
		FF_UNWRAP_RECT_AND_GET(jsRect) = rects.at(i);
		jsRects->Set(i, jsRect);
	}
	info.GetReturnValue().Set(jsRects);
}
#if CV_MINOR_VERSION > 3

NAN_METHOD(MultiTracker::AddMOSSE) {
	FF::TryCatch tryCatch;
	cv::Mat image;
	cv::Rect2d boundingBox;
	if (
		Mat::Converter::arg(0, &image, info) ||
		Rect::Converter::arg(1, &boundingBox, info)
		) {
		tryCatch.throwNew(tryCatch.formatCatchedError("MultiTracker::AddMOSSE"));
		return;
	}
	cv::Ptr<cv::Tracker> type = cv::TrackerMOSSE::create();
	bool ret = FF_UNWRAP(info.This(), MultiTracker)->tracker.add(type, image, boundingBox);
	info.GetReturnValue().Set(Nan::New(ret));
}

#endif
#if CV_MINOR_VERSION > 4 || (CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION > 0)

NAN_METHOD(MultiTracker::AddCSRT) {
	FF::TryCatch tryCatch;
	cv::Mat image;
	cv::Rect2d boundingBox;
	if (
		Mat::Converter::arg(0, &image, info) ||
		Rect::Converter::arg(1, &boundingBox, info)
		) {
		tryCatch.throwNew(tryCatch.formatCatchedError("MultiTracker::AddCSRT"));
		return;
	}
	cv::Ptr<cv::Tracker> type = cv::TrackerCSRT::create();
	bool ret = FF_UNWRAP(info.This(), MultiTracker)->tracker.add(type, image, boundingBox);
	info.GetReturnValue().Set(Nan::New(ret));
}
#endif

#endif

#endif
