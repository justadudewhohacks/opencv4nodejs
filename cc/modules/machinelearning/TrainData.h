#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/ml.hpp>
#include "Mat.h"

#ifndef __FF_TRAINDATA_H__
#define __FF_TRAINDATA_H__

class TrainData: public Nan::ObjectWrap {
public:
	cv::Ptr<cv::ml::TrainData> trainData;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static FF_GETTER(TrainData, layout, trainData->getLayout());
	static FF_GETTER_JSOBJ(TrainData, samples, trainData->getSamples(), FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(TrainData, responses, trainData->getResponses(), FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(TrainData, varIdx, trainData->getVarIdx(), FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(TrainData, sampleWeights, trainData->getSampleWeights(), FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(TrainData, varType, trainData->getVarType(), FF_UNWRAP_MAT_AND_GET, Mat::constructor);

	// TODO Getters

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::ml::TrainData>* getNativeObjectPtr() { return &trainData; }
	cv::Ptr<cv::ml::TrainData> getNativeObject() { return trainData; }

	typedef InstanceConverter<TrainData, cv::Ptr<cv::ml::TrainData> > Converter;

	static const char* getClassName() {
		return "TrainData";
	}
};

#endif