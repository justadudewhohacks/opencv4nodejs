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
	
	FF_GETTER_CUSTOM(c, FF::DoubleConverter, self->getC());
	FF_GETTER_CUSTOM(coef0, FF::DoubleConverter, self->getCoef0());
	FF_GETTER_CUSTOM(degree, FF::DoubleConverter, self->getDegree());
	FF_GETTER_CUSTOM(gamma, FF::DoubleConverter, self->getGamma());
	FF_GETTER_CUSTOM(nu, FF::DoubleConverter, self->getNu());
	FF_GETTER_CUSTOM(p, FF::DoubleConverter, self->getP());
	FF_GETTER_CUSTOM(kernelType, FF::IntConverter, self->getKernelType());
	FF_GETTER_CUSTOM(varCount, FF::IntConverter, self->getVarCount());
	FF_GETTER_CUSTOM(isTrained, FF::BoolConverter, self->isTrained());
	FF_GETTER_CUSTOM(classWeights, Mat::Converter, self->getClassWeights());

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