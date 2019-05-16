#ifdef HAVE_FACE

#include "FaceRecognizer.h"
#include "FaceRecognizerBindings.h"

void FaceRecognizer::Init(v8::Local<v8::FunctionTemplate> ctor) {
  Nan::SetPrototypeMethod(ctor, "train", Train);
  Nan::SetPrototypeMethod(ctor, "trainAsync", TrainAsync);
  Nan::SetPrototypeMethod(ctor, "predict", Predict);
  Nan::SetPrototypeMethod(ctor, "predictAsync", PredictAsync);
  Nan::SetPrototypeMethod(ctor, "save", Save);
  Nan::SetPrototypeMethod(ctor, "load", Load);
};

NAN_METHOD(FaceRecognizer::Save) {
	FF::TryCatch tryCatch;

	std::string path;
	if (StringConverter::arg(0, &path, info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("FaceRecognizer::Save");
		tryCatch.throwNew(err);
		return;
	}
	Nan::ObjectWrap::Unwrap<FaceRecognizer>(info.This())->save(path);
}

NAN_METHOD(FaceRecognizer::Load) {
	FF::TryCatch tryCatch;

	std::string path;
	if (StringConverter::arg(0, &path, info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("FaceRecognizer::Load");
		tryCatch.throwNew(err);
		return;
	}
	Nan::ObjectWrap::Unwrap<FaceRecognizer>(info.This())->load(path);
}

NAN_METHOD(FaceRecognizer::Train) {
  FF::SyncBinding(
    std::make_shared<FaceRecognizerBindings::TrainWorker>(FF_UNWRAP(info.This(), FaceRecognizer)->getFaceRecognizer()),
    "FaceRecognizer::Train",
    info
  );
}

NAN_METHOD(FaceRecognizer::TrainAsync) {
  FF::AsyncBinding(
    std::make_shared<FaceRecognizerBindings::TrainWorker>(FF_UNWRAP(info.This(), FaceRecognizer)->getFaceRecognizer()),
    "FaceRecognizer::TrainAsync",
    info
  );
}

NAN_METHOD(FaceRecognizer::Predict) {
  FF::SyncBinding(
    std::make_shared<FaceRecognizerBindings::PredictWorker>(FF_UNWRAP(info.This(), FaceRecognizer)->getFaceRecognizer()),
    "FaceRecognizer::Predict",
    info
  );
}

NAN_METHOD(FaceRecognizer::PredictAsync) {
  FF::AsyncBinding(
    std::make_shared<FaceRecognizerBindings::PredictWorker>(FF_UNWRAP(info.This(), FaceRecognizer)->getFaceRecognizer()),
    "FaceRecognizer::PredictAsync",
    info
  );
}

#endif