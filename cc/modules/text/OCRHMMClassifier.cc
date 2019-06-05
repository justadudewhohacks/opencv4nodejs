#ifdef HAVE_TEXT

#include "OCRHMMClassifier.h"
#include "OCRHMMClassifierBindings.h"

Nan::Persistent<v8::FunctionTemplate> OCRHMMClassifier::constructor;

NAN_MODULE_INIT(OCRHMMClassifier::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(OCRHMMClassifier::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("OCRHMMClassifier"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(ctor, "eval", Eval);
  Nan::SetPrototypeMethod(ctor, "evalAsync", EvalAsync);

  Nan::Set(target,FF::newString("OCRHMMClassifier"), FF::getFunction(ctor));
};

NAN_METHOD(OCRHMMClassifier::Eval) {
  FF::SyncBindingBase(
    std::make_shared<OCRHMMClassifierBindings::EvalWorker>(OCRHMMClassifier::unwrapSelf(info)),
    "OCRHMMClassifier::Eval",
    info
  );
}

NAN_METHOD(OCRHMMClassifier::EvalAsync) {
  FF::AsyncBindingBase(
    std::make_shared<OCRHMMClassifierBindings::EvalWorker>(OCRHMMClassifier::unwrapSelf(info)),
    "OCRHMMClassifier::EvalAsync",
    info
  );
}

#endif
