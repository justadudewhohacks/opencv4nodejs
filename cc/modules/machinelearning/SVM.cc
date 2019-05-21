#include "SVM.h"
#include "SVMBindings.h"

Nan::Persistent<v8::FunctionTemplate> SVM::constructor;

NAN_MODULE_INIT(SVM::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SVM::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SVM").ToLocalChecked());

  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("c"), c);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("coef0"), coef0);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("degree"), degree);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("gamma"), gamma);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("nu"), nu);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("p"), p);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("kernelType"), kernelType);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("classWeights"), classWeights);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("varCount"), varCount);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("isTrained"), isTrained);

  Nan::SetPrototypeMethod(ctor, "setParams", SetParams);
  Nan::SetPrototypeMethod(ctor, "train", Train);
  Nan::SetPrototypeMethod(ctor, "trainAuto", TrainAuto);
  Nan::SetPrototypeMethod(ctor, "predict", Predict);
  Nan::SetPrototypeMethod(ctor, "getSupportVectors", GetSupportVectors);
  Nan::SetPrototypeMethod(ctor, "getUncompressedSupportVectors", GetUncompressedSupportVectors);
  Nan::SetPrototypeMethod(ctor, "getDecisionFunction", GetDecisionFunction);
  Nan::SetPrototypeMethod(ctor, "calcError", CalcError);
  Nan::SetPrototypeMethod(ctor, "save", Save);
  Nan::SetPrototypeMethod(ctor, "load", Load);

  Nan::SetPrototypeMethod(ctor, "trainAsync", TrainAsync);
  Nan::SetPrototypeMethod(ctor, "trainAutoAsync", TrainAutoAsync);

  target->Set(Nan::New("SVM").ToLocalChecked(), FF::getFunction(ctor));
};

void SVM::setParams(v8::Local<v8::Object> params) {
	FF::TryCatch tryCatch;
	double c = this->svm->getC();
	double coef0 = this->svm->getCoef0();
	double degree = this->svm->getDegree();
	double gamma = this->svm->getGamma();
	double nu = this->svm->getNu();
	double p = this->svm->getP();
	uint kernelType = this->svm->getKernelType();
	cv::Mat classWeights = this->svm->getClassWeights();
	if (
		DoubleConverter::optProp(&c, "c", params) ||
		DoubleConverter::optProp(&coef0, "coef0", params) ||
		DoubleConverter::optProp(&degree, "degree", params) ||
		DoubleConverter::optProp(&gamma, "gamma", params) ||
		DoubleConverter::optProp(&nu, "nu", params) ||
		DoubleConverter::optProp(&p, "p", params) ||
		UintConverter::optProp(&kernelType, "kernelType", params) ||
		Mat::Converter::optProp(&classWeights, "classWeights", params)
		) {
		tryCatch.throwNew(tryCatch.formatCatchedError("SVM::setParams"));
		return;
	}
	this->svm->setC(c);
	this->svm->setCoef0(coef0);
	this->svm->setDegree(degree);
	this->svm->setGamma(gamma);
	this->svm->setNu(nu);
	this->svm->setP(p);
	this->svm->setKernel(kernelType);
	this->svm->setClassWeights(classWeights);
}

