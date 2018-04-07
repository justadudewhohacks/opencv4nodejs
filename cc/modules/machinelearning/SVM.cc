#include "SVM.h"
#include "TrainData.h"
#include "ParamGrid.h"
#include "CatchCvExceptionWorker.h"

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
	Nan::SetPrototypeMethod(ctor, "calcError", CalcError);
	Nan::SetPrototypeMethod(ctor, "save", Save);
	Nan::SetPrototypeMethod(ctor, "load", Load);

	Nan::SetPrototypeMethod(ctor, "trainAsync", TrainAsync);
	Nan::SetPrototypeMethod(ctor, "trainAutoAsync", TrainAutoAsync);

	target->Set(Nan::New("SVM").ToLocalChecked(), ctor->GetFunction());
};

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
		FF_ARG_UNPACK_FLOAT_ARRAY(0, samples);
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

struct SVM::TrainFromTrainDataWorker : CatchCvExceptionWorker {
public:
	cv::Ptr<cv::ml::SVM> svm;

	TrainFromTrainDataWorker(cv::Ptr<cv::ml::SVM> svm) {
		this->svm = svm;
	}

	cv::Ptr<cv::ml::TrainData> trainData;
	uint flags;

	bool ret;

	const char* executeCatchCvExceptionWorker() {
		ret = svm->train(trainData, (int)flags);
		return "";
	}

	FF_VAL getReturnValue() {
		return Nan::New(ret);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return TrainData::Converter::arg(0, &trainData, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return UintConverter::optArg(1, &flags, info);
	}
};

struct SVM::TrainFromMatWorker : CatchCvExceptionWorker {
public:
	cv::Ptr<cv::ml::SVM> svm;

	TrainFromMatWorker(cv::Ptr<cv::ml::SVM> svm) {
		this->svm = svm;
	}

	cv::Mat samples;
	uint layout;
	cv::Mat responses;

	bool ret;

	const char* executeCatchCvExceptionWorker() {
		ret = svm->train(samples, (int)layout, responses);
		return "";
	}

	FF_VAL getReturnValue() {
		return Nan::New(ret);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &samples, info) ||
			UintConverter::arg(1, &layout, info) ||
			Mat::Converter::arg(2, &responses, info)
		);
	}
};

NAN_METHOD(SVM::Train) {
	if (!FF_IS_INSTANCE(TrainData::constructor, info[0]) && !FF_IS_INSTANCE(Mat::constructor, info[0])) {
		return Nan::ThrowError("SVM::Train - Error: expected argument 0 to be of type TrainData or Mat");
	}

	bool isTrainFromTrainData = FF_IS_INSTANCE(TrainData::constructor, info[0]);
	if (isTrainFromTrainData) {
		TrainFromTrainDataWorker worker(SVM::Converter::unwrap(info.This()));
		FF_WORKER_SYNC("SVM::Train", worker);
		info.GetReturnValue().Set(worker.getReturnValue());
	}
	else {
		TrainFromMatWorker worker(SVM::Converter::unwrap(info.This()));
		FF_WORKER_SYNC("SVM::Train", worker);
		info.GetReturnValue().Set(worker.getReturnValue());
	}
}

NAN_METHOD(SVM::TrainAsync) {
	if (!FF_IS_INSTANCE(TrainData::constructor, info[0]) && !FF_IS_INSTANCE(Mat::constructor, info[0])) {
		return Nan::ThrowError("SVM::TrainAsync - Error: expected argument 0 to be of type TrainData or Mat");
	}

	bool isTrainFromTrainData = FF_IS_INSTANCE(TrainData::constructor, info[0]);
	if (isTrainFromTrainData) {
		TrainFromTrainDataWorker worker(SVM::Converter::unwrap(info.This()));
		FF_WORKER_ASYNC("SVM::TrainAsync", TrainFromTrainDataWorker, worker);
	}
	else {
		TrainFromMatWorker worker(SVM::Converter::unwrap(info.This()));
		FF_WORKER_ASYNC("SVM::TrainAsync", TrainFromMatWorker, worker);
	}
}

struct SVM::TrainAutoWorker : CatchCvExceptionWorker  {
public:
	cv::Ptr<cv::ml::SVM> svm;

	TrainAutoWorker(cv::Ptr<cv::ml::SVM> svm) {
		this->svm = svm;
	}

	cv::Ptr<cv::ml::TrainData> trainData;
	uint kFold = 10;
	cv::ml::ParamGrid cGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::C);
	cv::ml::ParamGrid gammaGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::GAMMA);
	cv::ml::ParamGrid pGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::P);
	cv::ml::ParamGrid nuGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::NU);
	cv::ml::ParamGrid coeffGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::COEF);
	cv::ml::ParamGrid degreeGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::DEGREE);
	bool balanced = false;

	bool ret;

	const char* executeCatchCvExceptionWorker() {
		ret = svm->trainAuto(trainData, (int)kFold, cGrid, gammaGrid, pGrid, nuGrid, coeffGrid, degreeGrid, balanced);
		return "";
	}

	FF_VAL getReturnValue() {
		return Nan::New(ret);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return TrainData::Converter::arg(0, &trainData, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			UintConverter::optArg(1, &kFold, info) ||
			ParamGrid::Converter::optArg(2, &cGrid, info) ||
			ParamGrid::Converter::optArg(3, &gammaGrid, info) ||
			ParamGrid::Converter::optArg(4, &pGrid, info) ||
			ParamGrid::Converter::optArg(5, &nuGrid, info) ||
			ParamGrid::Converter::optArg(6, &coeffGrid, info) ||
			ParamGrid::Converter::optArg(7, &degreeGrid, info) ||
			BoolConverter::optArg(8, &balanced, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[1]->ToObject();
		return (
			UintConverter::optProp(&kFold, "kFold", opts) ||
			ParamGrid::Converter::optProp(&cGrid, "cGrid", opts) ||
			ParamGrid::Converter::optProp(&gammaGrid, "gammaGrid", opts) ||
			ParamGrid::Converter::optProp(&pGrid, "pGrid", opts) ||
			ParamGrid::Converter::optProp(&nuGrid, "nuGrid", opts) ||
			ParamGrid::Converter::optProp(&coeffGrid, "coeffGrid", opts) ||
			ParamGrid::Converter::optProp(&degreeGrid, "degreeGrid", opts) ||
			BoolConverter::optProp(&balanced, "balanced", opts)
		);
	}
};

NAN_METHOD(SVM::TrainAuto) {
	TrainAutoWorker worker(SVM::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("SVM::TrainAuto", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(SVM::TrainAutoAsync) {
	TrainAutoWorker worker(SVM::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("SVM::TrainAutoAsync", TrainAutoWorker, worker);
}