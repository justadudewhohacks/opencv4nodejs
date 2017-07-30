#include "SIFTDetector.h"

Nan::Persistent<v8::FunctionTemplate> SIFTDetector::constructor;

NAN_MODULE_INIT(SIFTDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SIFTDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SIFTDetector").ToLocalChecked());

	Nan::SetAccessor(instanceTemplate, Nan::New("nFeatures").ToLocalChecked(), SIFTDetector::GetNFeatures);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaveLayers").ToLocalChecked(), SIFTDetector::GeNOctaveLayers);
	Nan::SetAccessor(instanceTemplate, Nan::New("contrastThreshold").ToLocalChecked(), SIFTDetector::GetContrastThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("edgeThreshold").ToLocalChecked(), SIFTDetector::GetEdgeThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("sigma").ToLocalChecked(), SIFTDetector::GetSigma);

  target->Set(Nan::New("SIFTDetector").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(SIFTDetector::New) {
	if (!info.IsConstructCall()) {
		return Nan::ThrowError("SIFTDetector::New expected new key word");
	}
	SIFTDetector* self = new SIFTDetector();
	if (info[0]->IsObject()) {
		v8::Local<v8::Object> args = info[0]->ToObject();
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->nFeatures, nFeatures, IsInt32, Int32Value)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->nOctaveLayers, nOctaveLayers, IsInt32, Int32Value)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->contrastThreshold, contrastThreshold, IsNumber, NumberValue)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->edgeThreshold, edgeThreshold, IsNumber, NumberValue)
		FF_GET_TYPECHECKED_JSPROP_IFDEF(args, self->sigma, sigma, IsNumber, NumberValue)
	}

	self->Wrap(info.Holder());
	self->detector = cv::xfeatures2d::SIFT::create(self->nFeatures, self->nOctaveLayers, self->contrastThreshold, self->edgeThreshold, self->sigma);
  info.GetReturnValue().Set(info.Holder());
}
