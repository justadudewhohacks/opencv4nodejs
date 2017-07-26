#include "BRISKDetector.h"

Nan::Persistent<v8::FunctionTemplate> BRISKDetector::constructor;

NAN_MODULE_INIT(BRISKDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(BRISKDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("BRISKDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);
	
	//Nan::SetAccessor(instanceTemplate, Nan::New("thresh").ToLocalChecked(), BRISKDetector::GetThresh);
	//Nan::SetAccessor(instanceTemplate, Nan::New("octaves").ToLocalChecked(), BRISKDetector::GetOctaves);
	//Nan::SetAccessor(instanceTemplate, Nan::New("patternScale").ToLocalChecked(), BRISKDetector::GetPatternScale);

  target->Set(Nan::New("BRISKDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(BRISKDetector::New) {
	if (!info.IsConstructCall()) {
		return Nan::ThrowError("BRISKDetector::New expected new key word");
	}

	int thresh = 30; 
	int octaves = 3;
	float patternScale = 1.0f;

	if (info[0]->IsObject()) {
		v8::Local<v8::Object> args = info[0]->ToObject();
		FF_GET_CHECKED_PROP_IFDEF(args, thresh, IsInt32, Int32Value)
		FF_GET_CHECKED_PROP_IFDEF(args, octaves, IsInt32, Int32Value)
		FF_GET_CHECKED_PROP_IFDEF(args, patternScale, IsNumber, NumberValue)
	}
	BRISKDetector* self = new BRISKDetector();
	self->Wrap(info.Holder());
	self->detector = cv::BRISK::create(thresh, octaves, patternScale);
  info.GetReturnValue().Set(info.Holder());
}