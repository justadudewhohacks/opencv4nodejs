#include "DetectionROI.h"

Nan::Persistent<v8::FunctionTemplate> DetectionROI::constructor;

NAN_MODULE_INIT(DetectionROI::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(DetectionROI::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("DetectionROI"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("scale"), scaleGet, scaleSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("locations"), locationsGet, locationsSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("confidences"), confidencesGet, confidencesSet);

	target->Set(FF_NEW_STRING("DetectionROI"), ctor->GetFunction());
};

NAN_METHOD(DetectionROI::New) {
	DetectionROI* self = new DetectionROI();
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};