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
	static FF_GETTER_JSOBJ(TrainData, samples, trainData->getSamples(), Mat);
	static FF_GETTER_JSOBJ(TrainData, responses, trainData->getResponses(), Mat);
	static FF_GETTER_JSOBJ(TrainData, varIdx, trainData->getVarIdx(), Mat);
	static FF_GETTER_JSOBJ(TrainData, sampleWeights, trainData->getSampleWeights(), Mat);
	static FF_GETTER_JSOBJ(TrainData, varType, trainData->getVarType(), Mat);

	// TODO Getters

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::ml::TrainData>* getNativeObjectPtr() { return &trainData; }
	cv::Ptr<cv::ml::TrainData> getNativeObject() { return trainData; }

	typedef InstanceConverter<TrainData, cv::Ptr<cv::ml::TrainData> > Converter;

	static const char* getClassName() {
		return "TrainData";
	}

	struct NewWorker : public CatchCvExceptionWorker {
	public:
		cv::Mat samples;
		int layout;
		cv::Mat responses;
		std::vector<int> varIdx;
		std::vector<int> sampleIdx;
		std::vector<float> sampleWeights;
		std::vector<uint> varType;

		std::string executeCatchCvExceptionWorker() {
			return "";
		}

		bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				Mat::Converter::arg(0, &samples, info) ||
				IntConverter::arg(1, &layout, info) ||
				Mat::Converter::arg(2, &responses, info)
			);
		}

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				IntArrayConverter::optArg(3, &varIdx, info) ||
				IntArrayConverter::optArg(4, &sampleIdx, info) ||
				FloatArrayConverter::optArg(5, &sampleWeights, info) ||
				UintArrayConverter::optArg(6, &varType, info)
			);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 3);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[3]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				IntArrayConverter::optProp(&varIdx, "varIdx", opts) ||
				IntArrayConverter::optProp(&sampleIdx, "sampleIdx", opts) ||
				FloatArrayConverter::optProp(&sampleWeights, "sampleWeights", opts) ||
				UintArrayConverter::optProp(&varType, "varType", opts)
			);
		}
	};
};

#endif