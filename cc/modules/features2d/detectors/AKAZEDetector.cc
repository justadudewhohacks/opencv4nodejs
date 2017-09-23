#include "AKAZEDetector.h"

Nan::Persistent<v8::FunctionTemplate> AKAZEDetector::constructor;

NAN_MODULE_INIT(AKAZEDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(AKAZEDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("AKAZEDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, Nan::New("descriptorType").ToLocalChecked(), AKAZEDetector::GetDescriptorType);
	Nan::SetAccessor(instanceTemplate, Nan::New("descriptorSize").ToLocalChecked(), AKAZEDetector::GetDescriptorSize);
	Nan::SetAccessor(instanceTemplate, Nan::New("descriptorChannels").ToLocalChecked(), AKAZEDetector::GetDescriptorChannels);
	Nan::SetAccessor(instanceTemplate, Nan::New("threshold").ToLocalChecked(), AKAZEDetector::GetThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaves").ToLocalChecked(), AKAZEDetector::GetNOctaves);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaveLayers").ToLocalChecked(), AKAZEDetector::GetNOctaveLayers);
	Nan::SetAccessor(instanceTemplate, Nan::New("diffusivity").ToLocalChecked(), AKAZEDetector::GetDiffusity);

  target->Set(Nan::New("AKAZEDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(AKAZEDetector::New) {
	FF_METHOD_CONTEXT("AKAZEDetector::New");

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

	FF_GET_INT_IFDEF(optArgs, int descriptorType, "descriptorType", cv::AKAZE::DESCRIPTOR_MLDB);
	FF_GET_INT_IFDEF(optArgs, int descriptorSize, "descriptorSize", 0);
	FF_GET_INT_IFDEF(optArgs, int descriptorChannels, "descriptorChannels", 3);
	FF_GET_NUMBER_IFDEF(optArgs, double threshold, "threshold", 0.001f);
	FF_GET_INT_IFDEF(optArgs, int nOctaves, "nOctaves", 4);
	FF_GET_INT_IFDEF(optArgs, int nOctaveLayers, "nOctaveLayers", 4);
	FF_GET_INT_IFDEF(optArgs, int diffusivity, "diffusivity", cv::KAZE::DIFF_PM_G2);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(0, descriptorType, descriptorType);
		FF_ARG_INT_IFDEF(1, descriptorSize, descriptorSize);
		FF_ARG_INT_IFDEF(2, descriptorChannels, descriptorChannels);
		FF_ARG_NUMBER_IFDEF(3, threshold, threshold);
		FF_ARG_INT_IFDEF(4, nOctaves, nOctaves);
		FF_ARG_INT_IFDEF(5, nOctaveLayers, nOctaveLayers);
		FF_ARG_INT_IFDEF(6, diffusivity, diffusivity);
	}

	AKAZEDetector* self = new AKAZEDetector();
	self->Wrap(info.Holder());
	self->detector = cv::AKAZE::create(descriptorType, descriptorSize, descriptorChannels, threshold, nOctaves, nOctaveLayers, diffusivity);
  FF_RETURN(info.Holder());
}