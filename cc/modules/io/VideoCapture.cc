#include "VideoCapture.h"
#include "Workers.h"

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

NAN_METHOD(VideoCapture::Read) {
	FF_OBJ jsMat = FF_NEW_INSTANCE(Mat::constructor);
	FF_UNWRAP(info.This(), VideoCapture)->cap.read(FF_UNWRAP_MAT_AND_GET(jsMat));
	FF_RETURN(jsMat);
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

NAN_METHOD(VideoCapture::ReadAsync) {
	FF_METHOD_CONTEXT("VideoCapture::ReadAsync");

	ReadContext ctx;
	ctx.cap = FF_UNWRAP(info.This(), VideoCapture)->cap;

	FF_ARG_FUNC(0, v8::Local<v8::Function> cbFunc);
	Nan::AsyncQueueWorker(new GenericAsyncWorker<ReadContext>(
		new Nan::Callback(cbFunc),
		ctx
	));
}

NAN_METHOD(VideoCapture::Get) {
	FF_METHOD_CONTEXT("VideoCapture::Get");
	FF_ARG_INT(0, int prop);
	FF_RETURN(FF_UNWRAP(info.This(), VideoCapture)->cap.get(prop));
}

NAN_METHOD(VideoCapture::Set) {
	FF_METHOD_CONTEXT("VideoCapture::Set");
	FF_ARG_INT(0, int prop);
	FF_ARG_NUMBER(1, double value);
	FF_UNWRAP(info.This(), VideoCapture)->cap.set(prop, value);
}