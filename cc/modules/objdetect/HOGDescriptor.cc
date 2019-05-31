#include "HOGDescriptor.h"
#include "HOGDescriptorBindings.h"

Nan::Persistent<v8::FunctionTemplate> HOGDescriptor::constructor;

NAN_MODULE_INIT(HOGDescriptor::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(HOGDescriptor::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("HOGDescriptor"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString("winSize"), winSize);
  Nan::SetAccessor(instanceTemplate, FF::newString("blockSize"), blockSize);
  Nan::SetAccessor(instanceTemplate, FF::newString("blockStride"), blockStride);
  Nan::SetAccessor(instanceTemplate, FF::newString("cellSize"), cellSize);
  Nan::SetAccessor(instanceTemplate, FF::newString("nbins"), nbins);
  Nan::SetAccessor(instanceTemplate, FF::newString("derivAperture"), derivAperture);
  Nan::SetAccessor(instanceTemplate, FF::newString("histogramNormType"), histogramNormType);
  Nan::SetAccessor(instanceTemplate, FF::newString("nlevels"), nlevels);
  Nan::SetAccessor(instanceTemplate, FF::newString("winSigma"), winSigma);
  Nan::SetAccessor(instanceTemplate, FF::newString("L2HysThreshold"), L2HysThreshold);
  Nan::SetAccessor(instanceTemplate, FF::newString("gammaCorrection"), gammaCorrection);
  Nan::SetAccessor(instanceTemplate, FF::newString("signedGradient"), signedGradient);

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
	FF_ASSERT_CONSTRUCT_CALL(HOGDescriptor);
	FF::TryCatch tryCatch;
	HOGDescriptorBindings::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("HOGDescriptor::New");
		tryCatch.throwNew(err);
		return;
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
  FF_METHOD_CONTEXT("SetSVMDetector");
  std::vector<float> detector;
  if (!FF::hasArg(info, 0) || FF::FloatArrayConverter::unwrapUncheckedTo(&detector, info[0])) {
    FF_THROW("expected detector to be an Array of type Number");
  }
  HOGDescriptor::unwrapSelf(info)->setSVMDetector(detector);
}

NAN_METHOD(HOGDescriptor::Save) {
	FF::TryCatch tryCatch;

	std::string path;
	if (FF::StringConverter::arg(0, &path, info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("HOGDescriptor::Save");
		tryCatch.throwNew(err);
		return;
	}
	HOGDescriptor::unwrapSelf(info)->save(path);
}

NAN_METHOD(HOGDescriptor::Load) {
	FF::TryCatch tryCatch;

	std::string path;
	if (FF::StringConverter::arg(0, &path, info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("HOGDescriptor::Load");
		tryCatch.throwNew(err);
		return;
	}
	HOGDescriptor::unwrapSelf(info)->load(path);
}

NAN_METHOD(HOGDescriptor::Compute) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::ComputeWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::Compute",
    info
  );
}

NAN_METHOD(HOGDescriptor::ComputeAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::ComputeWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::ComputeAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::ComputeGradient) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::ComputeGradientWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::ComputeGradient",
    info
  );
}

NAN_METHOD(HOGDescriptor::ComputeGradientAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::ComputeGradientWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::ComputeGradientAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::Detect) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::Detect",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectROI) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectROIWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectROI",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectROIAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectROIWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectROIAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectMultiScale) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectMultiScaleWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectMultiScale",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectMultiScaleAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectMultiScaleWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectMultiScaleAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectMultiScaleROI) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectMultiScaleROIWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectMultiScaleROI",
    info
  );
}

NAN_METHOD(HOGDescriptor::DetectMultiScaleROIAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::DetectMultiScaleROIWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::DetectMultiScaleROIAsync",
    info
  );
}

NAN_METHOD(HOGDescriptor::GroupRectangles) {
  FF::SyncBinding(
    std::make_shared<HOGDescriptorBindings::GroupRectanglesWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::GroupRectangles",
    info
  );
}

NAN_METHOD(HOGDescriptor::GroupRectanglesAsync) {
  FF::AsyncBinding(
    std::make_shared<HOGDescriptorBindings::GroupRectanglesWorker>(HOGDescriptor::unwrapSelf(info)),
    "HOGDescriptor::GroupRectanglesAsync",
    info
  );
}
