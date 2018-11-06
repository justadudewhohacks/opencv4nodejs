#ifdef HAVE_TEXT

#include "text.h"
#include "textBindings.h"

NAN_MODULE_INIT(Text::Init) {
  OCRHMMDecoder::Init(target);
  OCRHMMClassifier::Init(target);
  Nan::SetMethod(target, "loadOCRHMMClassifierNM", LoadOCRHMMClassifierNM);
  Nan::SetMethod(target, "loadOCRHMMClassifierNMAsync", LoadOCRHMMClassifierNMAsync);
#if CV_MINOR_VERSION > 0
  Nan::SetMethod(target, "loadOCRHMMClassifierCNN", LoadOCRHMMClassifierCNN);
  Nan::SetMethod(target, "loadOCRHMMClassifierCNNAsync", LoadOCRHMMClassifierCNNAsync);
  Nan::SetMethod(target, "createOCRHMMTransitionsTable", CreateOCRHMMTransitionsTable);
  Nan::SetMethod(target, "createOCRHMMTransitionsTableAsync", CreateOCRHMMTransitionsTableAsync);
#endif
}

NAN_METHOD(Text::LoadOCRHMMClassifierNM) {
  FF::SyncBinding(
    std::make_shared<TextBindings::LoadOCRHMMClassifierNMWorker>(),
    "Text::LoadOCRHMMClassifierNM",
    info
  );
}

NAN_METHOD(Text::LoadOCRHMMClassifierNMAsync) {
  FF::AsyncBinding(
    std::make_shared<TextBindings::LoadOCRHMMClassifierNMWorker>(),
    "Text::LoadOCRHMMClassifierNMAsync",
    info
  );
}

#if CV_MINOR_VERSION > 0

NAN_METHOD(Text::LoadOCRHMMClassifierCNN) {
  FF::SyncBinding(
    std::make_shared<TextBindings::LoadOCRHMMClassifierCNNWorker>(),
    "Text::LoadOCRHMMClassifierCNN",
    info
  );
}

NAN_METHOD(Text::LoadOCRHMMClassifierCNNAsync) {
  FF::AsyncBinding(
    std::make_shared<TextBindings::LoadOCRHMMClassifierCNNWorker>(),
    "Text::LoadOCRHMMClassifierCNNAsync",
    info
  );
}

NAN_METHOD(Text::CreateOCRHMMTransitionsTable) {
  FF::SyncBinding(
    std::make_shared<TextBindings::CreateOCRHMMTransitionsTableWorker>(),
    "Text::CreateOCRHMMTransitionsTable",
    info
  );
}

NAN_METHOD(Text::CreateOCRHMMTransitionsTableAsync) {
  FF::AsyncBinding(
    std::make_shared<TextBindings::CreateOCRHMMTransitionsTableWorker>(),
    "Text::CreateOCRHMMTransitionsTableAsync",
    info
  );
}
#endif

#endif
