#include "BFMatcher.h"

Nan::Persistent<v8::FunctionTemplate> BFMatcher::constructor;

NAN_MODULE_INIT(BFMatcher::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(BFMatcher::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("BFMatcher").ToLocalChecked());

	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("normType").ToLocalChecked(), GetNormType);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("crossCheck").ToLocalChecked(), GetCrossCheck);

  target->Set(Nan::New("BFMatcher").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(BFMatcher::New) {
	FF_METHOD_CONTEXT("BFMatcher::New");
	BFMatcher* self = new BFMatcher();
  if (info.Length() > 0) {
		FF_ARG_INT(0, int normType);
		FF_ARG_INT(1, bool crossCheck);

		self->bfmatcher = cv::BFMatcher(normType, crossCheck);
  }
	self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(BFMatcher::Clone) {
  GaussianBlurWorker worker(Mat::Converter::unwrap(info.This()));
  FF_WORKER_SYNC("Mat::GaussianBlur", worker);
  info.GetReturnValue().Set(worker.getReturnValue());
}
