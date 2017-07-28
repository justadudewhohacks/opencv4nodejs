#include "KAZEDetector.h"

Nan::Persistent<v8::FunctionTemplate> KAZEDetector::constructor;

NAN_MODULE_INIT(KAZEDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(KAZEDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("KAZEDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);
	
	Nan::SetAccessor(instanceTemplate, Nan::New("extended").ToLocalChecked(), KAZEDetector::GetExtended);
	Nan::SetAccessor(instanceTemplate, Nan::New("upright").ToLocalChecked(), KAZEDetector::GetUpright);
	Nan::SetAccessor(instanceTemplate, Nan::New("threshold").ToLocalChecked(), KAZEDetector::GetThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaves").ToLocalChecked(), KAZEDetector::GetNOctaves);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaveLayers").ToLocalChecked(), KAZEDetector::GetNOctaveLayers);
	Nan::SetAccessor(instanceTemplate, Nan::New("diffusivity").ToLocalChecked(), KAZEDetector::GetDiffusivity);

  target->Set(Nan::New("KAZEDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(KAZEDetector::New) {
	if (!info.IsConstructCall()) {
		return Nan::ThrowError("KAZEDetector::New expected new key word");
	}

	bool extended = false;
	bool upright = false;
	float threshold = 0.001f;
	int nOctaves = 4;
	int nOctaveLayers = 4;
	int diffusivity = cv::KAZE::DIFF_PM_G2;

	if (info[0]->IsObject()) {
		v8::Local<v8::Object> args = info[0]->ToObject();
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, extended, IsBoolean, BooleanValue)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, upright, IsBoolean, BooleanValue)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, threshold, IsNumber, NumberValue)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, nOctaves, IsInt32, Int32Value)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, nOctaveLayers, IsInt32, Int32Value)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, diffusivity, IsInt32, Int32Value)
	}

	KAZEDetector* self = new KAZEDetector();
	self->Wrap(info.Holder());
	self->detector = cv::KAZE::create(extended, upright, threshold, nOctaves, nOctaveLayers, diffusivity);
  info.GetReturnValue().Set(info.Holder());
}