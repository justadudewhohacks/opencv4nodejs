#include "HOGDescriptor.h"
#include "HOGDescriptorBindings.h"

Nan::Persistent<v8::FunctionTemplate> HOGDescriptor::constructor;

NAN_MODULE_INIT(HOGDescriptor::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(HOGDescriptor::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF_NEW_STRING("HOGDescriptor"));
  instanceTemplate->SetInternalFieldCount(1);
  
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("winSize"), winSize);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("blockSize"), blockSize);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("blockStride"), blockStride);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("cellSize"), cellSize);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("nbins"), nbins);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("derivAperture"), derivAperture);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("histogramNormType"), histogramNormType);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("nlevels"), nlevels);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("winSigma"), winSigma);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("L2HysThreshold"), L2HysThreshold);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("gammaCorrection"), gammaCorrection);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("signedGradient"), signedGradient);

  Nan::SetMethod(ctor, "getDaimlerPeopleDetector", GetDaimlerPeopleDetector);
  Nan::SetMethod(ctor, "getDefaultPeopleDetector", GetDefaultPeopleDetector);

  Nan::SetPrototypeMethod(ctor, "compute", Compute);
  Nan::SetPrototypeMethod(ctor, "computeAsync", ComputeAsync);
  Nan::SetPrototypeMethod(ctor, "computeGradient", ComputeGradient);
  Nan::SetPrototypeMethod(ctor, "computeGradientAsync", ComputeGradientAsync);
  Nan::SetPrototypeMethod(ctor, "detect", Detect);
  Nan::SetPrototypeMethod(ctor, "detectAsync", DetectAsync);
  Nan::SetPrototypeMethod(ctor, "detectROI", DetectROI);
  Nan::SetPrototypeMethod(ctor, "detectROIAsync", DetectROIAsync);
  Nan::SetPrototypeMethod(ctor, "detectMultiScale", DetectMultiScale);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleAsync", DetectMultiScaleAsync);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleROI", DetectMultiScaleROI);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleROIAsync", DetectMultiScaleROIAsync);
  Nan::SetPrototypeMethod(ctor, "groupRectangles", GroupRectangles);
  Nan::SetPrototypeMethod(ctor, "groupRectanglesAsync", GroupRectanglesAsync);
  Nan::SetPrototypeMethod(ctor, "checkDetectorSize", CheckDetectorSize);
  Nan::SetPrototypeMethod(ctor, "setSVMDetector", SetSVMDetector);
  Nan::SetPrototypeMethod(ctor, "save", Save);
  Nan::SetPrototypeMethod(ctor, "load", Load);

  target->Set(FF_NEW_STRING("HOGDescriptor"), ctor->GetFunction());
};

