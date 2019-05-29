#include "FeatureSet.h"
#include "Mat.h"

Nan::Persistent<v8::FunctionTemplate> FeatureSet::constructor;

NAN_MODULE_INIT(FeatureSet::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(FeatureSet::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("FeatureSet").ToLocalChecked());

	target->Set(Nan::New("FeatureSet").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(FeatureSet::New) {
  FF_ASSERT_CONSTRUCT_CALL(FeatureSet);
	FeatureSet* self = new FeatureSet();

	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};