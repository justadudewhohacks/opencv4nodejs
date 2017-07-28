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
	if (!info.IsConstructCall()) {
		return Nan::ThrowError("ORBDetector::New expected new key word");
	}

	int nfeatures = 500; 
	float scaleFactor = 1.2f; 
	int nlevels = 8; 
	int edgeThreshold = 31;
	int firstLevel = 0;
	int WTA_K = 2;
	int scoreType = cv::ORB::HARRIS_SCORE; 
	int patchSize = 31;
	int fastThreshold = 20;

	if (info[0]->IsObject()) {
		v8::Local<v8::Object> args = info[0]->ToObject();
		FF_DESTRUCTURE_CHECKED_PROP_IFDEF(args, nfeatures, IsInt32, Int32Value)
		FF_DESTRUCTURE_CHECKED_PROP_IFDEF(args, scaleFactor, IsNumber, NumberValue)
		FF_DESTRUCTURE_CHECKED_PROP_IFDEF(args, nlevels, IsInt32, Int32Value)
		FF_DESTRUCTURE_CHECKED_PROP_IFDEF(args, edgeThreshold, IsInt32, Int32Value)
		FF_DESTRUCTURE_CHECKED_PROP_IFDEF(args, firstLevel, IsInt32, Int32Value)
		FF_DESTRUCTURE_CHECKED_PROP_IFDEF(args, WTA_K, IsInt32, Int32Value)
		FF_DESTRUCTURE_CHECKED_PROP_IFDEF(args, scoreType, IsInt32, Int32Value)
		FF_DESTRUCTURE_CHECKED_PROP_IFDEF(args, patchSize, IsInt32, Int32Value)
		FF_DESTRUCTURE_CHECKED_PROP_IFDEF(args, fastThreshold, IsInt32, Int32Value)
	}

	ORBDetector* self = new ORBDetector();
	self->Wrap(info.Holder());
	self->detector = cv::ORB::create(nfeatures, scaleFactor, nlevels, edgeThreshold, firstLevel, WTA_K, scoreType, patchSize, fastThreshold);
  info.GetReturnValue().Set(info.Holder());
}