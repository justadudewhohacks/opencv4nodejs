#include "macros.h"
#include "BackgroundSubtractor.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_BACKGROUNDSUBTRACTORMOG2_H__
#define __FF_BACKGROUNDSUBTRACTORMOG2_H__

class BackgroundSubtractorMOG2 : public BackgroundSubtractor {
public:
	cv::Ptr<cv::BackgroundSubtractorMOG2> subtractor;

	static FF_GETTER(BackgroundSubtractorMOG2, GetHistory, subtractor->getHistory());
	static FF_GETTER(BackgroundSubtractorMOG2, GetVarThreshold, subtractor->getVarThreshold());
	static FF_GETTER(BackgroundSubtractorMOG2, GetDetectShadows, subtractor->getDetectShadows());

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::BackgroundSubtractor> getSubtractor() {
		return subtractor;
	}

	struct NewWorker : CatchCvExceptionWorker {
	public:

		uint history = 500;
		double varThreshold = 16;
		bool detectShadows = true;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				UintConverter::optArg(0, &history, info) ||
				DoubleConverter::optArg(1, &varThreshold, info) ||
				BoolConverter::optArg(2, &detectShadows, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				UintConverter::optProp(&history, "history", opts) ||
				DoubleConverter::optProp(&varThreshold, "varThreshold", opts) ||
				BoolConverter::optProp(&detectShadows, "detectShadows", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};
};

#endif