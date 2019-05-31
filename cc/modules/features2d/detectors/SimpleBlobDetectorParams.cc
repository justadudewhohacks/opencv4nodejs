#include "SimpleBlobDetectorParams.h"

Nan::Persistent<v8::FunctionTemplate> SimpleBlobDetectorParams::constructor;

NAN_MODULE_INIT(SimpleBlobDetectorParams::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SimpleBlobDetectorParams::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("SimpleBlobDetectorParams"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF::newString("blobColor"), blobColorGet, blobColorSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("filterByArea"), filterByAreaGet, filterByAreaSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("filterByCircularity"), filterByCircularityGet, filterByCircularitySet);
	Nan::SetAccessor(instanceTemplate, FF::newString("filterByColor"), filterByColorGet, filterByColorSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("filterByConvexity"), filterByConvexityGet, filterByConvexitySet);
	Nan::SetAccessor(instanceTemplate, FF::newString("filterByInertia"), filterByInertiaGet, filterByInertiaSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("maxArea"), maxAreaGet, maxAreaSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("maxCircularity"), maxCircularityGet, maxCircularitySet);
	Nan::SetAccessor(instanceTemplate, FF::newString("maxConvexity"), maxConvexityGet, maxConvexitySet);
	Nan::SetAccessor(instanceTemplate, FF::newString("maxInertiaRatio"), maxInertiaRatioGet, maxInertiaRatioSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("maxThreshold"), maxThresholdGet, maxThresholdSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("minArea"), minAreaGet, minAreaSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("minCircularity"), minCircularityGet, minCircularitySet);
  Nan::SetAccessor(instanceTemplate, FF::newString("minConvexity"), minConvexityGet, minConvexitySet);
  Nan::SetAccessor(instanceTemplate, FF::newString("minDistBetweenBlobs"), minDistBetweenBlobsGet, minDistBetweenBlobsSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("minInertiaRatio"), minInertiaRatioGet, minInertiaRatioSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("minRepeatability"), minRepeatabilityGet, minRepeatabilitySet);
  Nan::SetAccessor(instanceTemplate, FF::newString("minThreshold"), minThresholdGet, minThresholdSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("thresholdStep"), thresholdStepGet, thresholdStepSet);

	Nan::Set(target,FF::newString("SimpleBlobDetectorParams"), FF::getFunction(ctor));
};


NAN_METHOD(SimpleBlobDetectorParams::New) {
	FF_ASSERT_CONSTRUCT_CALL(SimpleBlobDetectorParams);
	FF_METHOD_CONTEXT("SimpleBlobDetectorParams::New");
	SimpleBlobDetectorParams* self = new SimpleBlobDetectorParams();
	self->self = cv::SimpleBlobDetector::Params();
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};
