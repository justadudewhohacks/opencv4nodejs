#include "FeatureDetector.h"
#include "FeatureDetectorBindings.h"

void FeatureDetector::Init(v8::Local<v8::FunctionTemplate> ctor) {
  Nan::SetPrototypeMethod(ctor, "detect", FeatureDetector::Detect);
  Nan::SetPrototypeMethod(ctor, "compute", FeatureDetector::Compute);
  Nan::SetPrototypeMethod(ctor, "detectAsync", FeatureDetector::DetectAsync);
  Nan::SetPrototypeMethod(ctor, "computeAsync", FeatureDetector::ComputeAsync);
};

NAN_METHOD(FeatureDetector::Detect) {
  FF::SyncBindingBase(
    std::make_shared<FeatureDetectorBindings::DetectWorker>(FeatureDetector::unwrapThis(info)->getDetector()),
    "FeatureDetector::Detect",
    info
  );
}

NAN_METHOD(FeatureDetector::DetectAsync) {
  FF::AsyncBindingBase(
    std::make_shared<FeatureDetectorBindings::DetectWorker>(FeatureDetector::unwrapThis(info)->getDetector()),
    "FeatureDetector::DetectAsync",
    info
  );
}

NAN_METHOD(FeatureDetector::Compute) {
  FF::SyncBindingBase(
    std::make_shared<FeatureDetectorBindings::ComputeWorker>(FeatureDetector::unwrapThis(info)->getDetector()),
    "FeatureDetector::Compute",
    info
  );
}

NAN_METHOD(FeatureDetector::ComputeAsync) {
  FF::AsyncBindingBase(
    std::make_shared<FeatureDetectorBindings::ComputeWorker>(FeatureDetector::unwrapThis(info)->getDetector()),
    "FeatureDetector::ComputeAsync",
    info
  );
}
