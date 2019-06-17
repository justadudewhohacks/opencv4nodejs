#include "opencv_modules.h"

#ifdef HAVE_IO

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
  Nan::Set(target,FF::newString("VideoWriter"), FF::getFunction(ctor));
};

NAN_METHOD(VideoWriter::New) {
	FF::TryCatch tryCatch("VideoWriter::New");
	FF_ASSERT_CONSTRUCT_CALL();
	VideoWriterBindings::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	VideoWriter* self = new VideoWriter();
	self->self.open(worker.fileName, worker.fourccCode, worker.fps, (cv::Size)worker.frameSize, worker.isColor);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(VideoWriter::Release) {
	Nan::ObjectWrap::Unwrap<VideoWriter>(info.This())->self.release();
}

NAN_METHOD(VideoWriter::Get) {
	FF::executeSyncBinding(
		std::make_shared<VideoWriterBindings::GetWorker>(VideoWriter::unwrapSelf(info)),
		"VideoWriter::Get",
		info
	);
}

NAN_METHOD(VideoWriter::GetAsync) {
	FF::executeAsyncBinding(
		std::make_shared<VideoWriterBindings::GetWorker>(VideoWriter::unwrapSelf(info)),
		"VideoWriter::GetAsync",
		info
	);
}

NAN_METHOD(VideoWriter::Set) {
	FF::executeSyncBinding(
		std::make_shared<VideoWriterBindings::SetWorker>(VideoWriter::unwrapSelf(info)),
		"VideoCaptureVideoWriter::Set",
		info
	);
}

NAN_METHOD(VideoWriter::SetAsync) {
	FF::executeAsyncBinding(
		std::make_shared<VideoWriterBindings::SetWorker>(VideoWriter::unwrapSelf(info)),
		"VideoWriter::SetAsync",
		info
	);
}

NAN_METHOD(VideoWriter::Fourcc) {
  FF::executeSyncBinding(
    std::make_shared<VideoWriterBindings::FourccWorker>(),
    "VideoWriter::Fourcc",
    info
  );
}

NAN_METHOD(VideoWriter::Write) {
  FF::executeSyncBinding(
    std::make_shared<VideoWriterBindings::WriteWorker>(VideoWriter::unwrapSelf(info)),
    "VideoWriter::Write",
    info
  );
}

NAN_METHOD(VideoWriter::WriteAsync) {
  FF::executeAsyncBinding(
    std::make_shared<VideoWriterBindings::WriteWorker>(VideoWriter::unwrapSelf(info)),
    "VideoWriter::WriteAsync",
    info
  );
}

#endif