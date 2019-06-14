#include "opencv_modules.h"

#ifdef HAVE_OPENCV_ML

#include "SVM.h"
#include "SVMBindings.h"

Nan::Persistent<v8::FunctionTemplate> SVM::constructor;

NAN_MODULE_INIT(SVM::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SVM::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SVM").ToLocalChecked());

  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("c"), c_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("coef0"), coef0_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("degree"), degree_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("gamma"), gamma_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("nu"), nu_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("p"), p_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("kernelType"), kernelType_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("classWeights"), classWeights_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("varCount"), varCount_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("isTrained"), isTrained_getter);

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

  Nan::Set(target,Nan::New("SVM").ToLocalChecked(), FF::getFunction(ctor));
};

void SVM::setParams(v8::Local<v8::Object> params) {
	FF::TryCatch tryCatch("SVM::setParams");
	double c = this->self->getC();
	double coef0 = this->self->getCoef0();
	double degree = this->self->getDegree();
	double gamma = this->self->getGamma();
	double nu = this->self->getNu();
	double p = this->self->getP();
	uint kernelType = this->self->getKernelType();
	cv::Mat classWeights = this->self->getClassWeights();
	if (
		FF::DoubleConverter::optProp(&c, "c", params) ||
		FF::DoubleConverter::optProp(&coef0, "coef0", params) ||
		FF::DoubleConverter::optProp(&degree, "degree", params) ||
		FF::DoubleConverter::optProp(&gamma, "gamma", params) ||
		FF::DoubleConverter::optProp(&nu, "nu", params) ||
		FF::DoubleConverter::optProp(&p, "p", params) ||
		FF::UintConverter::optProp(&kernelType, "kernelType", params) ||
		Mat::Converter::optProp(&classWeights, "classWeights", params)
		) {
		return tryCatch.reThrow();
	}
	this->self->setC(c);
	this->self->setCoef0(coef0);
	this->self->setDegree(degree);
	this->self->setGamma(gamma);
	this->self->setNu(nu);
	this->self->setP(p);
	this->self->setKernel(kernelType);
	this->self->setClassWeights(classWeights);
}

