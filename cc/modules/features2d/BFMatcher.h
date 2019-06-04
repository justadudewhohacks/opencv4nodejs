#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include "KeyPoint.h"
#include "Mat.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_BFMATCHER_H__
#define __FF_BFMATCHER_H__

class BFMatcher : public FF::ObjectWrap<BFMatcher, cv::BFMatcher> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "BFMatcher";
	}

	int normType;
	bool crossCheck;

	FF_GETTER_CUSTOM(normType, FF::IntConverter, normType);
	FF_GETTER_CUSTOM(crossCheck, FF::BoolConverter, crossCheck);

	static NAN_MODULE_INIT(Init);

    static NAN_METHOD(New);
    static NAN_METHOD(match);
    static NAN_METHOD(matchAsync);
    static NAN_METHOD(knnMatch);
    static NAN_METHOD(knnMatchAsync);

	struct NewWorker : CatchCvExceptionWorker {
	public:
		int normType = cv::NORM_L2;
		bool crossCheck = false;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::IntConverter::optArg(0, &normType, info) ||
				FF::BoolConverter::optArg(1, &crossCheck, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::IntConverter::optProp(&normType, "history", opts) ||
				FF::BoolConverter::optProp(&crossCheck, "crossCheck", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};
};

#endif