NAN_METHOD(SVM::New) {
  FF_ASSERT_CONSTRUCT_CALL(SVM);
  FF_METHOD_CONTEXT("SVM::New");
  SVM* self = new SVM();
  self->svm = cv::ml::SVM::create();
  if (info.Length() > 0) {
	if (!info[0]->IsObject()) {
		FF_THROW("expected arg 0 to be an object");
	}
	v8::Local<v8::Object> args = v8::Local<v8::Object>::Cast(info[0]);

    Nan::TryCatch tryCatch;
    self->setParams(args);
    if (tryCatch.HasCaught()) {
      tryCatch.ReThrow();
    }
  }
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

NAN_METHOD(SVM::SetParams) {
  if (!info[0]->IsObject()) {
    return Nan::ThrowError("SVM::SetParams - args object required");
  }
  v8::Local<v8::Object> args = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();

  Nan::TryCatch tryCatch;
  FF_UNWRAP(info.This(), SVM)->setParams(args);
  if (tryCatch.HasCaught()) {
    tryCatch.ReThrow();
  }
  info.GetReturnValue().Set(info.This());
};

NAN_METHOD(SVM::Predict) {
  FF_METHOD_CONTEXT("SVM::Predict");

  if (!info[0]->IsArray() && !FF_IS_INSTANCE(Mat::constructor, info[0])) {
    FF_THROW("expected arg 0 to be an ARRAY or an instance of Mat");
  }

  FF::TryCatch tryCatch;
  cv::Mat results;
  if (info[0]->IsArray()) {
	std::vector<float> samples;
	unsigned int flags = 0;
	if (
		FloatArrayConverter::arg(0, &samples, info) ||
		UintConverter::optArg(1, &flags, info)
	) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("SVM::Predict");
		tryCatch.throwNew(err);
		return;
	}
    FF_UNWRAP(info.This(), SVM)->svm->predict(samples, results, (int)flags);
  }
  else {
	cv::Mat samples;
	unsigned int flags = 0;
	if (
		Mat::Converter::arg(0, &samples, info) ||
		UintConverter::optArg(1, &flags, info)
		) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("SVM::Predict");
		tryCatch.throwNew(err);
		return;
	}
	FF_UNWRAP(info.This(), SVM)->svm->predict(samples, results, (int)flags);
  }

  v8::Local<v8::Value> jsResult;
  if (results.cols == 1 && results.rows == 1) {
    jsResult = Nan::New((double)results.at<float>(0, 0));
  }
  else {
    std::vector<float> resultsVec;
    results.col(0).copyTo(resultsVec);
    jsResult = FloatArrayConverter::wrap(resultsVec);
  }
  info.GetReturnValue().Set(jsResult);
}

NAN_METHOD(SVM::GetSupportVectors) {
  v8::Local<v8::Object> jsSupportVectors = FF::newInstance(Nan::New(Mat::constructor));
  FF_UNWRAP_MAT_AND_GET(jsSupportVectors) = FF_UNWRAP(info.This(), SVM)->svm->getSupportVectors();
  info.GetReturnValue().Set(jsSupportVectors);
}

NAN_METHOD(SVM::GetUncompressedSupportVectors) {
  FF_METHOD_CONTEXT("SVM::GetUncompressedSupportVectors");
#if CV_VERSION_MINOR < 2
  FF_THROW("getUncompressedSupportVectors not implemented for v3.0, v3.1");
#else
  v8::Local<v8::Object> jsSupportVectors = FF::newInstance(Nan::New(Mat::constructor));
  FF_UNWRAP_MAT_AND_GET(jsSupportVectors) = FF_UNWRAP(info.This(), SVM)->svm->getUncompressedSupportVectors();
  info.GetReturnValue().Set(jsSupportVectors);
#endif
}

NAN_METHOD(SVM::GetDecisionFunction) {
  FF_METHOD_CONTEXT("SVM::GetDecisionFunction");

  if (!info[0]->IsNumber()) {
    FF_THROW("expected arg 0 to be a Int");
  }

  v8::Local<v8::Object> alpha = FF::newInstance(Nan::New(Mat::constructor));
  v8::Local<v8::Object> svidx = FF::newInstance(Nan::New(Mat::constructor));

  FF::TryCatch tryCatch;
  int i;
  if (IntConverter::arg(0, &i, info)) {
	  v8::Local<v8::Value> err = tryCatch.formatCatchedError("SVM::GetDecisionFunction");
	  tryCatch.throwNew(err);
	  return;
  }
  double rho = FF_UNWRAP(info.This(), SVM)->svm->getDecisionFunction(i, FF_UNWRAP_MAT_AND_GET(alpha), FF_UNWRAP_MAT_AND_GET(svidx));

  v8::Local<v8::Object> ret = Nan::New<v8::Object>();
  Nan::Set(ret, FF::newString("rho"), Nan::New((double)rho));
  Nan::Set(ret, FF::newString("alpha"), alpha);
  Nan::Set(ret, FF::newString("svidx"), svidx);
  info.GetReturnValue().Set(ret);
}

