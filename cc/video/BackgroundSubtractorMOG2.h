#include "macros.h"
#include "BackgroundSubtractor.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_BACKGROUNDSUBTRACTORMOG2_H__
#define __FF_BACKGROUNDSUBTRACTORMOG2_H__
class BackgroundSubtractorMOG2 : public BackgroundSubtractor, public FF::ObjectWrapTemplate<BackgroundSubtractorMOG2, cv::Ptr<cv::BackgroundSubtractorMOG2>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "BackgroundSubtractorMOG2";
	}

	cv::Ptr<cv::BackgroundSubtractor> getSubtractor() {
		return self;
	}

	FF_GETTER_CUSTOM(history, FF::IntConverter, self->getHistory());
	FF_GETTER_CUSTOM(varThreshold, FF::DoubleConverter, self->getVarThreshold());
	FF_GETTER_CUSTOM(detectShadows, FF::BoolConverter, self->getDetectShadows());

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	struct NewWorker : CatchCvExceptionWorker {
	public:

		uint history = 500;
		double varThreshold = 16;
		bool detectShadows = true;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::UintConverter::optArg(0, &history, info) ||
				FF::DoubleConverter::optArg(1, &varThreshold, info) ||
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
				FF::DoubleConverter::optProp(&varThreshold, "varThreshold", opts) ||
				FF::BoolConverter::optProp(&detectShadows, "detectShadows", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};
};

#endif