#include "SVM.h"
#include "SVMBindings.h"

Nan::Persistent<v8::FunctionTemplate> SVM::constructor;

NAN_MODULE_INIT(SVM::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SVM::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SVM").ToLocalChecked());

  Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("c"), c);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("coef0"), coef0);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("degree"), degree);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("gamma"), gamma);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("nu"), nu);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("p"), p);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("kernelType"), kernelType);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("classWeights"), classWeights);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("varCount"), varCount);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("isTrained"), isTrained);

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

  target->Set(Nan::New("SVM").ToLocalChecked(), ctor->GetFunction());
};

void SVM::setParams(v8::Local<v8::Object> params) {
  FF_METHOD_CONTEXT("SVM::SetParams");

  FF_GET_NUMBER_IFDEF(params, double c, "c", this->svm->getC());
  FF_GET_NUMBER_IFDEF(params, double coef0, "coef0", this->svm->getCoef0());
  FF_GET_NUMBER_IFDEF(params, double degree, "degree", this->svm->getDegree());
  FF_GET_NUMBER_IFDEF(params, double gamma, "gamma", this->svm->getGamma());
  FF_GET_NUMBER_IFDEF(params, double nu, "nu", this->svm->getNu());
  FF_GET_NUMBER_IFDEF(params, double p, "p", this->svm->getP());
  FF_GET_NUMBER_IFDEF(params, unsigned int kernelType, "kernelType", this->svm->getKernelType());
  FF_GET_INSTANCE_IFDEF(params, cv::Mat classWeights, "classWeights", Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat, this->svm->getClassWeights());

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
  FF_METHOD_CONTEXT("SVM::New");
  SVM* self = new SVM();
  self->svm = cv::ml::SVM::create();
  if (info.Length() > 0) {
    FF_ARG_OBJ(0, FF_OBJ args);

    Nan::TryCatch tryCatch;
    self->setParams(args);
    if (tryCatch.HasCaught()) {
      tryCatch.ReThrow();
    }
  }
  self->Wrap(info.Holder());
  FF_RETURN(info.Holder());
};

NAN_METHOD(SVM::SetParams) {
  if (!info[0]->IsObject()) {
    return Nan::ThrowError("SVM::SetParams - args object required");  
  }                                                                                            
  v8::Local<v8::Object> args = info[0]->ToObject();

  Nan::TryCatch tryCatch;
  FF_UNWRAP(info.This(), SVM)->setParams(args);
  if (tryCatch.HasCaught()) {
    tryCatch.ReThrow();
  }
  FF_RETURN(info.This());
};

NAN_METHOD(SVM::Predict) {
  FF_METHOD_CONTEXT("SVM::Predict");

  if (!info[0]->IsArray() && !FF_IS_INSTANCE(Mat::constructor, info[0])) {
    FF_THROW("expected arg 0 to be an ARRAY or an instance of Mat");
  }

  cv::Mat results;
  if (info[0]->IsArray()) {
	std::vector<float> samples;
	FloatArrayConverter::arg(0, &samples, info);
    FF_ARG_UINT_IFDEF(1, unsigned int flags, 0);
    FF_UNWRAP(info.This(), SVM)->svm->predict(samples, results, (int)flags);
  }
  else {
    FF_ARG_INSTANCE(0, cv::Mat samples, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
    FF_ARG_UINT_IFDEF(1, unsigned int flags, 0);
    FF_UNWRAP(info.This(), SVM)->svm->predict(samples, results, (int)flags);
  }

  FF_VAL jsResult;
  if (results.cols == 1 && results.rows == 1) {
    jsResult = Nan::New((double)results.at<float>(0, 0));
  }
  else {
    std::vector<float> resultsVec;
    results.col(0).copyTo(resultsVec);
    FF_PACK_ARRAY(resultArray, resultsVec);
    jsResult = resultArray;
  }
  FF_RETURN(jsResult);
}

NAN_METHOD(SVM::GetSupportVectors) {
  FF_OBJ jsSupportVectors = FF_NEW_INSTANCE(Mat::constructor);
  FF_UNWRAP_MAT_AND_GET(jsSupportVectors) = FF_UNWRAP(info.This(), SVM)->svm->getSupportVectors();
  FF_RETURN(jsSupportVectors);
}

NAN_METHOD(SVM::GetUncompressedSupportVectors) {
  FF_METHOD_CONTEXT("SVM::GetUncompressedSupportVectors");
#if CV_VERSION_MINOR < 2
  FF_THROW("getUncompressedSupportVectors not implemented for v3.0, v3.1");
#else
  FF_OBJ jsSupportVectors = FF_NEW_INSTANCE(Mat::constructor);
  FF_UNWRAP_MAT_AND_GET(jsSupportVectors) = FF_UNWRAP(info.This(), SVM)->svm->getUncompressedSupportVectors();
  FF_RETURN(jsSupportVectors);
#endif
}

NAN_METHOD(SVM::GetDecisionFunction) {
  FF_METHOD_CONTEXT("SVM::GetDecisionFunction");

  if (!info[0]->IsNumber()) {
    FF_THROW("expected arg 0 to be a Int");
  }

  FF_OBJ alpha = FF_NEW_INSTANCE(Mat::constructor);
  FF_OBJ svidx = FF_NEW_INSTANCE(Mat::constructor);
  FF_ARG_INT(0, int i);
  double rho = FF_UNWRAP(info.This(), SVM)->svm->getDecisionFunction(i, FF_UNWRAP_MAT_AND_GET(alpha), FF_UNWRAP_MAT_AND_GET(svidx));

  FF_OBJ ret = FF_NEW_OBJ();
  Nan::Set(ret, FF_NEW_STRING("rho"), Nan::New((double)rho));
  Nan::Set(ret, FF_NEW_STRING("alpha"), alpha);
  Nan::Set(ret, FF_NEW_STRING("svidx"), svidx);
  FF_RETURN(ret);
}

NAN_METHOD(SVM::CalcError) {
  FF_METHOD_CONTEXT("SVM::CalcError");
  FF_ARG_INSTANCE(0, cv::Ptr<cv::ml::TrainData> trainData, TrainData::constructor, FF_UNWRAP_TRAINDATA_AND_GET);
  FF_ARG_BOOL(1, bool test);

  FF_OBJ jsResponses = FF_NEW_INSTANCE(Mat::constructor);
  float error = FF_UNWRAP(info.This(), SVM)->svm->calcError(trainData, test, FF_UNWRAP_MAT_AND_GET(jsResponses));

  FF_OBJ ret = FF_NEW_OBJ();
  Nan::Set(ret, FF_NEW_STRING("error"), Nan::New((double)error));
  Nan::Set(ret, FF_NEW_STRING("responses"), jsResponses);
  FF_RETURN(ret);
}

NAN_METHOD(SVM::Save) {
  FF_METHOD_CONTEXT("SVM::Save");
  FF_ARG_STRING(0, std::string path);
  FF_UNWRAP(info.This(), SVM)->svm->save(path);
}

NAN_METHOD(SVM::Load) {
  FF_METHOD_CONTEXT("SVM::Load");
  FF_ARG_STRING(0, std::string path);
#if CV_VERSION_MINOR < 2
  FF_UNWRAP(info.This(), SVM)->svm = cv::ml::SVM::load<cv::ml::SVM>(path);
#else
  FF_UNWRAP(info.This(), SVM)->svm = cv::ml::SVM::load(path);
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
