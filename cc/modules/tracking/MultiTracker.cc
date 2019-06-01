#ifdef HAVE_TRACKING

#include "MultiTracker.h"

#if CV_MINOR_VERSION > 0

Nan::Persistent<v8::FunctionTemplate> MultiTracker::constructor;

NAN_MODULE_INIT(MultiTracker::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(MultiTracker::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("MultiTracker"));
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

	Nan::Set(target,FF::newString("MultiTracker"), FF::getFunction(ctor));
};

NAN_METHOD(MultiTracker::New) {
	FF_ASSERT_CONSTRUCT_CALL(MultiTracker);
	MultiTracker* self = new MultiTracker();
	self->setNativeObject(cv::MultiTracker::create());
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
	bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
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
	bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
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
	bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
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
	bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
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
	bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
	info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(MultiTracker::Update) {
	FF::TryCatch tryCatch;
	cv::Mat image;
	if (Mat::Converter::arg(0, &image, info)) {
		return tryCatch.throwNew(tryCatch.formatCatchedError("MultiTracker::Update"));
	}

	std::vector<cv::Rect2d> rects;
	MultiTracker::unwrapSelf(info)->update(image, rects);
	info.GetReturnValue().Set(Rect::ArrayConverter::wrap(rects));
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
	bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
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
	bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
	info.GetReturnValue().Set(Nan::New(ret));
}
#endif

#endif

#endif
