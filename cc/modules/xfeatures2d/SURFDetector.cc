#ifdef HAVE_XFEATURES2D

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
	FF_METHOD_CONTEXT("SURFDetector::New");
	SURFDetector* self = new SURFDetector();

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

	FF_GET_NUMBER_IFDEF(optArgs, double hessianThreshold, "hessianThreshold", 100);
	FF_GET_INT_IFDEF(optArgs, int nOctaves, "nOctaves", 4);
	FF_GET_INT_IFDEF(optArgs, int nOctaveLayers, "nOctaveLayers", 3);
	FF_GET_BOOL_IFDEF(optArgs, bool extended, "extended", false);
	FF_GET_BOOL_IFDEF(optArgs, bool upright, "upright", false);
	if (!hasOptArgsObj) {
		FF_ARG_NUMBER_IFDEF(0, hessianThreshold, hessianThreshold);
		FF_ARG_INT_IFDEF(1, nOctaves, nOctaves);
		FF_ARG_INT_IFDEF(2, nOctaveLayers, nOctaveLayers);
		FF_ARG_BOOL_IFDEF(3, extended, extended);
		FF_ARG_BOOL_IFDEF(4, upright, upright);
	}

	self->Wrap(info.Holder());
	self->detector = cv::xfeatures2d::SURF::create(
		hessianThreshold,
		nOctaves, 
		nOctaveLayers, 
		extended, 
		upright
	);
  FF_RETURN(info.Holder());
}

#endif // HAVE_XFEATURES2D