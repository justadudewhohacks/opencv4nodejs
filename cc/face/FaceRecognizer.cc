#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

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
	FF::TryCatch tryCatch("FaceRecognizer::Save");

	std::string path;
	if (FF::StringConverter::arg(0, &path, info)) {
		return tryCatch.reThrow();
	}
	Nan::ObjectWrap::Unwrap<FaceRecognizer>(info.This())->save(path);
}

NAN_METHOD(FaceRecognizer::Load) {
	FF::TryCatch tryCatch("FaceRecognizer::Load");

	std::string path;
	if (FF::StringConverter::arg(0, &path, info)) {
		return tryCatch.reThrow();
	}
	Nan::ObjectWrap::Unwrap<FaceRecognizer>(info.This())->load(path);
}

NAN_METHOD(FaceRecognizer::Train) {
  FF::executeSyncBinding(
    std::make_shared<FaceRecognizerBindings::TrainWorker>(FaceRecognizer::unwrapThis(info)->getFaceRecognizer()),
    "FaceRecognizer::Train",
    info
  );
}

NAN_METHOD(FaceRecognizer::TrainAsync) {
  FF::executeAsyncBinding(
    std::make_shared<FaceRecognizerBindings::TrainWorker>(FaceRecognizer::unwrapThis(info)->getFaceRecognizer()),
    "FaceRecognizer::TrainAsync",
    info
  );
}

NAN_METHOD(FaceRecognizer::Predict) {
  FF::executeSyncBinding(
    std::make_shared<FaceRecognizerBindings::PredictWorker>(FaceRecognizer::unwrapThis(info)->getFaceRecognizer()),
    "FaceRecognizer::Predict",
    info
  );
}

NAN_METHOD(FaceRecognizer::PredictAsync) {
  FF::executeAsyncBinding(
    std::make_shared<FaceRecognizerBindings::PredictWorker>(FaceRecognizer::unwrapThis(info)->getFaceRecognizer()),
    "FaceRecognizer::PredictAsync",
    info
  );
}

#endif