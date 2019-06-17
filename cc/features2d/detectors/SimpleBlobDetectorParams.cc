#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "SimpleBlobDetectorParams.h"

Nan::Persistent<v8::FunctionTemplate> SimpleBlobDetectorParams::constructor;

NAN_MODULE_INIT(SimpleBlobDetectorParams::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SimpleBlobDetectorParams::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("SimpleBlobDetectorParams"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF::newString("blobColor"), blobColor_getter, blobColor_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("filterByArea"), filterByArea_getter, filterByArea_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("filterByCircularity"), filterByCircularity_getter, filterByCircularity_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("filterByColor"), filterByColor_getter, filterByColor_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("filterByConvexity"), filterByConvexity_getter, filterByConvexity_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("filterByInertia"), filterByInertia_getter, filterByInertia_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("maxArea"), maxArea_getter, maxArea_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("maxCircularity"), maxCircularity_getter, maxCircularity_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("maxConvexity"), maxConvexity_getter, maxConvexity_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("maxInertiaRatio"), maxInertiaRatio_getter, maxInertiaRatio_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("maxThreshold"), maxThreshold_getter, maxThreshold_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("minArea"), minArea_getter, minArea_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("minCircularity"), minCircularity_getter, minCircularity_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("minConvexity"), minConvexity_getter, minConvexity_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("minDistBetweenBlobs"), minDistBetweenBlobs_getter, minDistBetweenBlobs_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("minInertiaRatio"), minInertiaRatio_getter, minInertiaRatio_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("minRepeatability"), minRepeatability_getter, minRepeatability_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("minThreshold"), minThreshold_getter, minThreshold_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("thresholdStep"), thresholdStep_getter, thresholdStep_setter);

	Nan::Set(target,FF::newString("SimpleBlobDetectorParams"), FF::getFunction(ctor));
};


NAN_METHOD(SimpleBlobDetectorParams::New) {
	FF::TryCatch tryCatch("SimpleBlobDetectorParams::New");
	FF_ASSERT_CONSTRUCT_CALL();
	SimpleBlobDetectorParams* self = new SimpleBlobDetectorParams();
	self->self = cv::SimpleBlobDetector::Params();
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif
