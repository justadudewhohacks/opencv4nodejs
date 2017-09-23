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
	FF_METHOD_CONTEXT("BRISKDetector::New");
	BRISKDetector* self = new BRISKDetector();

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

	FF_GET_INT_IFDEF(optArgs, self->thresh, "thresh", 30);
	FF_GET_INT_IFDEF(optArgs, self->octaves, "octaves", 3);
	FF_GET_NUMBER_IFDEF(optArgs, self->patternScale, "patternScale", 1.0);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(0, self->thresh, self->thresh);
		FF_ARG_INT_IFDEF(1, self->octaves, self->octaves);
		FF_ARG_NUMBER_IFDEF(2, self->patternScale, self->patternScale);
	}

	self->Wrap(info.Holder());
	self->detector = cv::BRISK::create(self->thresh, self->octaves, (float)self->patternScale);
  FF_RETURN(info.Holder());
}