#ifdef HAVE_FACE

#include "Facemark.h"
#include "FacemarkAAMData.h"

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

struct Facemark::AddTrainingSampleWorker : public SimpleWorker {
public:
  cv::Ptr<cv::face::Facemark> self;
  AddTrainingSampleWorker(cv::Ptr<cv::face::Facemark> self) {
    this->self = self;
  }

  bool results;
  cv::Mat image;
  std::vector<cv::Point2f> landmarks;

  const char *execute() {
    results = self->addTrainingSample(image, landmarks);
    return "";
  }

  v8::Local<v8::Value> getReturnValue() {
    v8::Local<v8::Value> ret = Nan::New<v8::Boolean>(results);
    return ret;
  }

  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
    return (Mat::Converter::arg(0, &image, info) ||
            ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(
                1, &landmarks, info));
  }
};

NAN_METHOD(Facemark::AddTrainingSample) {
  AddTrainingSampleWorker worker(
      FF_UNWRAP(info.This(), Facemark)->getFacemark());
  FF_WORKER_SYNC("Facemark::AddTrainingSample", worker);
  info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Facemark::AddTrainingSampleAsync) {
  AddTrainingSampleWorker worker(
      FF_UNWRAP(info.This(), Facemark)->getFacemark());
  FF_WORKER_ASYNC("Facemark::AddTrainingSampleAsync", AddTrainingSampleWorker,
                  worker);
}

struct Facemark::LoadModelWorker : public SimpleWorker {
public:
  cv::Ptr<cv::face::Facemark> self;
  LoadModelWorker(cv::Ptr<cv::face::Facemark> self) { this->self = self; }

  std::string model;

  const char *execute() {
    self->loadModel(model);
    return "";
  }

  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
    return (StringConverter::arg(0, &model, info));
  }
};

NAN_METHOD(Facemark::LoadModel) {
  LoadModelWorker worker(FF_UNWRAP(info.This(), Facemark)->getFacemark());
  FF_WORKER_SYNC("Facemark::LoadModel", worker);
  info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Facemark::LoadModelAsync) {
  LoadModelWorker worker(FF_UNWRAP(info.This(), Facemark)->getFacemark());
  FF_WORKER_ASYNC("Facemark::LoadModelAsync", LoadModelWorker, worker);
}

struct Facemark::GetDataWorker : public SimpleWorker {
public:
  cv::Ptr<cv::face::Facemark> self;
  GetDataWorker(cv::Ptr<cv::face::Facemark> self) { this->self = self; }

  cv::face::FacemarkAAM::Data data;

  const char *execute() {
    self->getData(&data);
    return "";
  }

  v8::Local<v8::Value> getReturnValue() {
    v8::Local<v8::Value> ret = InstanceConverter<FacemarkAAMData, cv::face::FacemarkAAM::Data>::wrap(data);
    return ret;
  }
};

NAN_METHOD(Facemark::GetData) {
  GetDataWorker worker(FF_UNWRAP(info.This(), Facemark)->getFacemark());
  FF_WORKER_SYNC("Facemark::GetData", worker);
  info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Facemark::GetDataAsync) {
  GetDataWorker worker(FF_UNWRAP(info.This(), Facemark)->getFacemark());
  FF_WORKER_ASYNC("Facemark::GetDataAsync", GetDataWorker, worker);
}

struct Facemark::GetFacesWorker : public SimpleWorker {
public:
  cv::Ptr<cv::face::Facemark> self;
  GetFacesWorker(cv::Ptr<cv::face::Facemark> self) { this->self = self; }

  cv::Mat image;
  std::vector<cv::Rect> faces;

  const char *execute() {
    self->getFaces(image, faces);
    return "";
  }

  v8::Local<v8::Value> getReturnValue() {
    v8::Local<v8::Value> ret =
        ObjectArrayConverter<Rect, cv::Rect>::wrap(faces);
    return ret;
  }

  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
    return (Mat::Converter::arg(0, &image, info));
  }
};

NAN_METHOD(Facemark::GetFaces) {
  GetFacesWorker worker(FF_UNWRAP(info.This(), Facemark)->getFacemark());
  FF_WORKER_SYNC("Facemark::GetFaces", worker);
  info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Facemark::GetFacesAsync) {
  GetFacesWorker worker(FF_UNWRAP(info.This(), Facemark)->getFacemark());
  FF_WORKER_ASYNC("Facemark::GetFacesAsync", GetFacesWorker, worker);
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

struct Facemark::TrainingWorker : public SimpleWorker {
public:
  cv::Ptr<cv::face::Facemark> self;
  TrainingWorker(cv::Ptr<cv::face::Facemark> self) { this->self = self; }

  const char *execute() {
    self->training();
    return "";
  }
};

NAN_METHOD(Facemark::Training) {
  TrainingWorker worker(FF_UNWRAP(info.This(), Facemark)->getFacemark());
  FF_WORKER_SYNC("Facemark::Train", worker);
  info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Facemark::TrainingAsync) {
  TrainingWorker worker(FF_UNWRAP(info.This(), Facemark)->getFacemark());
  FF_WORKER_ASYNC("Facemark::TrainAsync", TrainingWorker, worker);
}

struct Facemark::FitWorker : public SimpleWorker {
public:
  cv::Ptr<cv::face::Facemark> self;
  FitWorker(cv::Ptr<cv::face::Facemark> self) { this->self = self; }

  cv::Mat image;
  std::vector<cv::Rect> faces;
  std::vector<std::vector<cv::Point2f>> landmarks;

  const char *execute() {
    self->fit(image, faces, landmarks);
    return "";
  }

  v8::Local<v8::Value> getReturnValue() {
    v8::Local<v8::Value> ret =
        ObjectArrayOfArraysConverter<Point2, cv::Point2d, cv::Point2f>::wrap(
            landmarks);
    return ret;
  }

  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
    return (Mat::Converter::arg(0, &image, info) ||
            ObjectArrayConverter<Rect, cv::Rect>::arg(1, &faces, info));
  }
};

NAN_METHOD(Facemark::Fit) {
  FitWorker worker(FF_UNWRAP(info.This(), Facemark)->getFacemark());
  FF_WORKER_SYNC("Facemark::Fit", worker);
  info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Facemark::FitAsync) {
  FitWorker worker(FF_UNWRAP(info.This(), Facemark)->getFacemark());
  FF_WORKER_ASYNC("Facemark::FitAsync", FitWorker, worker);
}

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

#endif
