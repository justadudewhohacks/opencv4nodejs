#include "GFTTDetector.h"

Nan::Persistent<v8::FunctionTemplate> GFTTDetector::constructor;

NAN_MODULE_INIT(GFTTDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(GFTTDetector::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("GFTTDetector").ToLocalChecked());

	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("maxCorners").ToLocalChecked(), GFTTDetector::GetMaxFeatures);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("qualityLevel").ToLocalChecked(), GFTTDetector::GetQualityLevel);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("minDistance").ToLocalChecked(), GFTTDetector::GetMinDistance);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("blockSize").ToLocalChecked(), GFTTDetector::GetBlockSize);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("useHarrisDetector").ToLocalChecked(), GFTTDetector::GetUseHarrisDetector);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("k").ToLocalChecked(), GFTTDetector::GetK);
/*
	//cv::AKAZE
	//cv::AgastFeatureDetector
	//BRISK, ORB, MSER, FAST, AGAST, GFTTDetector, KAZE
	int maxCorners = 1000, double qualityLevel = 0.01, double minDistance = 1,
		int blockSize = 3, bool useHarrisDetector = false, double k = 0.04;
	
	// detector->getHarrisDetector() != nullptr
	//cv::FastFeatureDetector::create()
	//cv::AgastFeatureDetector::cre
		//cv::BRISK::create
		//cv::FastFeatureDetector::create
		*/

  target->Set(Nan::New("GFTTDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(GFTTDetector::New) {
	int maxCorners = 1000;
	double qualityLevel = 0.01;
	double minDistance = 1;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	
	FF_VERIFY_OPTIONAL_ARG(0, maxCorners, IsUint32, Int32Value)
	FF_VERIFY_OPTIONAL_ARG(1, qualityLevel, IsNumber, NumberValue)
	FF_VERIFY_OPTIONAL_ARG(2, minDistance, IsNumber, NumberValue)
	FF_VERIFY_OPTIONAL_ARG(3, blockSize, IsUint32, Int32Value)
	FF_VERIFY_OPTIONAL_ARG(4, useHarrisDetector, IsBoolean, BooleanValue)
	FF_VERIFY_OPTIONAL_ARG(5, k, IsNumber, NumberValue)

	GFTTDetector* self = new GFTTDetector();
	self->Wrap(info.Holder());
	self->detector = cv::GFTTDetector::create(maxCorners, qualityLevel, minDistance, blockSize, useHarrisDetector, k);
  info.GetReturnValue().Set(info.Holder());
}
