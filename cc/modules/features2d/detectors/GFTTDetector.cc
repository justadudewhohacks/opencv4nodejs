#include "GFTTDetector.h"

Nan::Persistent<v8::FunctionTemplate> GFTTDetector::constructor;

NAN_MODULE_INIT(GFTTDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(GFTTDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("GFTTDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);
	
	Nan::SetAccessor(instanceTemplate, Nan::New("maxCorners").ToLocalChecked(), GFTTDetector::GetMaxFeatures);
	Nan::SetAccessor(instanceTemplate, Nan::New("qualityLevel").ToLocalChecked(), GFTTDetector::GetQualityLevel);
	Nan::SetAccessor(instanceTemplate, Nan::New("minDistance").ToLocalChecked(), GFTTDetector::GetMinDistance);
	Nan::SetAccessor(instanceTemplate, Nan::New("blockSize").ToLocalChecked(), GFTTDetector::GetBlockSize);
	Nan::SetAccessor(instanceTemplate, Nan::New("useHarrisDetector").ToLocalChecked(), GFTTDetector::GetUseHarrisDetector);
	Nan::SetAccessor(instanceTemplate, Nan::New("k").ToLocalChecked(), GFTTDetector::GetK);

  target->Set(Nan::New("GFTTDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(GFTTDetector::New) {
	FF_METHOD_CONTEXT("GFTTDetector::New");

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

	FF_GET_INT_IFDEF(optArgs, int maxCorners, "maxCorners", 1000);
	FF_GET_NUMBER_IFDEF(optArgs, double qualityLevel, "qualityLevel", 0.01);
	FF_GET_NUMBER_IFDEF(optArgs, double minDistance, "minDistance", 1);
	FF_GET_INT_IFDEF(optArgs, int blockSize, "blockSize", 3);
	FF_GET_BOOL_IFDEF(optArgs, bool useHarrisDetector, "useHarrisDetector", false);
	FF_GET_NUMBER_IFDEF(optArgs, double k, "k", 0.04);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(0, maxCorners, maxCorners);
		FF_ARG_NUMBER_IFDEF(1, qualityLevel, qualityLevel);
		FF_ARG_NUMBER_IFDEF(2, minDistance, minDistance);
		FF_ARG_INT_IFDEF(3, blockSize, blockSize);
		FF_ARG_BOOL_IFDEF(4, useHarrisDetector, useHarrisDetector);
		FF_ARG_NUMBER_IFDEF(5, k, k);
	}

	GFTTDetector* self = new GFTTDetector();
	self->Wrap(info.Holder());
	self->detector = cv::GFTTDetector::create(maxCorners, qualityLevel, minDistance, blockSize, useHarrisDetector, k);
  FF_RETURN(info.Holder());
}