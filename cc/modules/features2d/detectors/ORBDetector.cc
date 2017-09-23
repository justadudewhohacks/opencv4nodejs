#include "ORBDetector.h"

Nan::Persistent<v8::FunctionTemplate> ORBDetector::constructor;

NAN_MODULE_INIT(ORBDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(ORBDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("ORBDetector").ToLocalChecked());

	Nan::SetAccessor(instanceTemplate, Nan::New("nfeatures").ToLocalChecked(), ORBDetector::GetNFeatures);
	Nan::SetAccessor(instanceTemplate, Nan::New("scaleFactor").ToLocalChecked(), ORBDetector::GetScaleFactor);
	Nan::SetAccessor(instanceTemplate, Nan::New("nlevels").ToLocalChecked(), ORBDetector::GetNlevels);
	Nan::SetAccessor(instanceTemplate, Nan::New("edgeThreshold").ToLocalChecked(), ORBDetector::GetEdgeThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("firstLevel").ToLocalChecked(), ORBDetector::GetFirstLevel);
	Nan::SetAccessor(instanceTemplate, Nan::New("WTA_K").ToLocalChecked(), ORBDetector::GetWTA_K);
	Nan::SetAccessor(instanceTemplate, Nan::New("scoreType").ToLocalChecked(), ORBDetector::GetScoreType);
	Nan::SetAccessor(instanceTemplate, Nan::New("patchSize").ToLocalChecked(), ORBDetector::GetPatchSize);
	Nan::SetAccessor(instanceTemplate, Nan::New("fastThreshold").ToLocalChecked(), ORBDetector::GetFastThreshold);

  target->Set(Nan::New("ORBDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(ORBDetector::New) {
	FF_METHOD_CONTEXT("ORBDetector::New");

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

	FF_GET_INT_IFDEF(optArgs, int nfeatures, "nfeatures", 500);
	FF_GET_NUMBER_IFDEF(optArgs, double scaleFactor, "scaleFactor", 1.2f);
	FF_GET_INT_IFDEF(optArgs, int nlevels, "nlevels", 8);
	FF_GET_INT_IFDEF(optArgs, int edgeThreshold, "edgeThreshold", 31);
	FF_GET_INT_IFDEF(optArgs, int firstLevel, "firstLevel", 0);
	FF_GET_INT_IFDEF(optArgs, int WTA_K, "WTA_K", 2);
	FF_GET_INT_IFDEF(optArgs, int scoreType, "scoreType", cv::ORB::HARRIS_SCORE);
	FF_GET_INT_IFDEF(optArgs, int patchSize, "patchSize", 31);
	FF_GET_INT_IFDEF(optArgs, int fastThreshold, "fastThreshold", 20);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(0, nfeatures, nfeatures);
		FF_ARG_NUMBER_IFDEF(1, scaleFactor, scaleFactor);
		FF_ARG_INT_IFDEF(2, nlevels, nlevels);
		FF_ARG_INT_IFDEF(3, edgeThreshold, edgeThreshold);
		FF_ARG_INT_IFDEF(4, firstLevel, firstLevel);
		FF_ARG_INT_IFDEF(5, WTA_K, WTA_K);
		FF_ARG_INT_IFDEF(6, scoreType, scoreType);
		FF_ARG_INT_IFDEF(7, patchSize, patchSize);
		FF_ARG_INT_IFDEF(8, fastThreshold, fastThreshold);
	}

	ORBDetector* self = new ORBDetector();
	self->Wrap(info.Holder());
	self->detector = cv::ORB::create(nfeatures, scaleFactor, nlevels, edgeThreshold, firstLevel, WTA_K, scoreType, patchSize, fastThreshold);
  FF_RETURN(info.Holder());
}