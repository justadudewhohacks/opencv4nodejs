#include "SimpleBlobDetectorParams.h"

Nan::Persistent<v8::FunctionTemplate> SimpleBlobDetectorParams::constructor;

NAN_MODULE_INIT(SimpleBlobDetectorParams::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SimpleBlobDetectorParams::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("SimpleBlobDetectorParams"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("blobColor"), blobColorGet, blobColorSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("filterByArea"), filterByAreaGet, filterByAreaSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("filterByCircularity"), filterByCircularityGet, filterByCircularitySet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("filterByColor"), filterByColorGet, filterByColorSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("filterByConvexity"), filterByConvexityGet, filterByConvexitySet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("filterByInertia"), filterByInertiaGet, filterByInertiaSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("maxArea"), maxAreaGet, maxAreaSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("maxCircularity"), maxCircularityGet, maxCircularitySet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("maxConvexity"), maxConvexityGet, maxConvexitySet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("maxInertiaRatio"), maxInertiaRatioGet, maxInertiaRatioSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("maxThreshold"), maxThresholdGet, maxThresholdSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("minArea"), minAreaGet, minAreaSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("minCircularity"), minCircularityGet, minCircularitySet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("minConvexity"), minConvexityGet, minConvexitySet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("minDistBetweenBlobs"), minDistBetweenBlobsGet, minDistBetweenBlobsSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("minInertiaRatio"), minInertiaRatioGet, minInertiaRatioSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("minRepeatability"), minRepeatabilityGet, minRepeatabilitySet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("minThreshold"), minThresholdGet, minThresholdSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("thresholdStep"), thresholdStepGet, thresholdStepSet);

	target->Set(FF_NEW_STRING("SimpleBlobDetectorParams"), ctor->GetFunction());
};


NAN_METHOD(SimpleBlobDetectorParams::New) {
	FF_METHOD_CONTEXT("SimpleBlobDetectorParams::New");
	SimpleBlobDetectorParams* self = new SimpleBlobDetectorParams();
	self->params = cv::SimpleBlobDetector::Params();
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

