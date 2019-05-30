#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_FASTDETECTOR_H__
#define __FF_FASTDETECTOR_H__

class FASTDetector : public FeatureDetector {
public:
	cv::Ptr<cv::FastFeatureDetector> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(FASTDetector, GetThreshold, detector->getThreshold());
	static FF_GETTER(FASTDetector, GetNonmaxSuppression, detector->getNonmaxSuppression());
	static FF_GETTER(FASTDetector, GetType, detector->getType());

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}

	struct NewWorker : public CatchCvExceptionWorker {
	public:

		int threshold = 10;
		bool nonmaxSuppression = true;
		int type = cv::FastFeatureDetector::TYPE_9_16;

		std::string executeCatchCvExceptionWorker() {
			return "";
		}

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
	};
};

#endif