#include "CascadeClassifier.h"
#include "CascadeClassifierBindings.h"

Nan::Persistent<v8::FunctionTemplate> CascadeClassifier::constructor;

NAN_MODULE_INIT(CascadeClassifier::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(CascadeClassifier::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("CascadeClassifier"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(ctor, "detectMultiScale", DetectMultiScale);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleAsync", DetectMultiScaleAsync);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleGpu", DetectMultiScaleGpu);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleWithRejectLevels", DetectMultiScaleWithRejectLevels);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleWithRejectLevelsAsync", DetectMultiScaleWithRejectLevelsAsync);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleWithRejectLevelsGpu", DetectMultiScaleWithRejectLevelsGpu);

  Nan::Set(target,FF::newString("CascadeClassifier"), FF::getFunction(ctor));
};

NAN_METHOD(CascadeClassifier::New) {
	FF_ASSERT_CONSTRUCT_CALL(CascadeClassifier);
	FF::TryCatch tryCatch;
	CascadeClassifierBindings::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("CascadeClassifier::New");
		tryCatch.throwNew(err);
		return;
	}

	CascadeClassifier* self = new CascadeClassifier();
	self->classifier = cv::CascadeClassifier(worker.xmlFilePath);
	if (worker.applyUnwrappers(info)) {
		return Nan::ThrowError(FF::newString(std::string("CascadeClassifier::New") + " - " + std::string("failed to load cascade.xml file: " + worker.xmlFilePath)));
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(CascadeClassifier::DetectMultiScale) {
  FF::SyncBinding(
    std::make_shared<CascadeClassifierBindings::DetectMultiScaleWorker>(CascadeClassifier::unwrapSelf(info)),
    "CascadeClassifier::DetectMultiScale",
    info
  );
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleAsync) {
  FF::AsyncBinding(
    std::make_shared<CascadeClassifierBindings::DetectMultiScaleWorker>(CascadeClassifier::unwrapSelf(info)),
    "CascadeClassifier::DetectMultiScaleAsync",
    info
  );
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleGpu) {
  FF::SyncBinding(
    std::make_shared<CascadeClassifierBindings::DetectMultiScaleWorker>(CascadeClassifier::unwrapSelf(info)),
    "CascadeClassifier::DetectMultiScaleGpu",
    info
  );
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleWithRejectLevels) {
  FF::SyncBinding(
    std::make_shared<CascadeClassifierBindings::DetectMultiScaleWithRejectLevelsWorker>(CascadeClassifier::unwrapSelf(info)),
    "CascadeClassifier::DetectMultiScaleWithRejectLevels",
    info
  );
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleWithRejectLevelsAsync) {
  FF::AsyncBinding(
    std::make_shared<CascadeClassifierBindings::DetectMultiScaleWithRejectLevelsWorker>(CascadeClassifier::unwrapSelf(info)),
    "CascadeClassifier::DetectMultiScaleWithRejectLevelsAsync",
    info
  );
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleWithRejectLevelsGpu) {
  FF::SyncBinding(
    std::make_shared<CascadeClassifierBindings::DetectMultiScaleWithRejectLevelsWorker>(CascadeClassifier::unwrapSelf(info)),
    "CascadeClassifier::DetectMultiScaleWithRejectLevelsGpu",
    info
  );
}
