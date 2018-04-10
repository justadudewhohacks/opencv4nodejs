#include "FeatureDetector.h"
#include "FeatureDetectorBindings.h"

void FeatureDetector::Init(v8::Local<v8::FunctionTemplate> ctor) {
  Nan::SetPrototypeMethod(ctor, "detect", FeatureDetector::Detect);
  Nan::SetPrototypeMethod(ctor, "compute", FeatureDetector::Compute);
  Nan::SetPrototypeMethod(ctor, "detectAsync", FeatureDetector::DetectAsync);
  Nan::SetPrototypeMethod(ctor, "computeAsync", FeatureDetector::ComputeAsync);
};

NAN_METHOD(FeatureDetector::Detect) {
  FF::SyncBinding(
    std::make_shared<FeatureDetectorBindings::DetectWorker>(FeatureDetector::Converter::unwrap(info.This())),
    "FeatureDetector::Detect",
    info
  );
}

NAN_METHOD(FeatureDetector::DetectAsync) {
  FF::AsyncBinding(
    std::make_shared<FeatureDetectorBindings::DetectWorker>(FeatureDetectorr::Converter::unwrap(info.This())),
    "FeatureDetector::DetectAsync",
    info
  );
}

NAN_METHOD(FeatureDetector::Compute) {
  FF::SyncBinding(
    std::make_shared<FeatureDetectorBindings::ComputeWorker>(FeatureDetectorr::Converter::unwrap(info.This())),
    "FeatureDetector::Compute",
    info
  );
}

NAN_METHOD(FeatureDetector::ComputeAsync) {
  FF::AsyncBinding(
    std::make_shared<FeatureDetectorBindings::ComputeWorker>(FeatureDetectorr::Converter::unwrap(info.This())),
    "FeatureDetector::ComputeAsync",
    info
  );
}
