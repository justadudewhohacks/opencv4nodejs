#ifdef HAVE_TRACKING

#include "MultiTracker.h"

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
	Nan::SetPrototypeMethod(ctor, "update", MultiTracker::Update);

	target->Set(FF_NEW_STRING("MultiTracker"), ctor->GetFunction());
};

NAN_METHOD(MultiTracker::New) {
	FF_METHOD_CONTEXT("MultiTracker::New");
	MultiTracker* self = new MultiTracker();
	self->tracker = cv::MultiTracker();
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

NAN_METHOD(MultiTracker::AddMIL) {
	FF_METHOD_CONTEXT("MultiTracker::AddMIL");
	FF_ARG_INSTANCE(0, cv::Mat image, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Rect2d boundingBox, Rect::constructor, FF_UNWRAP_RECT_AND_GET);
	const std::string type("MIL");
	bool ret = FF_UNWRAP(info.This(), MultiTracker)->tracker.add(type, image, boundingBox);
	FF_RETURN(Nan::New(ret));
}

NAN_METHOD(MultiTracker::AddBOOSTING) {
	FF_METHOD_CONTEXT("MultiTracker::AddBOOSTING");
	FF_ARG_INSTANCE(0, cv::Mat image, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Rect2d boundingBox, Rect::constructor, FF_UNWRAP_RECT_AND_GET);
	const cv::String type("BOOSTING");
	bool ret = FF_UNWRAP(info.This(), MultiTracker)->tracker.add(type, image, boundingBox);
	FF_RETURN(Nan::New(ret));
}

NAN_METHOD(MultiTracker::AddMEDIANFLOW) {
	FF_METHOD_CONTEXT("MultiTracker::AddMEDIANFLOW");
	FF_ARG_INSTANCE(0, cv::Mat image, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Rect2d boundingBox, Rect::constructor, FF_UNWRAP_RECT_AND_GET);
	const cv::String type("MEDIANFLOW");
	bool ret = FF_UNWRAP(info.This(), MultiTracker)->tracker.add(type, image, boundingBox);
	FF_RETURN(Nan::New(ret));
}

NAN_METHOD(MultiTracker::AddTLD) {
	FF_METHOD_CONTEXT("MultiTracker::AddTLD");
	FF_ARG_INSTANCE(0, cv::Mat image, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Rect2d boundingBox, Rect::constructor, FF_UNWRAP_RECT_AND_GET);
	const cv::String type("TLD");
	bool ret = FF_UNWRAP(info.This(), MultiTracker)->tracker.add(type, image, boundingBox);
	FF_RETURN(Nan::New(ret));
}

NAN_METHOD(MultiTracker::AddKCF) {
	FF_METHOD_CONTEXT("MultiTracker::AddKCF");
	FF_ARG_INSTANCE(0, cv::Mat image, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Rect2d boundingBox, Rect::constructor, FF_UNWRAP_RECT_AND_GET);
	const cv::String type("KCF");
	bool ret = FF_UNWRAP(info.This(), MultiTracker)->tracker.add(type, image, boundingBox);
	FF_RETURN(Nan::New(ret));
}

NAN_METHOD(MultiTracker::Update) {
	FF_METHOD_CONTEXT("MultiTracker::Update");

	FF_ARG_INSTANCE(0, cv::Mat image, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

	std::vector<cv::Rect2d> rects;
	FF_UNWRAP(info.This(), MultiTracker)->tracker.update(image, rects);

	FF_ARR jsRects = FF_NEW_ARRAY(rects.size());
	for (int i = 0; i < rects.size(); i++) {
		FF_OBJ jsRect = FF_NEW_INSTANCE(Rect::constructor);
		FF_UNWRAP_RECT_AND_GET(jsRect) = rects.at(i);
		jsRects->Set(i, jsRect);
	}
	FF_RETURN(jsRects);
}

#endif