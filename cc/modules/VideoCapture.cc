#include "VideoCapture.h"

Nan::Persistent<v8::FunctionTemplate> VideoCapture::constructor;

NAN_MODULE_INIT(VideoCapture::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(VideoCapture::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF_V8STRING("VideoCapture"));
	Nan::SetPrototypeMethod(ctor, "read", Read);
  Nan::SetPrototypeMethod(ctor, "reset", Reset);
  target->Set(FF_V8STRING("VideoCapture"), ctor->GetFunction());
};

NAN_METHOD(VideoCapture::New) {
	VideoCapture* self = new VideoCapture();
	if (info[0]->IsString()) {
		self->path = FF_TO_STRING(info[0]);
		self->cap.open(self->path);
	}
	else if (info[0]->IsUint32()) {
		self->cap.open(info[0]->Uint32Value());
	}
	else {
		return Nan::ThrowError("VideoCapture::New expected arg0 to be path or device port");
	}
	if (!self->cap.isOpened()) {
		return Nan::ThrowError("VideoCapture::New failed to open capture");
	}

	self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(VideoCapture::Read) {
	v8::Local<v8::Object> jsMat = FF_NEW(Mat::constructor);
	FF_UNWRAP(info.This(), VideoCapture)->cap.read(FF_UNWRAP_MAT_AND_GET(jsMat));
	info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(VideoCapture::Reset) {
	VideoCapture* self = FF_UNWRAP(info.This(), VideoCapture);
	self->cap.release();
	self->cap.open(self->path);
	if (!self->cap.isOpened()) {
		return Nan::ThrowError("VideoCapture::Reset failed to reset capture");
	}
}