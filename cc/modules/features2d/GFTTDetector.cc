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



/*
	//BRISK, MSER, FAST, AGAST, AKAZE, KAZE

	//cv::FastFeatureDetector::create()
	//cv::AgastFeatureDetector::cre
		//cv::BRISK::create
		//cv::FastFeatureDetector::create
		*/

  target->Set(Nan::New("GFTTDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(GFTTDetector::New) {
	if (!info.IsConstructCall()) {
		return Nan::ThrowError("GFTTDetector::New expected new key word");
	}

	int maxCorners = 1000;
	double qualityLevel = 0.01;
	double minDistance = 1;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;

	if (info[0]->IsObject()) {
		v8::Local<v8::Object> args = info[0]->ToObject();
		FF_GET_CHECKED_PROP_IFDEF(args, maxCorners, IsInt32, Int32Value)
		FF_GET_CHECKED_PROP_IFDEF(args, qualityLevel, IsNumber, NumberValue)
		FF_GET_CHECKED_PROP_IFDEF(args, minDistance, IsNumber, NumberValue)
		FF_GET_CHECKED_PROP_IFDEF(args, blockSize, IsInt32, Int32Value)
		FF_GET_CHECKED_PROP_IFDEF(args, useHarrisDetector, IsBoolean, BooleanValue)
		FF_GET_CHECKED_PROP_IFDEF(args, k, IsNumber, NumberValue)
	}
	GFTTDetector* self = new GFTTDetector();
	self->Wrap(info.Holder());
	self->detector = cv::GFTTDetector::create(maxCorners, qualityLevel, minDistance, blockSize, useHarrisDetector, k);
  info.GetReturnValue().Set(info.Holder());
}