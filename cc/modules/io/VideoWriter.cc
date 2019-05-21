#include "VideoWriter.h"
#include "VideoWriterBindings.h"

Nan::Persistent<v8::FunctionTemplate> VideoWriter::constructor;

NAN_MODULE_INIT(VideoWriter::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(VideoWriter::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF::newString("VideoWriter"));
  Nan::SetMethod(ctor, "fourcc", Fourcc);
  Nan::SetPrototypeMethod(ctor, "write", Write);
  Nan::SetPrototypeMethod(ctor, "writeAsync", WriteAsync);
  Nan::SetPrototypeMethod(ctor, "get", Get);
  Nan::SetPrototypeMethod(ctor, "getAsync", GetAsync);
  Nan::SetPrototypeMethod(ctor, "set", Set);
  Nan::SetPrototypeMethod(ctor, "setAsync", SetAsync);
  Nan::SetPrototypeMethod(ctor, "release", Release);
  target->Set(FF::newString("VideoWriter"), FF::getFunction(ctor));
};

NAN_METHOD(VideoWriter::New) {
	FF_ASSERT_CONSTRUCT_CALL(VideoWriter);
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
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(VideoWriter::Release) {
	Nan::ObjectWrap::Unwrap<VideoWriter>(info.This())->writer.release();
}

NAN_METHOD(VideoWriter::Get) {
	FF::SyncBinding(
		std::make_shared<VideoWriterBindings::GetWorker>(VideoWriter::Converter::unwrap(info.This())),
		"VideoWriter::Get",
		info
	);
}

NAN_METHOD(VideoWriter::GetAsync) {
	FF::AsyncBinding(
		std::make_shared<VideoWriterBindings::GetWorker>(VideoWriter::Converter::unwrap(info.This())),
		"VideoWriter::GetAsync",
		info
	);
}

NAN_METHOD(VideoWriter::Set) {
	FF::SyncBinding(
		std::make_shared<VideoWriterBindings::SetWorker>(VideoWriter::Converter::unwrap(info.This())),
		"VideoCaptureVideoWriter::Set",
		info
	);
}

NAN_METHOD(VideoWriter::SetAsync) {
	FF::AsyncBinding(
		std::make_shared<VideoWriterBindings::SetWorker>(VideoWriter::Converter::unwrap(info.This())),
		"VideoWriter::SetAsync",
		info
	);
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
