#ifdef HAVE_TEXT

#include "OCRHMMClassifier.h"
#include "OCRHMMClassifierBindings.h"

Nan::Persistent<v8::FunctionTemplate> OCRHMMClassifier::constructor;

NAN_MODULE_INIT(OCRHMMClassifier::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(OCRHMMClassifier::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF_NEW_STRING("OCRHMMClassifier"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(ctor, "eval", Eval);
  Nan::SetPrototypeMethod(ctor, "evalAsync", EvalAsync);

  target->Set(FF_NEW_STRING("OCRHMMClassifier"), ctor->GetFunction());
};

NAN_METHOD(OCRHMMClassifier::Eval) {
  FF::SyncBinding(
    std::make_shared<OCRHMMClassifierBindings::EvalWorker>(OCRHMMClassifier::Converter::unwrap(info.This())),
    "OCRHMMClassifier::Eval",
    info
  );
}

NAN_METHOD(OCRHMMClassifier::EvalAsync) {
  FF::AsyncBinding(
    std::make_shared<OCRHMMClassifierBindings::EvalWorker>(OCRHMMClassifier::Converter::unwrap(info.This())),
    "OCRHMMClassifier::EvalAsync",
    info
  );
}

#endif