NAN_METHOD(HOGDescriptor::New) {
  FF_METHOD_CONTEXT("HOGDescriptor::New");

  // optional args
  bool hasOptArgsObj = FF_ARG_IS_OBJECT(0) && !FF_IS_INSTANCE(Size::constructor, info[1]);
  FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();

  FF_GET_INSTANCE_IFDEF(optArgs, cv::Size2d winSize, "winSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d(64, 128));
  FF_GET_INSTANCE_IFDEF(optArgs, cv::Size2d blockSize, "blockSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d(16, 16));
  FF_GET_INSTANCE_IFDEF(optArgs, cv::Size2d blockStride, "blockStride", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d(8, 8));
  FF_GET_INSTANCE_IFDEF(optArgs, cv::Size2d cellSize, "cellSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d(8, 8));
  FF_GET_UINT_IFDEF(optArgs, uint nbins, "nbins", 9);
  FF_GET_INT_IFDEF(optArgs, int derivAperture, "derivAperture", 1);
  FF_GET_NUMBER_IFDEF(optArgs, double winSigma, "winSigma", -1);
  FF_GET_UINT_IFDEF(optArgs, uint histogramNormType, "histogramNormType", cv::HOGDescriptor::L2Hys);
  FF_GET_NUMBER_IFDEF(optArgs, double L2HysThreshold, "L2HysThreshold", 0.2);
  FF_GET_BOOL_IFDEF(optArgs, bool gammaCorrection, "gammaCorrection", false);
  FF_GET_UINT_IFDEF(optArgs, uint nlevels, "nlevels", cv::HOGDescriptor::DEFAULT_NLEVELS);
  FF_GET_BOOL_IFDEF(optArgs, bool signedGradient, "signedGradient", false);
  if (!hasOptArgsObj) {
    FF_ARG_INSTANCE_IFDEF(0, winSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, winSize);
    FF_ARG_INSTANCE_IFDEF(1, blockSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, blockSize);
    FF_ARG_INSTANCE_IFDEF(2, blockStride, Size::constructor, FF_UNWRAP_SIZE_AND_GET, blockStride);
    FF_ARG_INSTANCE_IFDEF(3, cellSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, cellSize);
    FF_ARG_UINT_IFDEF(4, nbins, nbins);
    FF_ARG_INT_IFDEF(5, derivAperture, derivAperture);
    FF_ARG_NUMBER_IFDEF(6, winSigma, winSigma);
    FF_ARG_UINT_IFDEF(7, histogramNormType, histogramNormType);
    FF_ARG_NUMBER_IFDEF(8, L2HysThreshold, L2HysThreshold);
    FF_ARG_BOOL_IFDEF(9, gammaCorrection, gammaCorrection);
    FF_ARG_UINT_IFDEF(10, nlevels, nlevels);
    FF_ARG_BOOL_IFDEF(11, signedGradient, signedGradient);
  }

  HOGDescriptor* self = new HOGDescriptor();
  self->hog = cv::HOGDescriptor(
    winSize, 
    blockSize, 
    blockStride,
    cellSize, 
    (int)nbins, 
    derivAperture, 
    winSigma,
    (int)histogramNormType,
    L2HysThreshold,
    gammaCorrection,
    (int)nlevels,
    signedGradient
  );

  self->Wrap(info.Holder());
  FF_RETURN(info.Holder());
};

NAN_METHOD(HOGDescriptor::GetDaimlerPeopleDetector) {
  std::vector<float> detector = cv::HOGDescriptor::getDaimlerPeopleDetector();
  FF_RETURN(FloatArrayConverter::wrap(detector));
}

NAN_METHOD(HOGDescriptor::GetDefaultPeopleDetector) {
  std::vector<float> detector = cv::HOGDescriptor::getDefaultPeopleDetector();
  FF_RETURN(FloatArrayConverter::wrap(detector));
}

NAN_METHOD(HOGDescriptor::CheckDetectorSize) {
  FF_RETURN(Nan::New(HOGDescriptor::Converter::unwrap(info.This()).checkDetectorSize()));
}

NAN_METHOD(HOGDescriptor::SetSVMDetector) {
  FF_METHOD_CONTEXT("SetSVMDetector");
  std::vector<float> detector;
  if (!FF_HAS_ARG(0) || FloatArrayConverter::unwrap(&detector, info[0])) {
    FF_THROW("expected detector to be an Array of type Number");
  }
  HOGDescriptor::Converter::unwrapPtr(info.This())->setSVMDetector(detector);
}

NAN_METHOD(HOGDescriptor::Save) {
  FF_METHOD_CONTEXT("HOGDescriptor::Save");
  FF_ARG_STRING(0, std::string path);
  FF_UNWRAP(info.This(), HOGDescriptor)->hog.save(path);
}

NAN_METHOD(HOGDescriptor::Load) {
  FF_METHOD_CONTEXT("HOGDescriptor::Load");
  FF_ARG_STRING(0, std::string path);
  FF_UNWRAP(info.This(), HOGDescriptor)->hog.load(path);
}

NAN_METHOD(HOGDescriptor::Compute) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::ComputeWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::Compute",
    info
  );
}

NAN_METHOD(HOGDescriptor::ComputeAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::ComputeWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::ComputeAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::ComputeGradient) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::ComputeGradientWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::ComputeGradient",
    info
  );
}

NAN_METHOD(HOGDescriptor::ComputeGradientAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::ComputeGradientWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::ComputeGradientAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::Detect) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::Detect",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::DetectAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectROI) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectROIWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::DetectROI",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectROIAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectROIWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::DetectROIAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectMultiScale) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectMultiScaleWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::DetectMultiScale",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectMultiScaleAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectMultiScaleWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::DetectMultiScaleAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectMultiScaleROI) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectMultiScaleROIWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::DetectMultiScaleROI",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectMultiScaleROIAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectMultiScaleROIWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::DetectMultiScaleROIAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::GroupRectangles) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::GroupRectanglesWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::GroupRectangles",
    info
  );
}

NAN_METHOD(HOGDescriptor::GroupRectanglesAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::GroupRectanglesWorker>(HOGDescriptor::Converter::unwrap(info.This())),
    "HOGDescriptor::GroupRectanglesAsync",
    info
  );
}
