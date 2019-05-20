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
  Nan::SetPrototypeMethod(ctor, "getAsync", GetAsync);
  Nan::SetPrototypeMethod(ctor, "set", Set);
  Nan::SetPrototypeMethod(ctor, "setAsync", SetAsync);
  Nan::SetPrototypeMethod(ctor, "release", Release);
  target->Set(FF_NEW_STRING("VideoCapture"), FF::getFunction(ctor));
};

NAN_METHOD(VideoCapture::New) {
  FF_ASSERT_CONSTRUCT_CALL(VideoCapture);
  FF_METHOD_CONTEXT("VideoCapture::New");
  VideoCapture* self = new VideoCapture();
  if (info[0]->IsString()) {
    self->path = FF_CAST_STRING(info[0]);
    self->cap.open(self->path);
  }
  else if (info[0]->IsUint32()) {
    self->cap.open(info[0]->ToUint32(Nan::GetCurrentContext()).ToLocalChecked()->Value());
  }
  else {
    FF_THROW("expected arg 0 to be path or device port");
  }
  if (!self->cap.isOpened()) {
    FF_THROW("failed to open capture");
  }

  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(VideoCapture::Reset) {
  VideoCapture* self = Nan::ObjectWrap::Unwrap<VideoCapture>(info.This());
  self->cap.release();
  self->cap.open(self->path);
  if (!self->cap.isOpened()) {
	return Nan::ThrowError(FF_NEW_STRING(std::string("VideoCapture::Reset") + " - " + std::string("failed to reset capture")));
  }
}

NAN_METHOD(VideoCapture::Release) {
	Nan::ObjectWrap::Unwrap<VideoCapture>(info.This())->cap.release();
}

NAN_METHOD(VideoCapture::Get) {
	FF::SyncBinding(
		std::make_shared<VideoCaptureBindings::GetWorker>(VideoCapture::Converter::unwrap(info.This())),
		"VideoCapture::Get",
		info
	);
}

NAN_METHOD(VideoCapture::GetAsync) {
	FF::AsyncBinding(
		std::make_shared<VideoCaptureBindings::GetWorker>(VideoCapture::Converter::unwrap(info.This())),
		"VideoCapture::GetAsync",
		info
	);
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
