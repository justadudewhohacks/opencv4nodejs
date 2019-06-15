#include "opencv_modules.h"

#ifdef HAVE_IO

#include "VideoCapture.h"
#include "VideoCaptureBindings.h"

Nan::Persistent<v8::FunctionTemplate> VideoCapture::constructor;

NAN_MODULE_INIT(VideoCapture::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(VideoCapture::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF::newString("VideoCapture"));
  Nan::SetPrototypeMethod(ctor, "read", Read);
  Nan::SetPrototypeMethod(ctor, "reset", Reset);
  Nan::SetPrototypeMethod(ctor, "readAsync", ReadAsync);
  Nan::SetPrototypeMethod(ctor, "get", Get);
  Nan::SetPrototypeMethod(ctor, "getAsync", GetAsync);
  Nan::SetPrototypeMethod(ctor, "set", Set);
  Nan::SetPrototypeMethod(ctor, "setAsync", SetAsync);
  Nan::SetPrototypeMethod(ctor, "release", Release);
  Nan::Set(target,FF::newString("VideoCapture"), FF::getFunction(ctor));
};

NAN_METHOD(VideoCapture::New) {
	FF::TryCatch tryCatch("VideoCapture::New");
  FF_ASSERT_CONSTRUCT_CALL();
  VideoCapture* self = new VideoCapture();
  if (info[0]->IsString()) {
    self->path = FF::StringConverter::unwrapUnchecked(info[0]);
    self->self.open(self->path);
  }
  else if (info[0]->IsUint32()) {
    self->self.open(info[0]->ToUint32(Nan::GetCurrentContext()).ToLocalChecked()->Value());
  }
  else {
    return tryCatch.throwError("expected arg 0 to be path or device port");
  }
  if (!self->self.isOpened()) {
    return tryCatch.throwError("failed to open capture");
  }

  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(VideoCapture::Reset) {
	FF::TryCatch tryCatch("VideoCapture::Reset");
  VideoCapture* self = Nan::ObjectWrap::Unwrap<VideoCapture>(info.This());
  self->self.release();
  self->self.open(self->path);
  if (!self->self.isOpened()) {
	return tryCatch.throwError("failed to reset capture");
  }
}

NAN_METHOD(VideoCapture::Release) {
	Nan::ObjectWrap::Unwrap<VideoCapture>(info.This())->self.release();
}

NAN_METHOD(VideoCapture::Get) {
	FF::executeSyncBinding(
		std::make_shared<VideoCaptureBindings::GetWorker>(VideoCapture::unwrapSelf(info)),
		"VideoCapture::Get",
		info
	);
}

NAN_METHOD(VideoCapture::GetAsync) {
	FF::executeAsyncBinding(
		std::make_shared<VideoCaptureBindings::GetWorker>(VideoCapture::unwrapSelf(info)),
		"VideoCapture::GetAsync",
		info
	);
}

NAN_METHOD(VideoCapture::Read) {
  FF::executeSyncBinding(
    std::make_shared<VideoCaptureBindings::ReadWorker>(VideoCapture::unwrapSelf(info)),
    "VideoCapture::Read",
    info
  );
}

NAN_METHOD(VideoCapture::ReadAsync) {
  FF::executeAsyncBinding(
    std::make_shared<VideoCaptureBindings::ReadWorker>(VideoCapture::unwrapSelf(info)),
    "VideoCapture::ReadAsync",
    info
  );
}

NAN_METHOD(VideoCapture::Set) {
  FF::executeSyncBinding(
    std::make_shared<VideoCaptureBindings::SetWorker>(VideoCapture::unwrapSelf(info)),
    "VideoCapture::Set",
    info
  );
}

NAN_METHOD(VideoCapture::SetAsync) {
  FF::executeAsyncBinding(
    std::make_shared<VideoCaptureBindings::SetWorker>(VideoCapture::unwrapSelf(info)),
    "VideoCapture::SetAsync",
    info
  );
}

#endif