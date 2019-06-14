#include "macros.h"
#include "BackgroundSubtractor.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_BACKGROUNDSUBTRACTORKNN_H__
#define __FF_BACKGROUNDSUBTRACTORKNN_H__

class BackgroundSubtractorKNN : public BackgroundSubtractor, public FF::ObjectWrapTemplate<BackgroundSubtractorKNN, cv::Ptr<cv::BackgroundSubtractorKNN>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "BackgroundSubtractorKNN";
	}

	cv::Ptr<cv::BackgroundSubtractor> getSubtractor() {
		return self;
	}

	FF_GETTER_CUSTOM(history, FF::IntConverter, self->getHistory());
	FF_GETTER_CUSTOM(dist2Threshold, FF::DoubleConverter, self->getDist2Threshold());
	FF_GETTER_CUSTOM(detectShadows, FF::BoolConverter, self->getDetectShadows());

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	struct NewWorker : CatchCvExceptionWorker {
	public:

		uint history = 500;
		double dist2Threshold = 400;
		bool detectShadows = true;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::UintConverter::optArg(0, &history, info) ||
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
				FF::UintConverter::optProp(&history, "history", opts) ||
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