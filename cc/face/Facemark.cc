#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "Facemark.h"
#include "FacemarkBindings.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

NAN_METHOD(Facemark::Save) {
	FF::TryCatch tryCatch("Facemark::Save");

	std::string path;
	if (FF::StringConverter::arg(0, &path, info)) {
		return tryCatch.reThrow();
	}
	Nan::ObjectWrap::Unwrap<Facemark>(info.This())->save(path);
}

NAN_METHOD(Facemark::Load) {
	FF::TryCatch tryCatch("Facemark::Load");

	std::string path;
	if (FF::StringConverter::arg(0, &path, info)) {
		return tryCatch.reThrow();
	}
	Nan::ObjectWrap::Unwrap<Facemark>(info.This())->load(path);
}

void Facemark::Init(v8::Local<v8::FunctionTemplate> ctor) {
  Nan::SetPrototypeMethod(ctor, "loadModel", LoadModel);
  Nan::SetPrototypeMethod(ctor, "loadModelAsync", LoadModelAsync);
  Nan::SetPrototypeMethod(ctor, "fit", Fit);
  Nan::SetPrototypeMethod(ctor, "fitAsync", FitAsync);
  Nan::SetPrototypeMethod(ctor, "save", Save);
  Nan::SetPrototypeMethod(ctor, "load", Load);
#if CV_VERSION_MAJOR <= 3 && CV_VERSION_MINOR < 2
  Nan::SetPrototypeMethod(ctor, "addTrainingSample", AddTrainingSample);
  Nan::SetPrototypeMethod(ctor, "addTrainingSampleAsync",
	  AddTrainingSampleAsync);
  Nan::SetPrototypeMethod(ctor, "getData", GetData);
  Nan::SetPrototypeMethod(ctor, "getDataAsync", GetDataAsync);
  Nan::SetPrototypeMethod(ctor, "getFaces", GetFaces);
  Nan::SetPrototypeMethod(ctor, "getFacesAsync", GetFacesAsync);
  Nan::SetPrototypeMethod(ctor, "setFaceDetector", SetFaceDetector);
  Nan::SetPrototypeMethod(ctor, "training", Training);
  Nan::SetPrototypeMethod(ctor, "trainingAsync", TrainingAsync);
#endif
};

NAN_METHOD(Facemark::LoadModel) {
  FF::executeSyncBinding(
    std::make_shared<FacemarkBindings::LoadModelWorker>(Facemark::unwrapThis(info)->getFacemark()),
    "Facemark::LoadModel",
    info
  );
}

NAN_METHOD(Facemark::LoadModelAsync) {
  FF::executeAsyncBinding(
    std::make_shared<FacemarkBindings::LoadModelWorker>(Facemark::unwrapThis(info)->getFacemark()),
    "Facemark::LoadModelAsync",
    info
  );
}

NAN_METHOD(Facemark::Fit) {
	FF::executeSyncBinding(
		std::make_shared<FacemarkBindings::FitWorker>(Facemark::unwrapThis(info)->getFacemark()),
		"Facemark::Fit",
		info
	);
}

NAN_METHOD(Facemark::FitAsync) {
	FF::executeAsyncBinding(
		std::make_shared<FacemarkBindings::FitWorker>(Facemark::unwrapThis(info)->getFacemark()),
		"Facemark::FitAsync",
		info
	);
}

#if CV_VERSION_MAJOR <= 3 && CV_VERSION_MINOR < 2

NAN_METHOD(Facemark::AddTrainingSample) {
	FF::executeSyncBinding(
		std::make_shared<FacemarkBindings::AddTrainingSampleWorker>(Facemark::unwrapThis(info)->getFacemark()),
		"Facemark::AddTrainingSample",
		info
	);
}

NAN_METHOD(Facemark::AddTrainingSampleAsync) {
	FF::executeAsyncBinding(
		std::make_shared<FacemarkBindings::AddTrainingSampleWorker>(Facemark::unwrapThis(info)->getFacemark()),
		"Facemark::AddTrainingSampleAsync",
		info
	);
}

NAN_METHOD(Facemark::GetData) {
  FF::executeSyncBinding(
    std::make_shared<FacemarkBindings::GetDataWorker>(Facemark::unwrapThis(info)->getFacemark()),
    "Facemark::GetData",
    info
  );
}

NAN_METHOD(Facemark::GetDataAsync) {
  FF::executeAsyncBinding(
    std::make_shared<FacemarkBindings::GetDataWorker>(Facemark::unwrapThis(info)->getFacemark()),
    "Facemark::GetDataAsync",
    info
  );
}

NAN_METHOD(Facemark::GetFaces) {
  FF::executeSyncBinding(
    std::make_shared<FacemarkBindings::GetFacesWorker>(Facemark::unwrapThis(info)->getFacemark()),
    "Facemark::GetFaces",
    info
  );
}

NAN_METHOD(Facemark::GetFacesAsync) {
  FF::executeAsyncBinding(
    std::make_shared<FacemarkBindings::GetFacesWorker>(Facemark::unwrapThis(info)->getFacemark()),
    "Facemark::GetFacesAsync",
    info
  );
}

NAN_METHOD(Facemark::SetFaceDetector) {
	FF::TryCatch tryCatch("Facemark::SetFaceDetector");
  if (!info[0]->IsFunction()) {
    return tryCatch.throwError("expected argument 0 to be of type");
  }
  v8::Local<v8::Function> cbFunc = v8::Local<v8::Function>::Cast(info[0]);
  Nan::Callback *callback = new Nan::Callback(cbFunc);

  bool results = Facemark::unwrapThis(info)
      ->getFacemark()
      ->setFaceDetector((cv::face::FN_FaceDetector)detector, callback);

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(results));
}

NAN_METHOD(Facemark::Training) {
  FF::executeSyncBinding(
    std::make_shared<FacemarkBindings::TrainingWorker>(Facemark::unwrapThis(info)->getFacemark()),
    "Facemark::Train",
    info
  );
}

NAN_METHOD(Facemark::TrainingAsync) {
  FF::executeAsyncBinding(
    std::make_shared<FacemarkBindings::TrainingWorker>(Facemark::unwrapThis(info)->getFacemark()),
    "Facemark::TrainAsync",
    info
  );
}

#endif

bool Facemark::detector(cv::InputArray image, cv::OutputArray faces,
                        Nan::Callback *callback) {
  Nan::HandleScope scope;

  cv::Mat frame = image.getMat().clone();
  v8::Local<v8::Value> jsMat = Mat::Converter::wrap(frame);

  v8::Local<v8::Value> argv[] = {jsMat};

  Nan::AsyncResource resource("opencv4nodejs:Facemark::Detector");
  v8::Local<v8::Object> jsObject = resource.runInAsyncScope(Nan::GetCurrentContext()->Global(), **callback, 1, argv)
    .ToLocalChecked()->ToObject(Nan::GetCurrentContext()).ToLocalChecked();

  std::vector<cv::Rect2d> _faces;
  Rect::ArrayConverter::unwrapTo(&_faces, jsObject);

  cv::Mat(_faces).copyTo(faces);

  return true;
}

#endif

#endif