NAN_METHOD(SVM::CalcError) {
	FF::TryCatch tryCatch;
	cv::Ptr<cv::ml::TrainData> trainData;
	bool test;
	if (
		TrainData::Converter::arg(0, &trainData, info) ||
		BoolConverter::arg(1, &test, info)
		) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("SVM::CalcError");
		tryCatch.throwNew(err);
		return;
	}

	v8::Local<v8::Object> jsResponses = FF::newInstance(Nan::New(Mat::constructor));
	float error = FF_UNWRAP(info.This(), SVM)->svm->calcError(trainData, test, FF_UNWRAP_MAT_AND_GET(jsResponses));

	v8::Local<v8::Object> ret = Nan::New<v8::Object>();
	Nan::Set(ret, FF::newString("error"), Nan::New((double)error));
	Nan::Set(ret, FF::newString("responses"), jsResponses);
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(SVM::Save) {
	FF::TryCatch tryCatch;

	std::string path;
	if (StringConverter::arg(0, &path, info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("SVM::Save");
		tryCatch.throwNew(err);
		return;
	}
	Nan::ObjectWrap::Unwrap<SVM>(info.This())->svm->save(path);
}

NAN_METHOD(SVM::Load) {
	FF::TryCatch tryCatch;

	std::string path;
	if (StringConverter::arg(0, &path, info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("SVM::Load");
		tryCatch.throwNew(err);
		return;
	}
#if CV_VERSION_MINOR < 2
	Nan::ObjectWrap::Unwrap<SVM>(info.This())->svm = cv::ml::SVM::load<cv::ml::SVM>(path);
#else
	Nan::ObjectWrap::Unwrap<SVM>(info.This())->svm = cv::ml::SVM::load(path);
#endif
}

NAN_METHOD(SVM::Train) {
  bool isTrainFromTrainData = FF_IS_INSTANCE(TrainData::constructor, info[0]);
  if (isTrainFromTrainData) {
	FF::SyncBinding(
		std::make_shared<SVMBindings::TrainFromTrainDataWorker>(SVM::Converter::unwrap(info.This())),
		"SVM::Train",
		info
	);
  }
  else {
	FF::SyncBinding(
	  std::make_shared<SVMBindings::TrainFromMatWorker>(SVM::Converter::unwrap(info.This())),
	  "SVM::Train",
      info
    );
  }
}

NAN_METHOD(SVM::TrainAsync) {
  bool isTrainFromTrainData = FF_IS_INSTANCE(TrainData::constructor, info[0]);
  if (isTrainFromTrainData) {
	FF::AsyncBinding(
	  std::make_shared<SVMBindings::TrainFromTrainDataWorker>(SVM::Converter::unwrap(info.This())),
	  "SVM::TrainAsync",
	  info
	);
  }
  else {
	FF::AsyncBinding(
	  std::make_shared<SVMBindings::TrainFromMatWorker>(SVM::Converter::unwrap(info.This())),
	  "SVM::TrainAsync",
	  info
	);
  }
}

NAN_METHOD(SVM::TrainAuto) {
  FF::SyncBinding(
    std::make_shared<SVMBindings::TrainAutoWorker>(SVM::Converter::unwrap(info.This())),
    "SVM::TrainAuto",
    info
  );
}

NAN_METHOD(SVM::TrainAutoAsync) {
  FF::AsyncBinding(
    std::make_shared<SVMBindings::TrainAutoWorker>(SVM::Converter::unwrap(info.This())),
    "SVM::TrainAutoAsync",
    info
  );
}
