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
	FF_METHOD_CONTEXT("KAZEDetector::New");

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

	FF_GET_BOOL_IFDEF(optArgs, bool extended, "extended", false);
	FF_GET_BOOL_IFDEF(optArgs, bool upright, "upright", false);
	FF_GET_NUMBER_IFDEF(optArgs, double threshold, "threshold", 0.001f);
	FF_GET_INT_IFDEF(optArgs, int nOctaves, "nOctaves", 4);
	FF_GET_INT_IFDEF(optArgs, int nOctaveLayers, "nOctaveLayers", 4);
	FF_GET_INT_IFDEF(optArgs, int diffusivity, "diffusivity", cv::KAZE::DIFF_PM_G2);
	if (!hasOptArgsObj) {
		FF_ARG_BOOL_IFDEF(0, extended, extended);
		FF_ARG_BOOL_IFDEF(1, upright, upright);
		FF_ARG_NUMBER_IFDEF(2, threshold, threshold);
		FF_ARG_INT_IFDEF(3, nOctaves, nOctaves);
		FF_ARG_INT_IFDEF(4, nOctaveLayers, nOctaveLayers);
		FF_ARG_INT_IFDEF(5, diffusivity, diffusivity);
	}

	KAZEDetector* self = new KAZEDetector();
	self->Wrap(info.Holder());
	self->detector = cv::KAZE::create(extended, upright, threshold, nOctaves, nOctaveLayers, diffusivity);
  FF_RETURN(info.Holder());
}