#ifdef HAVE_FACE

#include "Facemark.h"
#include "FacemarkBindings.h"

#if CV_VERSION_MINOR >= 4

NAN_METHOD(Facemark::Save) {
  FF_METHOD_CONTEXT("Facemark::Save");
  FF_ARG_STRING(0, std::string path);
  FF_UNWRAP(info.This(), Facemark)->save(path);
}

NAN_METHOD(Facemark::Load) {
  FF_METHOD_CONTEXT("Facemark::Load");
  FF_ARG_STRING(0, std::string path);
  FF_UNWRAP(info.This(), Facemark)->load(path);
}

void Facemark::Init(v8::Local<v8::FunctionTemplate> ctor) {
  Nan::SetPrototypeMethod(ctor, "addTrainingSample", AddTrainingSample);
  Nan::SetPrototypeMethod(ctor, "addTrainingSampleAsync",
                          AddTrainingSampleAsync);
  Nan::SetPrototypeMethod(ctor, "loadModel", LoadModel);
  Nan::SetPrototypeMethod(ctor, "loadModelAsync", LoadModelAsync);
  Nan::SetPrototypeMethod(ctor, "getData", GetData);
  Nan::SetPrototypeMethod(ctor, "getDataAsync", GetDataAsync);
  Nan::SetPrototypeMethod(ctor, "getFaces", GetFaces);
  Nan::SetPrototypeMethod(ctor, "getFacesAsync", GetFacesAsync);
  Nan::SetPrototypeMethod(ctor, "setFaceDetector", SetFaceDetector);
  Nan::SetPrototypeMethod(ctor, "training", Training);
  Nan::SetPrototypeMethod(ctor, "trainingAsync", TrainingAsync);
  Nan::SetPrototypeMethod(ctor, "fit", Fit);
  Nan::SetPrototypeMethod(ctor, "fitAsync", FitAsync);
  Nan::SetPrototypeMethod(ctor, "save", Save);
  Nan::SetPrototypeMethod(ctor, "load", Load);
};

NAN_METHOD(Facemark::AddTrainingSample) {
  FF::SyncBinding(
    std::make_shared<FacemarkBindings::AddTrainingSampleWorker>(FF_UNWRAP(info.This(), Facemark)->getFacemark()),
    "Facemark::AddTrainingSample",
    info
  );
}

NAN_METHOD(Facemark::AddTrainingSampleAsync) {
  FF::AsyncBinding(
    std::make_shared<FacemarkBindings::AddTrainingSampleWorker>(FF_UNWRAP(info.This(), Facemark)->getFacemark()),
    "Facemark::AddTrainingSampleAsync",
    info
  );
}

NAN_METHOD(Facemark::LoadModel) {
  FF::SyncBinding(
    std::make_shared<FacemarkBindings::LoadModelWorker>(FF_UNWRAP(info.This(), Facemark)->getFacemark()),
    "Facemark::LoadModel",
    info
  );
}

NAN_METHOD(Facemark::LoadModelAsync) {
  FF::AsyncBinding(
    std::make_shared<FacemarkBindings::LoadModelWorker>(FF_UNWRAP(info.This(), Facemark)->getFacemark()),
    "Facemark::LoadModelAsync",
    info
  );
}

NAN_METHOD(Facemark::GetData) {
  FF::SyncBinding(
    std::make_shared<FacemarkBindings::GetDataWorker>(FF_UNWRAP(info.This(), Facemark)->getFacemark()),
    "Facemark::GetData",
    info
  );
}

NAN_METHOD(Facemark::GetDataAsync) {
  FF::AsyncBinding(
    std::make_shared<FacemarkBindings::GetDataWorker>(FF_UNWRAP(info.This(), Facemark)->getFacemark()),
    "Facemark::GetDataAsync",
    info
  );
}

NAN_METHOD(Facemark::GetFaces) {
  FF::SyncBinding(
    std::make_shared<FacemarkBindings::GetFacesWorker>(FF_UNWRAP(info.This(), Facemark)->getFacemark()),
    "Facemark::GetFaces",
    info
  );
}

NAN_METHOD(Facemark::GetFacesAsync) {
  FF::AsyncBinding(
    std::make_shared<FacemarkBindings::GetFacesWorker>(FF_UNWRAP(info.This(), Facemark)->getFacemark()),
    "Facemark::GetFacesAsync",
    info
  );
}

NAN_METHOD(Facemark::SetFaceDetector) {
  FF_METHOD_CONTEXT("SetFaceDetector");

  if (!info[0]->IsFunction()) {
    return Nan::ThrowError(Nan::New("Facemark::SetFaceDetector - Error: "
                                    "expected argument 0 to be of type")
                               .ToLocalChecked());
  }

  FF_ARG_FUNC(0, v8::Local<v8::Function> cbFunc);
  Nan::Callback *callback = new Nan::Callback(cbFunc);

  bool results = FF_UNWRAP(info.This(), Facemark)
      ->getFacemark()
      ->setFaceDetector((cv::face::FN_FaceDetector)detector, callback);

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(results));
}

NAN_METHOD(Facemark::Training) {
  FF::SyncBinding(
    std::make_shared<FacemarkBindings::TrainingWorker>(FF_UNWRAP(info.This(), Facemark)->getFacemark()),
    "Facemark::Train",
    info
  );
}

NAN_METHOD(Facemark::TrainingAsync) {
  FF::AsyncBinding(
    std::make_shared<FacemarkBindings::TrainingWorker>(FF_UNWRAP(info.This(), Facemark)->getFacemark()),
    "Facemark::TrainAsync",
    info
  );
}

NAN_METHOD(Facemark::Fit) {
  FF::SyncBinding(
    std::make_shared<FacemarkBindings::FitWorker>(FF_UNWRAP(info.This(), Facemark)->getFacemark()),
    "Facemark::Fit",
    info
  );
}

NAN_METHOD(Facemark::FitAsync) {
  FF::AsyncBinding(
    std::make_shared<FacemarkBindings::FitWorker>(FF_UNWRAP(info.This(), Facemark)->getFacemark()),
    "Facemark::FitAsync",
    info
  );
}

bool Facemark::detector(cv::InputArray image, cv::OutputArray faces,
                        Nan::Callback *callback) {
  Nan::HandleScope scope;

  cv::Mat frame = image.getMat().clone();
  v8::Local<v8::Value> jsMat = Mat::Converter::wrap(frame);

  v8::Local<v8::Value> argv[] = {jsMat};
  FF_OBJ jsObject = callback->Call(1, argv)->ToObject();

  std::vector<cv::Rect> _faces;
  ObjectArrayConverter<Rect, cv::Rect>::unwrap(&_faces, jsObject);

  cv::Mat(_faces).copyTo(faces);

  return true;
}

#endif

#endif
