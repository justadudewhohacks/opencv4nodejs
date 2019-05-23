#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_AGASTDETECTOR_H__
#define __FF_AGASTDETECTOR_H__

class AGASTDetector : public FeatureDetector {
public:
	cv::Ptr<cv::AgastFeatureDetector> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(AGASTDetector, GetThreshold, detector->getThreshold());
	static FF_GETTER(AGASTDetector, GetNonmaxSuppression, detector->getNonmaxSuppression());
	static FF_GETTER(AGASTDetector, GetType, detector->getType());

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}

	struct NewWorker : CatchCvExceptionWorker {
	public:
		int threshold = 10;
		bool nonmaxSuppression = true;
		int type = cv::AgastFeatureDetector::OAST_9_16;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				IntConverter::optArg(0, &threshold, info) ||
				BoolConverter::optArg(1, &nonmaxSuppression, info) ||
				IntConverter::optArg(2, &type, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				IntConverter::optProp(&threshold, "threshold", opts) ||
				BoolConverter::optProp(&nonmaxSuppression, "nonmaxSuppression", opts) ||
				IntConverter::optProp(&type, "type", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};
};

#endif