#ifdef HAVE_TRACKING

#include "Tracker.h"

void Tracker::Init(v8::Local<v8::FunctionTemplate> ctor) {
	Nan::SetPrototypeMethod(ctor, "clear", Tracker::Clear);
	Nan::SetPrototypeMethod(ctor, "init", Tracker::Init);
	Nan::SetPrototypeMethod(ctor, "update", Tracker::Update);
	Nan::SetPrototypeMethod(ctor, "getModel", Tracker::GetModel);
};

NAN_METHOD(Tracker::Clear) {
	FF_UNWRAP(info.This(), Tracker)->getTracker()->clear();
}

NAN_METHOD(Tracker::Init) {
	FF_METHOD_CONTEXT("Tracker::Init");

	FF_ARG_INSTANCE(0, cv::Mat image, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Rect2d boundingBox, Rect::constructor, FF_UNWRAP_RECT_AND_GET);

	bool ret = FF_UNWRAP(info.This(), Tracker)->getTracker()->init(image, boundingBox);
	FF_RETURN(Nan::New(ret));
}

NAN_METHOD(Tracker::Update) {
	FF_METHOD_CONTEXT("Tracker::Update");

	FF_ARG_INSTANCE(0, cv::Mat image, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

	FF_OBJ jsRect = FF_NEW_INSTANCE(Rect::constructor);
	bool ret = FF_UNWRAP(info.This(), Tracker)->getTracker()->update(image, FF_UNWRAP_RECT_AND_GET(jsRect));
	
	if (ret) {
		FF_RETURN(jsRect);
	} else {
		FF_RETURN(Nan::Null());
	}
}

NAN_METHOD(Tracker::GetModel) {
	// TBD
}

#endif