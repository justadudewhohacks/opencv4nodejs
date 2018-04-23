#include "CascadeClassifier.h"
#include "CascadeClassifierBindings.h"

Nan::Persistent<v8::FunctionTemplate> CascadeClassifier::constructor;

NAN_MODULE_INIT(CascadeClassifier::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(CascadeClassifier::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF_NEW_STRING("CascadeClassifier"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(ctor, "detectMultiScale", DetectMultiScale);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleAsync", DetectMultiScaleAsync);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleGpu", DetectMultiScaleGpu);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleWithRejectLevels", DetectMultiScaleWithRejectLevels);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleWithRejectLevelsAsync", DetectMultiScaleWithRejectLevelsAsync);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleWithRejectLevelsGpu", DetectMultiScaleWithRejectLevelsGpu);

  target->Set(FF_NEW_STRING("CascadeClassifier"), ctor->GetFunction());
};

NAN_METHOD(CascadeClassifier::New) {
  FF_METHOD_CONTEXT("CascadeClassifier::New");

  FF_ARG_STRING(0, std::string xmlFilePath);

  CascadeClassifier* self = new CascadeClassifier();
  self->classifier = cv::CascadeClassifier(xmlFilePath);
  if (self->classifier.empty()) {
    FF_THROW("failed to load cascade.xml file: " + xmlFilePath);
  }
  self->Wrap(info.Holder());
  FF_RETURN(info.Holder());
};

NAN_METHOD(CascadeClassifier::DetectMultiScale) {
  FF::SyncBinding(
    std::make_shared<CascadeClassifierBindings::DetectMultiScaleWorker>(CascadeClassifier::Converter::unwrap(info.This())),
    "CascadeClassifier::DetectMultiScale",
    info
  );
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleAsync) {
  FF::AsyncBinding(
    std::make_shared<CascadeClassifierBindings::DetectMultiScaleWorker>(CascadeClassifier::Converter::unwrap(info.This())),
    "CascadeClassifier::DetectMultiScaleAsync",
    info
  );
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleGpu) {
  FF::SyncBinding(
    std::make_shared<CascadeClassifierBindings::DetectMultiScaleWorker>(CascadeClassifier::Converter::unwrap(info.This())),
    "CascadeClassifier::DetectMultiScaleGpu",
    info
  );
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleWithRejectLevels) {
  FF::SyncBinding(
    std::make_shared<CascadeClassifierBindings::DetectMultiScaleWithRejectLevelsWorker>(CascadeClassifier::Converter::unwrap(info.This())),
    "CascadeClassifier::DetectMultiScaleWithRejectLevels",
    info
  );
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleWithRejectLevelsAsync) {
  FF::AsyncBinding(
    std::make_shared<CascadeClassifierBindings::DetectMultiScaleWithRejectLevelsWorker>(CascadeClassifier::Converter::unwrap(info.This())),
    "CascadeClassifier::DetectMultiScaleWithRejectLevelsAsync",
    info
  );
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleWithRejectLevelsGpu) {
  FF::SyncBinding(
    std::make_shared<CascadeClassifierBindings::DetectMultiScaleWithRejectLevelsWorker>(CascadeClassifier::Converter::unwrap(info.This())),
    "CascadeClassifier::DetectMultiScaleWithRejectLevelsGpu",
    info
  );
}
