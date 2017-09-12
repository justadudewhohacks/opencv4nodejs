#include "macros.h"
#include <opencv2/ml.hpp>
#include "Mat.h"

#ifndef __FF_SVM_H__
#define __FF_SVM_H__

class SVM: public Nan::ObjectWrap {
public:
	cv::Ptr<cv::ml::SVM> svm;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);
	static NAN_METHOD(SetParams);
	static NAN_METHOD(Train);
	static NAN_METHOD(TrainAuto);
	static NAN_METHOD(Predict);
	static NAN_METHOD(GetSupportVectors);
	static NAN_METHOD(GetUncompressedSupportVectors);
	static NAN_METHOD(CalcError);
	static NAN_METHOD(Save);

	static FF_GETTER(SVM, c, svm->getC());
	static FF_GETTER(SVM, coef0, svm->getCoef0());
	static FF_GETTER(SVM, degree, svm->getDegree());
	static FF_GETTER(SVM, nu, svm->getNu());
	static FF_GETTER(SVM, p, svm->getP());
	static FF_GETTER(SVM, kernelType, svm->getKernelType());
	static FF_GETTER(SVM, varCount, svm->getVarCount());
	static FF_GETTER(SVM, isTrained, svm->isTrained());
	static FF_GETTER_JSOBJ(SVM, classWeights, svm->getClassWeights(), FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	// TODO custom kernel

	void setParams(v8::Local<v8::Object> params);
  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif