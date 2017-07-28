#include "FASTDetector.h"

Nan::Persistent<v8::FunctionTemplate> FASTDetector::constructor;

NAN_MODULE_INIT(FASTDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(FASTDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("FASTDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);
	
	Nan::SetAccessor(instanceTemplate, Nan::New("threshold").ToLocalChecked(), FASTDetector::GetThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("nonmaxSuppression").ToLocalChecked(), FASTDetector::GetNonmaxSuppression);
	Nan::SetAccessor(instanceTemplate, Nan::New("type").ToLocalChecked(), FASTDetector::GetType);

  target->Set(Nan::New("FASTDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(FASTDetector::New) {
	if (!info.IsConstructCall()) {
		return Nan::ThrowError("FASTDetector::New expected new key word");
	}

	int threshold = 10;
	bool nonmaxSuppression = true;
	int type = cv::FastFeatureDetector::TYPE_9_16;

	if (info[0]->IsObject()) {
		v8::Local<v8::Object> args = info[0]->ToObject();
		FF_DESTRUCTURE_CHECKED_PROP_IFDEF(args, threshold, IsInt32, Int32Value)
		FF_DESTRUCTURE_CHECKED_PROP_IFDEF(args, nonmaxSuppression, IsBoolean, BooleanValue)
		FF_DESTRUCTURE_CHECKED_PROP_IFDEF(args, type, IsInt32, Int32Value)
	}
	FASTDetector* self = new FASTDetector();
	self->Wrap(info.Holder());
	self->detector = cv::FastFeatureDetector::create(threshold, nonmaxSuppression, type);
  info.GetReturnValue().Set(info.Holder());
}