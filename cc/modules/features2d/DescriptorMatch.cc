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
	DescriptorMatch* self = new DescriptorMatch();
  if (info.Length() > 0) {
		v8::Local<v8::Object> args = info[0]->ToObject();
		FF_GET_TYPECHECKED_JSPROP_REQUIRED(args, self->queryIdx, queryIdx, IsInt32, Int32Value);
		FF_GET_TYPECHECKED_JSPROP_REQUIRED(args, self->trainIdx, trainIdx, IsInt32, Int32Value);
		FF_GET_TYPECHECKED_JSPROP_REQUIRED(args, self->distance, distance, IsNumber, NumberValue);
  }
	self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

void DescriptorMatch::setNativeProps(cv::DMatch dmatch) {
	this->queryIdx = dmatch.queryIdx;
	this->trainIdx = dmatch.trainIdx;
	this->distance = dmatch.distance;
}