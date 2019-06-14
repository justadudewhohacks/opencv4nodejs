#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/ml.hpp>
#include "Mat.h"

#ifndef __FF_TRAINDATA_H__
#define __FF_TRAINDATA_H__

class TrainData: public FF::ObjectWrap<TrainData, cv::Ptr<cv::ml::TrainData>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "TrainData";
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	FF_GETTER_CUSTOM(layout, FF::IntConverter, self->getLayout());
	FF_GETTER_CUSTOM(samples, Mat::Converter, self->getSamples());
	FF_GETTER_CUSTOM(responses, Mat::Converter, self->getResponses());
	FF_GETTER_CUSTOM(varIdx, Mat::Converter, self->getVarIdx());
	FF_GETTER_CUSTOM(sampleWeights, Mat::Converter, self->getSampleWeights());
	FF_GETTER_CUSTOM(varType, Mat::Converter, self->getVarType());


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
				FF::IntConverter::arg(1, &layout, info) ||
				Mat::Converter::arg(2, &responses, info)
			);
		}

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::IntArrayConverter::optArg(3, &varIdx, info) ||
				FF::IntArrayConverter::optArg(4, &sampleIdx, info) ||
				FF::FloatArrayConverter::optArg(5, &sampleWeights, info) ||
				FF::UintArrayConverter::optArg(6, &varType, info)
			);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 3);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[3]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::IntArrayConverter::optProp(&varIdx, "varIdx", opts) ||
				FF::IntArrayConverter::optProp(&sampleIdx, "sampleIdx", opts) ||
				FF::FloatArrayConverter::optProp(&sampleWeights, "sampleWeights", opts) ||
				FF::UintArrayConverter::optProp(&varType, "varType", opts)
			);
		}
	};
};

#endif