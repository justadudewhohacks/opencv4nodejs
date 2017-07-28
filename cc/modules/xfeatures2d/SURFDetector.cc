#include "SURFDetector.h"

Nan::Persistent<v8::FunctionTemplate> SURFDetector::constructor;

NAN_MODULE_INIT(SURFDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SURFDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SURFDetector").ToLocalChecked());

	Nan::SetAccessor(instanceTemplate, Nan::New("hessianThreshold").ToLocalChecked(), SURFDetector::GetHessianThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaves").ToLocalChecked(), SURFDetector::GetNOctaves);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaveLayers").ToLocalChecked(), SURFDetector::GetNOctaveLayers);
	Nan::SetAccessor(instanceTemplate, Nan::New("extended").ToLocalChecked(), SURFDetector::GetExtended);
	Nan::SetAccessor(instanceTemplate, Nan::New("upright").ToLocalChecked(), SURFDetector::GetUpright);

  target->Set(Nan::New("SURFDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(SURFDetector::New) {
	if (!info.IsConstructCall()) {
		return Nan::ThrowError("SURFDetector::New expected new key word");
	}

	double hessianThreshold = 100;
	int nOctaves = 4; 
	int nOctaveLayers = 3;
	bool extended = false;
	bool upright = false;

	if (info[0]->IsObject()) {
		v8::Local<v8::Object> args = info[0]->ToObject();
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, hessianThreshold, IsNumber, NumberValue)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, nOctaves, IsInt32, Int32Value)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, nOctaveLayers, IsInt32, Int32Value)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, extended, IsBoolean, BooleanValue)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, upright, IsBoolean, BooleanValue)
	}

	SURFDetector* self = new SURFDetector();
	self->Wrap(info.Holder());
	self->detector = cv::xfeatures2d::SURF::create(hessianThreshold, nOctaves, nOctaveLayers, extended, upright);
  info.GetReturnValue().Set(info.Holder());
}