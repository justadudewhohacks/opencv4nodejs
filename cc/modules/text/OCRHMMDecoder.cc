#ifdef HAVE_TEXT

#include "OCRHMMDecoder.h"
#include "OCRHMMDecoderBindings.h"

Nan::Persistent<v8::FunctionTemplate> OCRHMMDecoder::constructor;

NAN_MODULE_INIT(OCRHMMDecoder::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(OCRHMMDecoder::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF_NEW_STRING("OCRHMMDecoder"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(ctor, "run", Run);
  Nan::SetPrototypeMethod(ctor, "runAsync", RunAsync);
  Nan::SetPrototypeMethod(ctor, "runWithInfo", RunWithInfo);
  Nan::SetPrototypeMethod(ctor, "runWithInfoAsync", RunWithInfoAsync);

  target->Set(FF_NEW_STRING("OCRHMMDecoder"), ctor->GetFunction());
};

NAN_METHOD(OCRHMMDecoder::New) {
  FF::SyncBinding(
    std::make_shared<OCRHMMDecoderBindings::NewWorker>(),
    "OCRHMMDecoder::New",
    info
  );
}

NAN_METHOD(OCRHMMDecoder::Run) {
  FF::SyncBinding(
    std::make_shared<OCRHMMDecoderBindings::RunWorker>(OCRHMMDecoder::Converter::unwrap(info.This())),
    "OCRHMMDecoder::Run",
    info
  );
}

NAN_METHOD(OCRHMMDecoder::RunAsync) {
  FF::AsyncBinding(
    std::make_shared<OCRHMMDecoderBindings::RunWorker>(OCRHMMDecoder::Converter::unwrap(info.This())),
    "OCRHMMDecoder::RunAsync",
    info
  );
}

NAN_METHOD(OCRHMMDecoder::RunWithInfo) {
  FF::SyncBinding(
    std::make_shared<OCRHMMDecoderBindings::RunWithInfoWorker>(OCRHMMDecoder::Converter::unwrap(info.This())),
    "OCRHMMDecoder::RunWithInfo",
    info
  );
}

NAN_METHOD(OCRHMMDecoder::RunWithInfoAsync) {
  FF::AsyncBinding(
    std::make_shared<OCRHMMDecoderBindings::RunWithInfoWorker>(OCRHMMDecoder::Converter::unwrap(info.This())),
    "OCRHMMDecoder::RunWithInfoAsync",
    info
  );
}

#endif
