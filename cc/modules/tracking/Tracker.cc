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
	FF::TryCatch tryCatch;
	cv::Mat image;
	cv::Rect2d boundingBox;
	if (
		Mat::Converter::arg(0, &image, info) ||
		Rect::Converter::arg(1, &boundingBox, info)
		) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Tracker::Init"));
		return;
	}

	bool ret = FF_UNWRAP(info.This(), Tracker)->getTracker()->init(image, boundingBox);
	FF_RETURN(Nan::New(ret));
}

NAN_METHOD(Tracker::Update) {
	FF::TryCatch tryCatch;
	cv::Mat image;
	if (Mat::Converter::arg(0, &image, info)) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Tracker::Update"));
		return;
	}
	FF_OBJ jsRect = FF::newInstance(Nan::New(Rect::constructor));
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