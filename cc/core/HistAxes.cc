//
// Created by stefan on 11/4/19.
//

#include "HistAxes.h"

Nan::Persistent<v8::FunctionTemplate> HistAxes::constructor;

NAN_MODULE_INIT(HistAxes::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(HistAxes::New);
  HistAxes::constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("HistAxes").ToLocalChecked());

  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("bins").ToLocalChecked(), HistAxes::bins_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("channel").ToLocalChecked(), HistAxes::channel_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("ranges").ToLocalChecked(), HistAxes::ranges_getter);

  Nan::Set(target, Nan::New("HistAxes").ToLocalChecked(), FF::getFunction(ctor));
}

NAN_METHOD(HistAxes::New) {
  FF::TryCatch tryCatch("HistAxes::New");
  FF_ASSERT_CONSTRUCT_CALL();
  if (info.Length() != 1) {
    return tryCatch.throwError("expected one argument");
  }
  if (!info[0]->IsObject()) {
    return tryCatch.throwError("expected arg0 to be an object");
  }

  HistAxes *self = new HistAxes();

  auto jsAxis = Nan::To<v8::Object>(info[0]).ToLocalChecked();

  if (!FF::hasOwnProperty(jsAxis, "ranges")) {
    return tryCatch.throwError("expected object to have ranges");
  }
  if (!FF::hasOwnProperty(jsAxis, "bins")) {
    return tryCatch.throwError("expected object to have bins");
  }
  if (!FF::hasOwnProperty(jsAxis, "channel")) {
    return tryCatch.throwError("expected object to have channel");
  }

  v8::Local<v8::Value> jsRangesVal = Nan::Get(jsAxis, Nan::New("ranges").ToLocalChecked()).ToLocalChecked();
  v8::Local<v8::Array> jsRanges = v8::Local<v8::Array>::Cast(jsRangesVal);

  if (
      jsRanges->Length() != 2 ||
      !Nan::Get(jsRanges, 0).ToLocalChecked()->IsNumber() ||
      !Nan::Get(jsRanges, 1).ToLocalChecked()->IsNumber()
      ) {
    return tryCatch.throwError("expected ranges to be an array with 2 numbers");
  }

  FF::DoubleArrayConverter::unwrapTo(&self->self.range, jsRanges);

  FF::IntConverter::prop(&self->self.channel, "channel", jsAxis);
  FF::IntConverter::prop(&self->self.bins, "bins", jsAxis);

  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}