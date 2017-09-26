#include "DescriptorMatch.h"

Nan::Persistent<v8::FunctionTemplate> DescriptorMatch::constructor;

NAN_MODULE_INIT(DescriptorMatch::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(DescriptorMatch::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("DescriptorMatch").ToLocalChecked());

	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("queryIdx").ToLocalChecked(), GetQueryIdx);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("trainIdx").ToLocalChecked(), GetTrainIdx);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("distance").ToLocalChecked(), GetDistance);

  target->Set(Nan::New("DescriptorMatch").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(DescriptorMatch::New) {
	FF_METHOD_CONTEXT("DescriptorMatch::New");
	DescriptorMatch* self = new DescriptorMatch();
  if (info.Length() > 0) {
		FF_ARG_INT(0, int queryIdx);
		FF_ARG_INT(1, int trainIdx);
		FF_ARG_NUMBER(2, double distance);
		self->dmatch = cv::DMatch(queryIdx, trainIdx, distance);
  }
	self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}