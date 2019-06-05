#include "HOGDescriptor.h"
#include "HOGDescriptorBindings.h"

Nan::Persistent<v8::FunctionTemplate> HOGDescriptor::constructor;

NAN_MODULE_INIT(HOGDescriptor::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(HOGDescriptor::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("HOGDescriptor"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString("winSize"), winSize_getter, winSize_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("blockSize"), blockSize_getter, blockSize_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("blockStride"), blockStride_getter, blockStride_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("cellSize"), cellSize_getter, cellSize_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("nbins"), nbins_getter, nbins_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("derivAperture"), derivAperture_getter, derivAperture_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("histogramNormType"), histogramNormType_getter, histogramNormType_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("nlevels"), nlevels_getter, nlevels_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("winSigma"), winSigma_getter, winSigma_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("L2HysThreshold"), L2HysThreshold_getter, L2HysThreshold_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("gammaCorrection"), gammaCorrection_getter, gammaCorrection_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("signedGradient"), signedGradient_getter, signedGradient_setter);

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

  Nan::Set(target,FF::newString("HOGDescriptor"), FF::getFunction(ctor));
};
NAN_METHOD(HOGDescriptor::New) {
	FF::TryCatch tryCatch("HOGDescriptor::New");
	FF_ASSERT_CONSTRUCT_CALL();
	HOGDescriptorBindings::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
	}

	HOGDescriptor* self = new HOGDescriptor();
	self->setNativeObject(std::make_shared<cv::HOGDescriptor>(
		worker.winSize,
		worker.blockSize,
		worker.blockStride,
		worker.cellSize,
		(int)worker.nbins,
		worker.derivAperture,
		worker.winSigma,
		(int)worker.histogramNormType,
		worker.L2HysThreshold,
		worker.gammaCorrection,
		(int)worker.nlevels,
		worker.signedGradient
	));
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(HOGDescriptor::GetDaimlerPeopleDetector) {
  std::vector<float> detector = cv::HOGDescriptor::getDaimlerPeopleDetector();
  info.GetReturnValue().Set(FF::FloatArrayConverter::wrap(detector));
}

NAN_METHOD(HOGDescriptor::GetDefaultPeopleDetector) {
  std::vector<float> detector = cv::HOGDescriptor::getDefaultPeopleDetector();
  info.GetReturnValue().Set(FF::FloatArrayConverter::wrap(detector));
}

NAN_METHOD(HOGDescriptor::CheckDetectorSize) {
  info.GetReturnValue().Set(Nan::New(HOGDescriptor::unwrapSelf(info)->checkDetectorSize()));
}

NAN_METHOD(HOGDescriptor::SetSVMDetector) {
  FF::TryCatch tryCatch("HOGDescriptor::SetSVMDetector");
  std::vector<float> detector;
  if (!FF::hasArg(info, 0) || FF::FloatArrayConverter::unwrapTo(&detector, info[0])) {
	  return tryCatch.throwError("expected detector to be an Array of type Number");
  }
  HOGDescriptor::unwrapSelf(info)->setSVMDetector(detector);
}

NAN_METHOD(HOGDescriptor::Save) {
	FF::TryCatch tryCatch("HOGDescriptor::Save");

	std::string path;
	if (FF::StringConverter::arg(0, &path, info)) {
		return tryCatch.reThrow();
	}
	HOGDescriptor::unwrapSelf(info)->save(path);
}

NAN_METHOD(HOGDescriptor::Load) {
	FF::TryCatch tryCatch("HOGDescriptor::Load");

	std::string path;
	if (FF::StringConverter::arg(0, &path, info)) {
		return tryCatch.reThrow();
	}
	HOGDescriptor::unwrapSelf(info)->load(path);
}

NAN_METHOD(HOGDescriptor::Compute) {
  FF::SyncBindingBase(
    std::make_shared<HOGDescriptorBindings::ComputeWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::Compute",
    info
  );
}

NAN_METHOD(HOGDescriptor::ComputeAsync) {
  FF::AsyncBindingBase(
    std::make_shared<HOGDescriptorBindings::ComputeWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::ComputeAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::ComputeGradient) {
  FF::SyncBindingBase(
    std::make_shared<HOGDescriptorBindings::ComputeGradientWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::ComputeGradient",
    info
  );
}

NAN_METHOD(HOGDescriptor::ComputeGradientAsync) {
  FF::AsyncBindingBase(
    std::make_shared<HOGDescriptorBindings::ComputeGradientWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::ComputeGradientAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::Detect) {
  FF::SyncBindingBase(
    std::make_shared<HOGDescriptorBindings::DetectWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::Detect",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectAsync) {
  FF::AsyncBindingBase(
    std::make_shared<HOGDescriptorBindings::DetectWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectROI) {
  FF::SyncBindingBase(
    std::make_shared<HOGDescriptorBindings::DetectROIWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectROI",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectROIAsync) {
  FF::AsyncBindingBase(
    std::make_shared<HOGDescriptorBindings::DetectROIWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectROIAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectMultiScale) {
  FF::SyncBindingBase(
    std::make_shared<HOGDescriptorBindings::DetectMultiScaleWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectMultiScale",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectMultiScaleAsync) {
  FF::AsyncBindingBase(
    std::make_shared<HOGDescriptorBindings::DetectMultiScaleWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectMultiScaleAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectMultiScaleROI) {
  FF::SyncBindingBase(
    std::make_shared<HOGDescriptorBindings::DetectMultiScaleROIWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectMultiScaleROI",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectMultiScaleROIAsync) {
  FF::AsyncBindingBase(
    std::make_shared<HOGDescriptorBindings::DetectMultiScaleROIWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectMultiScaleROIAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::GroupRectangles) {
  FF::SyncBindingBase(
    std::make_shared<HOGDescriptorBindings::GroupRectanglesWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::GroupRectangles",
    info
  );
}

NAN_METHOD(HOGDescriptor::GroupRectanglesAsync) {
  FF::AsyncBindingBase(
    std::make_shared<HOGDescriptorBindings::GroupRectanglesWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::GroupRectanglesAsync",
    info
  );
}
