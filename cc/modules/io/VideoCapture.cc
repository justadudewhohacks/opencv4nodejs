#include "VideoCapture.h"
#include "VideoCaptureBindings.h"

Nan::Persistent<v8::FunctionTemplate> VideoCapture::constructor;

NAN_MODULE_INIT(VideoCapture::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(VideoCapture::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF_NEW_STRING("VideoCapture"));
  Nan::SetPrototypeMethod(ctor, "read", Read);
  Nan::SetPrototypeMethod(ctor, "reset", Reset);
  Nan::SetPrototypeMethod(ctor, "readAsync", ReadAsync);
  Nan::SetPrototypeMethod(ctor, "get", Get);
  Nan::SetPrototypeMethod(ctor, "set", Set);
  Nan::SetPrototypeMethod(ctor, "setAsync", SetAsync);
  Nan::SetPrototypeMethod(ctor, "release", Release);
  target->Set(FF_NEW_STRING("VideoCapture"), ctor->GetFunction());
};

NAN_METHOD(VideoCapture::New) {
  FF_METHOD_CONTEXT("VideoCapture::New");
  VideoCapture* self = new VideoCapture();
  if (info[0]->IsString()) {
    self->path = FF_CAST_STRING(info[0]);
    self->cap.open(self->path);
  }
  else if (info[0]->IsUint32()) {
    self->cap.open(info[0]->Uint32Value());
  }
  else {
    FF_THROW("expected arg 0 to be path or device port");
  }
  if (!self->cap.isOpened()) {
    FF_THROW("failed to open capture");
  }

  self->Wrap(info.Holder());
  FF_RETURN(info.Holder());
}

NAN_METHOD(VideoCapture::Reset) {
  FF_METHOD_CONTEXT("VideoCapture::Reset");
  VideoCapture* self = FF_UNWRAP(info.This(), VideoCapture);
  self->cap.release();
  self->cap.open(self->path);
  if (!self->cap.isOpened()) {
    FF_THROW("failed to reset capture");
  }
}

NAN_METHOD(VideoCapture::Get) {
  FF_METHOD_CONTEXT("VideoCapture::Get");
  FF_ARG_INT(0, int prop);
  FF_RETURN(FF_UNWRAP(info.This(), VideoCapture)->cap.get(prop));
}

NAN_METHOD(VideoCapture::Release) {
  FF_UNWRAP(info.This(), VideoCapture)->cap.release();
}

NAN_METHOD(VideoCapture::Read) {
  FF::SyncBinding(
    std::make_shared<VideoCaptureBindings::ReadWorker>(VideoCapture::Converter::unwrap(info.This())),
    "VideoCapture::Read",
    info
  );
}

NAN_METHOD(VideoCapture::ReadAsync) {
  FF::AsyncBinding(
    std::make_shared<VideoCaptureBindings::ReadWorker>(VideoCapture::Converter::unwrap(info.This())),
    "VideoCapture::ReadAsync",
    info
  );
}

NAN_METHOD(VideoCapture::Set) {
  FF::SyncBinding(
    std::make_shared<VideoCaptureBindings::SetWorker>(VideoCapture::Converter::unwrap(info.This())),
    "VideoCapture::Set",
    info
  );
}

NAN_METHOD(VideoCapture::SetAsync) {
  FF::AsyncBinding(
    std::make_shared<VideoCaptureBindings::SetWorker>(VideoCapture::Converter::unwrap(info.This())),
    "VideoCapture::SetAsync",
    info
  );
}
