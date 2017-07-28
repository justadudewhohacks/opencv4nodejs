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
	if (!info.IsConstructCall()) {
		return Nan::ThrowError("AKAZEDetector::New expected new key word");
	}

	int descriptorType = cv::AKAZE::DESCRIPTOR_MLDB;
	int descriptorSize = 0; 
	int descriptorChannels = 3;
	float threshold = 0.001f; 
	int nOctaves = 4;
	int nOctaveLayers = 4; 
	int diffusivity = cv::KAZE::DIFF_PM_G2;

	if (info[0]->IsObject()) {
		v8::Local<v8::Object> args = info[0]->ToObject();
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, descriptorType, IsInt32, Int32Value)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, descriptorSize, IsInt32, Int32Value)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, descriptorChannels, IsInt32, Int32Value)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, threshold, IsNumber, NumberValue)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, nOctaves, IsInt32, Int32Value)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, nOctaveLayers, IsInt32, Int32Value)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, diffusivity, IsInt32, Int32Value)
	}

	AKAZEDetector* self = new AKAZEDetector();
	self->Wrap(info.Holder());
	self->detector = cv::AKAZE::create(descriptorType, descriptorSize, descriptorChannels, threshold, nOctaves, nOctaveLayers, diffusivity);
  info.GetReturnValue().Set(info.Holder());
}