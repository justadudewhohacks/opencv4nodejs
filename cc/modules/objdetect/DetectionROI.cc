#include "DetectionROI.h"

Nan::Persistent<v8::FunctionTemplate> DetectionROI::constructor;

NAN_MODULE_INIT(DetectionROI::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(DetectionROI::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("DetectionROI"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF::newString("scale"), scaleGet, scaleSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("locations"), locationsGet, locationsSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("confidences"), confidencesGet, confidencesSet);

	Nan::Set(target,FF::newString("DetectionROI"), FF::getFunction(ctor));
};

NAN_METHOD(DetectionROI::New) {
	FF::TryCatch tryCatch("DetectionROI::New");
	FF_ASSERT_CONSTRUCT_CALL();
	DetectionROI* self = new DetectionROI();
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};
