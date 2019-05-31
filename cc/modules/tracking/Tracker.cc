#ifdef HAVE_TRACKING

#include "Tracker.h"

void Tracker::Init(v8::Local<v8::FunctionTemplate> ctor) {
	Nan::SetPrototypeMethod(ctor, "clear", Tracker::Clear);
	Nan::SetPrototypeMethod(ctor, "init", Tracker::Init);
	Nan::SetPrototypeMethod(ctor, "update", Tracker::Update);
	Nan::SetPrototypeMethod(ctor, "getModel", Tracker::GetModel);
};

NAN_METHOD(Tracker::Clear) {
	Tracker::unwrapThis(info)->getTracker()->clear();
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

	bool ret = Tracker::unwrapThis(info)->getTracker()->init(image, boundingBox);
	info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(Tracker::Update) {
	FF::TryCatch tryCatch;
	cv::Mat image;
	if (Mat::Converter::arg(0, &image, info)) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Tracker::Update"));
		return;
	}
	v8::Local<v8::Object> jsRect = FF::newInstance(Nan::New(Rect::constructor));
	bool ret = Tracker::unwrapThis(info)->getTracker()->update(image, Rect::Converter::unwrapUnchecked(jsRect));
	
	if (ret) {
		info.GetReturnValue().Set(jsRect);
	} else {
		info.GetReturnValue().Set(Nan::Null());
	}
}

NAN_METHOD(Tracker::GetModel) {
	// TBD
}

#endif