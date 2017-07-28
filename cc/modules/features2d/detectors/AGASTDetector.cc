#include "AGASTDetector.h"

Nan::Persistent<v8::FunctionTemplate> AGASTDetector::constructor;

NAN_MODULE_INIT(AGASTDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(AGASTDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("AGASTDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);
	
	Nan::SetAccessor(instanceTemplate, Nan::New("threshold").ToLocalChecked(), AGASTDetector::GetThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("nonmaxSuppression").ToLocalChecked(), AGASTDetector::GetNonmaxSuppression);
	Nan::SetAccessor(instanceTemplate, Nan::New("type").ToLocalChecked(), AGASTDetector::GetType);

  target->Set(Nan::New("AGASTDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(AGASTDetector::New) {
	if (!info.IsConstructCall()) {
		return Nan::ThrowError("AGASTDetector::New expected new key word");
	}

	int threshold = 10;
	bool nonmaxSuppression = true;
	int type = cv::AgastFeatureDetector::OAST_9_16;

	if (info[0]->IsObject()) {
		v8::Local<v8::Object> args = info[0]->ToObject();
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, threshold, IsInt32, Int32Value)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, nonmaxSuppression, IsBoolean, BooleanValue)
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, type, IsInt32, Int32Value)
	}

	AGASTDetector* self = new AGASTDetector();
	self->Wrap(info.Holder());
	self->detector = cv::AgastFeatureDetector::create(threshold, nonmaxSuppression, type);
  info.GetReturnValue().Set(info.Holder());
}