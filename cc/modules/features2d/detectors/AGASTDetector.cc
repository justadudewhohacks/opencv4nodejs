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
	FF_METHOD_CONTEXT("AGASTDetector::New");

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

	FF_GET_INT_IFDEF(optArgs, int threshold, "threshold", 10);
	FF_GET_BOOL_IFDEF(optArgs, bool nonmaxSuppression, "nonmaxSuppression", true);
	FF_GET_INT_IFDEF(optArgs, int type, "type", cv::AgastFeatureDetector::OAST_9_16);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(0, threshold, threshold);
		FF_ARG_BOOL_IFDEF(1, nonmaxSuppression, nonmaxSuppression);
		FF_ARG_INT_IFDEF(2, type, type);
	}

	AGASTDetector* self = new AGASTDetector();
	self->Wrap(info.Holder());
	self->detector = cv::AgastFeatureDetector::create(threshold, nonmaxSuppression, type);
  FF_RETURN(info.Holder());
}