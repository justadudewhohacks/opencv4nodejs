#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/ml.hpp>
#include "Mat.h"
#include "TrainData.h"
#include "ParamGrid.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_SVM_H__
#define __FF_SVM_H__

class SVM: public FF::ObjectWrap<SVM, cv::Ptr<cv::ml::SVM>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "SVM";
	}

	void setParams(v8::Local<v8::Object> params);

	static NAN_MODULE_INIT(Init);
	
	static FF_GETTER(SVM, c, self->getC());
	static FF_GETTER(SVM, coef0, self->getCoef0());
	static FF_GETTER(SVM, degree, self->getDegree());
	static FF_GETTER(SVM, gamma, self->getGamma());
	static FF_GETTER(SVM, nu, self->getNu());
	static FF_GETTER(SVM, p, self->getP());
	static FF_GETTER(SVM, kernelType, self->getKernelType());
	static FF_GETTER(SVM, varCount, self->getVarCount());
	static FF_GETTER(SVM, isTrained, self->isTrained());
	static NAN_GETTER(classWeights) {
		info.GetReturnValue().Set(Mat::Converter::wrap(unwrapSelf(info)->getClassWeights()));
	}
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