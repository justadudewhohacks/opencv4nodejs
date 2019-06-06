#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_AGASTDETECTOR_H__
#define __FF_AGASTDETECTOR_H__

class AGASTDetector : public FeatureDetector, public FF::ObjectWrapTemplate<AGASTDetector, cv::Ptr<cv::AgastFeatureDetector>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "AGASTDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return self;
	}

	FF_GETTER_CUSTOM(threshold, FF::DoubleConverter, self->getThreshold());
	FF_GETTER_CUSTOM(nonmaxSuppression, FF::BoolConverter, self->getNonmaxSuppression());
	FF_GETTER_CUSTOM(type, FF::IntConverter, self->getType());

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	struct NewWorker : CatchCvExceptionWorker {
	public:
		int threshold = 10;
		bool nonmaxSuppression = true;
		int type = cv::AgastFeatureDetector::OAST_9_16;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::IntConverter::optArg(0, &threshold, info) ||
				FF::BoolConverter::optArg(1, &nonmaxSuppression, info) ||
				FF::IntConverter::optArg(2, &type, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::IntConverter::optProp(&threshold, "threshold", opts) ||
				FF::BoolConverter::optProp(&nonmaxSuppression, "nonmaxSuppression", opts) ||
				FF::IntConverter::optProp(&type, "type", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};
};

#endif