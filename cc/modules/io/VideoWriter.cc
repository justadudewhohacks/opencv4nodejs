#include "VideoWriter.h"
#include "VideoWriterBindings.h"

Nan::Persistent<v8::FunctionTemplate> VideoWriter::constructor;

NAN_MODULE_INIT(VideoWriter::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(VideoWriter::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF_NEW_STRING("VideoWriter"));
  Nan::SetMethod(ctor, "fourcc", Fourcc);
  Nan::SetPrototypeMethod(ctor, "write", Write);
  Nan::SetPrototypeMethod(ctor, "writeAsync", WriteAsync);
  Nan::SetPrototypeMethod(ctor, "get", Get);
  Nan::SetPrototypeMethod(ctor, "set", Set);
  Nan::SetPrototypeMethod(ctor, "release", Release);
  target->Set(FF_NEW_STRING("VideoWriter"), ctor->GetFunction());
};

NAN_METHOD(VideoWriter::Get) {
  FF_METHOD_CONTEXT("VideoWriter::Get");
  FF_ARG_INT(0, int prop);
  FF_RETURN(FF_UNWRAP(info.This(), VideoWriter)->writer.get(prop));
}

NAN_METHOD(VideoWriter::Set) {
  FF_METHOD_CONTEXT("VideoWriter::Set");
  FF_ARG_INT(0, int prop);
  FF_ARG_NUMBER(1, double value);
  FF_UNWRAP(info.This(), VideoWriter)->writer.set(prop, value);
}

NAN_METHOD(VideoWriter::Release) {
  FF_UNWRAP(info.This(), VideoWriter)->writer.release();
}

NAN_METHOD(VideoWriter::New) {
  FF::TryCatch tryCatch;
  VideoWriterBindings::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    v8::Local<v8::Value> err = tryCatch.formatCatchedError("VideoWriter::New");
    tryCatch.throwNew(err);
    return;
  }

  VideoWriter* self = new VideoWriter();
  self->writer.open(worker.fileName, worker.fourccCode, worker.fps, (cv::Size)worker.frameSize, worker.isColor);
  self->Wrap(info.Holder());
  FF_RETURN(info.Holder());
}

NAN_METHOD(VideoWriter::Fourcc) {
  FF::SyncBinding(
    std::make_shared<VideoWriterBindings::FourccWorker>(),
    "VideoWriter::Fourcc",
    info
  );
}

NAN_METHOD(VideoWriter::Write) {
  FF::SyncBinding(
    std::make_shared<VideoWriterBindings::WriteWorker>(VideoWriter::Converter::unwrap(info.This())),
    "VideoWriter::Write",
    info
  );
}

NAN_METHOD(VideoWriter::WriteAsync) {
  FF::AsyncBinding(
    std::make_shared<VideoWriterBindings::WriteWorker>(VideoWriter::Converter::unwrap(info.This())),
    "VideoWriter::WriteAsync",
    info
  );
}
