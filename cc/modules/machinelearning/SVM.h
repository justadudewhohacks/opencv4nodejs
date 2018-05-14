#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/ml.hpp>
#include "Mat.h"
#include "TrainData.h"
#include "ParamGrid.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_SVM_H__
#define __FF_SVM_H__

class SVM: public Nan::ObjectWrap {
public:
	cv::Ptr<cv::ml::SVM> svm;

	void setParams(v8::Local<v8::Object> params);
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::ml::SVM>* getNativeObjectPtr() { return &svm; }
	cv::Ptr<cv::ml::SVM> getNativeObject() { return svm; }

	typedef InstanceConverter<SVM, cv::Ptr<cv::ml::SVM> > Converter;

	static const char* getClassName() {
		return "SVM";
	}

	static NAN_MODULE_INIT(Init);
	
	static FF_GETTER(SVM, c, svm->getC());
	static FF_GETTER(SVM, coef0, svm->getCoef0());
	static FF_GETTER(SVM, degree, svm->getDegree());
	static FF_GETTER(SVM, gamma, svm->getGamma());
	static FF_GETTER(SVM, nu, svm->getNu());
	static FF_GETTER(SVM, p, svm->getP());
	static FF_GETTER(SVM, kernelType, svm->getKernelType());
	static FF_GETTER(SVM, varCount, svm->getVarCount());
	static FF_GETTER(SVM, isTrained, svm->isTrained());
	static FF_GETTER_JSOBJ(SVM, classWeights, svm->getClassWeights(), FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	// TODO custom kernel

	static NAN_METHOD(New);
	static NAN_METHOD(SetParams);
	static NAN_METHOD(Predict);
	static NAN_METHOD(GetSupportVectors);
	static NAN_METHOD(GetUncompressedSupportVectors);
	static NAN_METHOD(GetDecisionFunction);
	static NAN_METHOD(CalcError);
	static NAN_METHOD(Save);
	static NAN_METHOD(Load);
	static NAN_METHOD(Train);
	static NAN_METHOD(TrainAsync);
	static NAN_METHOD(TrainAuto);
	static NAN_METHOD(TrainAutoAsync);
};

#endif