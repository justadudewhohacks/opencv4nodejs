#include "SVM.h"
#include "TrainData.h"
#include "ParamGrid.h"
#include "Mat.h"

Nan::Persistent<v8::FunctionTemplate> SVM::constructor;

NAN_MODULE_INIT(SVM::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SVM::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SVM").ToLocalChecked());

	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("c"), c);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("coef0"), coef0);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("degree"), degree);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("nu"), nu);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("p"), p);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("kernelType"), kernelType);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("classWeights"), classWeights);

	Nan::SetPrototypeMethod(ctor, "setParams", SetParams);
	Nan::SetPrototypeMethod(ctor, "Train", Train);
	Nan::SetPrototypeMethod(ctor, "TrainAuto", TrainAuto);
	Nan::SetPrototypeMethod(ctor, "setParams", Predict);
	Nan::SetPrototypeMethod(ctor, "setParams", PredictWithResults);

	target->Set(Nan::New("SVM").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(SVM::New) {
	SVM* self = new SVM(); 
	self->svm = cv::ml::SVM::create();
	if (info.Length() > 0) {
		FF_REQUIRE_ARGS_OBJ("SVM::New");

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
	FF_REQUIRE_ARGS_OBJ("SVM::SetParams");

	Nan::TryCatch tryCatch;
	FF_UNWRAP(info.This(), SVM)->setParams(args);
	if (tryCatch.HasCaught()) {
		tryCatch.ReThrow();
	}
	info.GetReturnValue().Set(info.This());
};

NAN_METHOD(SVM::Train) {
	FF_METHOD_CONTEXT("SVM::Train");

	SVM* self = FF_UNWRAP(info.This(), SVM);
	FF_VAL ret;
	if (FF_IS_INSTANCE(Mat::constructor, info[0])) {
		FF_ARG_INSTANCE(0, cv::Ptr<cv::ml::TrainData> trainData, TrainData::constructor, FF_UNWRAP_TRAINDATA_AND_GET);
		FF_ARG_UINT_IFDEF(1, unsigned int flags, 0);
		ret = Nan::New(self->svm->train(trainData, flags));
	}
	else {
		FF_ARG_INSTANCE(0, cv::Mat samples, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
		FF_ARG_UINT(1, unsigned int layout);
		FF_ARG_INSTANCE(2, cv::Mat responses, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
		ret = Nan::New(self->svm->train(samples, (int)layout, responses));
	}
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(SVM::TrainAuto) {
	FF_METHOD_CONTEXT("SVM::TrainAuto");

	// required args
	FF_ARG_INSTANCE(0, cv::Ptr<cv::ml::TrainData> trainData, TrainData::constructor, FF_UNWRAP_TRAINDATA_AND_GET);

	// optional args
	FF_OBJ optArgs = (info.Length() == 2 && info[1]->IsObject() && !info[1]->IsUint32() ? info[1]->ToObject() : FF_NEW_OBJ());
	FF_GET_UINT_IFDEF(optArgs, unsigned int kFold, "kFold", 10);
	FF_GET_INSTANCE_IFDEF(optArgs, cv::ml::ParamGrid cGrid, "cGrid", ParamGrid::constructor, FF_UNWRAP_PARAMGRID_AND_GET, ParamGrid, cv::ml::SVM::getDefaultGrid(cv::ml::SVM::C));
	FF_GET_INSTANCE_IFDEF(optArgs, cv::ml::ParamGrid gammaGrid, "gammaGrid", ParamGrid::constructor, FF_UNWRAP_PARAMGRID_AND_GET, ParamGrid, cv::ml::SVM::getDefaultGrid(cv::ml::SVM::GAMMA));
	FF_GET_INSTANCE_IFDEF(optArgs, cv::ml::ParamGrid pGrid, "pGrid", ParamGrid::constructor, FF_UNWRAP_PARAMGRID_AND_GET, ParamGrid, cv::ml::SVM::getDefaultGrid(cv::ml::SVM::P));
	FF_GET_INSTANCE_IFDEF(optArgs, cv::ml::ParamGrid nuGrid, "nuGrid", ParamGrid::constructor, FF_UNWRAP_PARAMGRID_AND_GET, ParamGrid, cv::ml::SVM::getDefaultGrid(cv::ml::SVM::NU));
	FF_GET_INSTANCE_IFDEF(optArgs, cv::ml::ParamGrid coeffGrid, "coeffGrid", ParamGrid::constructor, FF_UNWRAP_PARAMGRID_AND_GET, ParamGrid, cv::ml::SVM::getDefaultGrid(cv::ml::SVM::COEF));
	FF_GET_INSTANCE_IFDEF(optArgs, cv::ml::ParamGrid degreeGrid, "degreeGrid", ParamGrid::constructor, FF_UNWRAP_PARAMGRID_AND_GET, ParamGrid, cv::ml::SVM::getDefaultGrid(cv::ml::SVM::DEGREE));
	FF_GET_BOOL_IFDEF(optArgs, bool balanced, "balanced", false);

	FF_ARG_UINT_IFDEF(1, kFold, kFold);
	FF_ARG_INSTANCE_IFDEF(2, cGrid, ParamGrid::constructor, FF_UNWRAP_PARAMGRID_AND_GET, cGrid);
	FF_ARG_INSTANCE_IFDEF(3, gammaGrid, ParamGrid::constructor, FF_UNWRAP_PARAMGRID_AND_GET, gammaGrid);
	FF_ARG_INSTANCE_IFDEF(4, pGrid, ParamGrid::constructor, FF_UNWRAP_PARAMGRID_AND_GET, pGrid);
	FF_ARG_INSTANCE_IFDEF(5, nuGrid, ParamGrid::constructor, FF_UNWRAP_PARAMGRID_AND_GET, nuGrid);
	FF_ARG_INSTANCE_IFDEF(6, coeffGrid, ParamGrid::constructor, FF_UNWRAP_PARAMGRID_AND_GET, coeffGrid);
	FF_ARG_INSTANCE_IFDEF(7, degreeGrid, ParamGrid::constructor, FF_UNWRAP_PARAMGRID_AND_GET, degreeGrid);
	FF_ARG_BOOL_IFDEF(8, balanced, balanced);

	bool ret = FF_UNWRAP(info.This(), SVM)->svm->trainAuto(trainData, (int)kFold, cGrid, gammaGrid, pGrid, nuGrid, coeffGrid, degreeGrid, balanced);
	info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(SVM::Predict) {
	FF_METHOD_CONTEXT("SVM::Predict");

	// required args
	FF_ARG_INSTANCE(0, cv::Mat samples, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

	// optional args
	FF_ARG_UINT_IFDEF(1, unsigned int flags, 0);

	float probability = FF_UNWRAP(info.This(), SVM)->svm->predict(samples, cv::noArray(), (int)flags);
	info.GetReturnValue().Set(Nan::New(probability));
}

NAN_METHOD(SVM::PredictWithResults) {
	FF_METHOD_CONTEXT("SVM::PredictWithResults");

	// required args
	FF_ARG_INSTANCE(0, cv::Mat samples, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

	// optional args
	FF_ARG_UINT_IFDEF(1, unsigned int flags, 0);

	FF_OBJ jsResults = FF_NEW_INSTANCE(Mat::constructor);
	float probability = FF_UNWRAP(info.This(), SVM)->svm->predict(samples, FF_UNWRAP_MAT_AND_GET(jsResults), flags);
	FF_OBJ ret = FF_NEW_OBJ();
	ret->Set(FF_NEW_STRING("results"), jsResults);
	ret->Set(FF_NEW_STRING("probability"), Nan::New(probability));
	info.GetReturnValue().Set(ret);
}

void SVM::setParams(v8::Local<v8::Object> params) {
	FF_METHOD_CONTEXT("SVM::SetParams");

	FF_GET_NUMBER_IFDEF(params, double c, "c", this->svm->getC());
	FF_GET_NUMBER_IFDEF(params, double coef0, "coef0", this->svm->getCoef0());
	FF_GET_NUMBER_IFDEF(params, double degree, "degree", this->svm->getDegree());
	FF_GET_NUMBER_IFDEF(params, double nu, "nu", this->svm->getNu());
	FF_GET_NUMBER_IFDEF(params, double p, "p", this->svm->getP());
	FF_GET_NUMBER_IFDEF(params, unsigned int kernelType, "kernelType", this->svm->getKernelType());
	FF_GET_INSTANCE_IFDEF(params, cv::Mat classWeights, "classWeights", Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat, this->svm->getClassWeights());

	this->svm->setC(c);
	this->svm->setCoef0(coef0);
	this->svm->setDegree(degree);
	this->svm->setNu(nu);
	this->svm->setP(p);
	this->svm->setKernel(kernelType);
	this->svm->setClassWeights(classWeights);
}