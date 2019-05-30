#include "macros.h"
#include "BackgroundSubtractor.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_BACKGROUNDSUBTRACTORKNN_H__
#define __FF_BACKGROUNDSUBTRACTORKNN_H__

class BackgroundSubtractorKNN : public BackgroundSubtractor {
public:
	cv::Ptr<cv::BackgroundSubtractorKNN> subtractor;

	static FF_GETTER(BackgroundSubtractorKNN, GetHistory, subtractor->getHistory());
	static FF_GETTER(BackgroundSubtractorKNN, GetDist2Threshold, subtractor->getDist2Threshold());
	static FF_GETTER(BackgroundSubtractorKNN, GetDetectShadows, subtractor->getDetectShadows());

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::BackgroundSubtractor> getSubtractor() {
		return subtractor;
	}

	struct NewWorker : CatchCvExceptionWorker {
	public:

		uint history = 500;
		double dist2Threshold = 400;
		bool detectShadows = true;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::IntConverter::optArg(0, &history, info) ||
				FF::DoubleConverter::optArg(1, &dist2Threshold, info) ||
				FF::BoolConverter::optArg(2, &detectShadows, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::IntConverter::optProp(&history, "history", opts) ||
				FF::DoubleConverter::optProp(&dist2Threshold, "dist2Threshold", opts) ||
				FF::BoolConverter::optProp(&detectShadows, "detectShadows", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};
};

#endif