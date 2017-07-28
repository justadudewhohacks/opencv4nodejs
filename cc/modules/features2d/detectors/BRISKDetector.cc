#include "BRISKDetector.h"

Nan::Persistent<v8::FunctionTemplate> BRISKDetector::constructor;

NAN_MODULE_INIT(BRISKDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(BRISKDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("BRISKDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);
	
	Nan::SetAccessor(instanceTemplate, Nan::New("thresh").ToLocalChecked(), BRISKDetector::GetThresh);
	Nan::SetAccessor(instanceTemplate, Nan::New("octaves").ToLocalChecked(), BRISKDetector::GetOctaves);
	Nan::SetAccessor(instanceTemplate, Nan::New("patternScale").ToLocalChecked(), BRISKDetector::GetPatternScale);

  target->Set(Nan::New("BRISKDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(BRISKDetector::New) {
	if (!info.IsConstructCall()) {
		return Nan::ThrowError("BRISKDetector::New expected new key word");
	}

	BRISKDetector* self = new BRISKDetector();
	if (info[0]->IsObject()) {
		v8::Local<v8::Object> args = info[0]->ToObject();	
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->thresh, thresh, IsInt32, Int32Value)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->octaves, octaves, IsInt32, Int32Value)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->patternScale, patternScale, IsNumber, NumberValue)
	}
	
	self->Wrap(info.Holder());
	self->detector = cv::BRISK::create(self->thresh, self->octaves, (float)self->patternScale);
  info.GetReturnValue().Set(info.Holder());
}