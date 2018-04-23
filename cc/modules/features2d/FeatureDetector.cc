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
    std::make_shared<FeatureDetectorBindings::DetectWorker>(FF_UNWRAP(info.This(), FeatureDetector)->getDetector()),
    "FeatureDetector::Detect",
    info
  );
}

NAN_METHOD(FeatureDetector::DetectAsync) {
  FF::AsyncBinding(
    std::make_shared<FeatureDetectorBindings::DetectWorker>(FF_UNWRAP(info.This(), FeatureDetector)->getDetector()),
    "FeatureDetector::DetectAsync",
    info
  );
}

NAN_METHOD(FeatureDetector::Compute) {
  FF::SyncBinding(
    std::make_shared<FeatureDetectorBindings::ComputeWorker>(FF_UNWRAP(info.This(), FeatureDetector)->getDetector()),
    "FeatureDetector::Compute",
    info
  );
}

NAN_METHOD(FeatureDetector::ComputeAsync) {
  FF::AsyncBinding(
    std::make_shared<FeatureDetectorBindings::ComputeWorker>(FF_UNWRAP(info.This(), FeatureDetector)->getDetector()),
    "FeatureDetector::ComputeAsync",
    info
  );
}