NAN_METHOD(SVM::New) {
	FF::TryCatch tryCatch("SVM::New");
  FF_ASSERT_CONSTRUCT_CALL();
  SVM* self = new SVM();
  self->setNativeObject(cv::ml::SVM::create());
  if (info.Length() > 0) {
	if (!info[0]->IsObject()) {
		return tryCatch.throwError("expected arg 0 to be an object");
	}
	v8::Local<v8::Object> args = v8::Local<v8::Object>::Cast(info[0]);

    self->setParams(args);
    if (tryCatch.HasCaught()) {
      return tryCatch.reThrow();
    }
  }
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

NAN_METHOD(SVM::SetParams) {
	FF::TryCatch tryCatch("SVM::SetParams");
  if (!info[0]->IsObject()) {
    return tryCatch.throwError("SVM::SetParams - args object required");
  }
  v8::Local<v8::Object> args = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();

  SVM::unwrapThis(info)->setParams(args);
  if (tryCatch.HasCaught()) {
	  return tryCatch.reThrow();
  }
  info.GetReturnValue().Set(info.This());
};

NAN_METHOD(SVM::Predict) {
	FF::TryCatch tryCatch("SVM::Predict");

  if (!info[0]->IsArray() && !Mat::hasInstance(info[0])) {
	  return tryCatch.throwError("expected arg 0 to be an ARRAY or an instance of Mat");
  }

  cv::Mat results;
  if (info[0]->IsArray()) {
	std::vector<float> samples;
	unsigned int flags = 0;
	if (
		FF::FloatArrayConverter::arg(0, &samples, info) ||
		FF::UintConverter::optArg(1, &flags, info)
	) {
		return tryCatch.reThrow();
	}
    SVM::unwrapSelf(info)->predict(samples, results, (int)flags);
  }
  else {
	cv::Mat samples;
	unsigned int flags = 0;
	if (
		Mat::Converter::arg(0, &samples, info) ||
		FF::UintConverter::optArg(1, &flags, info)
		) {
		return tryCatch.reThrow();
	}
	SVM::unwrapSelf(info)->predict(samples, results, (int)flags);
  }

  v8::Local<v8::Value> jsResult;
  if (results.cols == 1 && results.rows == 1) {
    jsResult = Nan::New((double)results.at<float>(0, 0));
  }
  else {
    std::vector<float> resultsVec;
    results.col(0).copyTo(resultsVec);
    jsResult = FF::FloatArrayConverter::wrap(resultsVec);
  }
  info.GetReturnValue().Set(jsResult);
}

NAN_METHOD(SVM::GetSupportVectors) {
  info.GetReturnValue().Set(Mat::Converter::wrap(SVM::unwrapSelf(info)->getSupportVectors()));
}

NAN_METHOD(SVM::GetUncompressedSupportVectors) {
	FF::TryCatch tryCatch("SVM::GetUncompressedSupportVectors");
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
	info.GetReturnValue().Set(Mat::Converter::wrap(SVM::unwrapSelf(info)->getUncompressedSupportVectors()));
#else
	return tryCatch.throwError("getUncompressedSupportVectors not implemented for v3.0, v3.1");
#endif
}

NAN_METHOD(SVM::GetDecisionFunction) {
	FF::TryCatch tryCatch("SVM::GetDecisionFunction");

  if (!info[0]->IsNumber()) {
	  return tryCatch.throwError("expected arg 0 to be a Int");
  }

  int i;
  if (FF::IntConverter::arg(0, &i, info)) {
	  return tryCatch.reThrow();
  }

  cv::Mat alpha, svidx;
  double rho = SVM::unwrapSelf(info)->getDecisionFunction(i, alpha, svidx);

  v8::Local<v8::Object> ret = Nan::New<v8::Object>();
  Nan::Set(ret, FF::newString("rho"), Nan::New((double)rho));
  Nan::Set(ret, FF::newString("alpha"), Mat::Converter::wrap(alpha));
  Nan::Set(ret, FF::newString("svidx"), Mat::Converter::wrap(svidx));
  info.GetReturnValue().Set(ret);
}

NAN_METHOD(SVM::CalcError) {
	FF::TryCatch tryCatch("SVM::CalcError");
	cv::Ptr<cv::ml::TrainData> trainData;
	bool test;
	if (
		TrainData::Converter::arg(0, &trainData, info) ||
		FF::BoolConverter::arg(1, &test, info)
		) {
		return tryCatch.reThrow();
	}

	v8::Local<v8::Object> jsResponses = FF::newInstance(Nan::New(Mat::constructor));
	float error = SVM::unwrapSelf(info)->calcError(trainData, test, Mat::Converter::unwrapUnchecked(jsResponses));

	v8::Local<v8::Object> ret = Nan::New<v8::Object>();
	Nan::Set(ret, FF::newString("error"), Nan::New((double)error));
	Nan::Set(ret, FF::newString("responses"), jsResponses);
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(SVM::Save) {
	FF::TryCatch tryCatch("SVM::Save");

	std::string path;
	if (FF::StringConverter::arg(0, &path, info)) {
		return tryCatch.reThrow();
	}
	SVM::unwrapSelf(info)->save(path);
}

NAN_METHOD(SVM::Load) {
	FF::TryCatch tryCatch("SVM::Load");

	std::string path;
	if (FF::StringConverter::arg(0, &path, info)) {
		return tryCatch.reThrow();
	}
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
	SVM::unwrapThis(info)->setNativeObject(cv::ml::SVM::load(path));
#else
	SVM::unwrapThis(info)->setNativeObject(cv::ml::SVM::load<cv::ml::SVM>(path));
#endif
}

NAN_METHOD(SVM::Train) {
  bool isTrainFromTrainData = TrainData::hasInstance(info[0]);
  if (isTrainFromTrainData) {
	FF::executeSyncBinding(
		std::make_shared<SVMBindings::TrainFromTrainDataWorker>(SVM::unwrapSelf(info)),
		"SVM::Train",
		info
	);
  }
  else {
	FF::executeSyncBinding(
	  std::make_shared<SVMBindings::TrainFromMatWorker>(SVM::unwrapSelf(info)),
	  "SVM::Train",
      info
    );
  }
}

NAN_METHOD(SVM::TrainAsync) {
  bool isTrainFromTrainData = TrainData::hasInstance(info[0]);
  if (isTrainFromTrainData) {
	FF::executeAsyncBinding(
	  std::make_shared<SVMBindings::TrainFromTrainDataWorker>(SVM::unwrapSelf(info)),
	  "SVM::TrainAsync",
	  info
	);
  }
  else {
	FF::executeAsyncBinding(
	  std::make_shared<SVMBindings::TrainFromMatWorker>(SVM::unwrapSelf(info)),
	  "SVM::TrainAsync",
	  info
	);
  }
}

NAN_METHOD(SVM::TrainAuto) {
  FF::executeSyncBinding(
    std::make_shared<SVMBindings::TrainAutoWorker>(SVM::unwrapSelf(info)),
    "SVM::TrainAuto",
    info
  );
}

NAN_METHOD(SVM::TrainAutoAsync) {
  FF::executeAsyncBinding(
    std::make_shared<SVMBindings::TrainAutoWorker>(SVM::unwrapSelf(info)),
    "SVM::TrainAutoAsync",
    info
  );
}

#endif
