#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include "KeyPoint.h"
#include "Mat.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_BFMATCHER_H__
#define __FF_BFMATCHER_H__

class BFMatcher : public Nan::ObjectWrap {
public:
    cv::BFMatcher bfmatcher;

	int normType;
	bool crossCheck;

	static FF_GETTER(BFMatcher, GetNormType, normType)
	static FF_GETTER(BFMatcher, GetCrossCheck, crossCheck)

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::BFMatcher* getNativeObjectPtr() { return &bfmatcher; }
	cv::BFMatcher getNativeObject() { return bfmatcher; }

	typedef InstanceConverter<BFMatcher, cv::BFMatcher> Converter;

	static NAN_MODULE_INIT(Init);

    static NAN_METHOD(New);
    static NAN_METHOD(match);
    static NAN_METHOD(matchAsync);
    static NAN_METHOD(knnMatch);
    static NAN_METHOD(knnMatchAsync);

    static const char* getClassName() {
        return "BFMatcher";
    }



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
