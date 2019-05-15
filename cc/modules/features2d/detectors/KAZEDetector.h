#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_KAZEDETECTOR_H__
#define __FF_KAZEDETECTOR_H__

class KAZEDetector : public FeatureDetector {
public:
	cv::Ptr<cv::KAZE> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(KAZEDetector, GetExtended, detector->getExtended());
	static FF_GETTER(KAZEDetector, GetUpright, detector->getUpright());
	static FF_GETTER(KAZEDetector, GetThreshold, detector->getThreshold());
	static FF_GETTER(KAZEDetector, GetNOctaves, detector->getNOctaves());
	static FF_GETTER(KAZEDetector, GetNOctaveLayers, detector->getNOctaveLayers());
	static FF_GETTER(KAZEDetector, GetDiffusivity, detector->getDiffusivity());

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}

	struct NewWorker : CatchCvExceptionWorker {
	public:

		bool extended = false;
		bool upright = false;
		double threshold = 0.001f;
		int nOctaves = 4;
		int nOctaveLayers = 4;
		int diffusivity = cv::KAZE::DIFF_PM_G2;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				BoolConverter::optArg(0, &extended, info) ||
				BoolConverter::optArg(1, &upright, info) ||
				DoubleConverter::optArg(2, &threshold, info) ||
				IntConverter::optArg(3, &nOctaves, info) ||
				IntConverter::optArg(4, &nOctaveLayers, info) ||
				IntConverter::optArg(5, &diffusivity, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				BoolConverter::optProp(&extended, "extended", opts) ||
				BoolConverter::optProp(&upright, "upright", opts) ||
				DoubleConverter::optProp(&threshold, "threshold", opts) ||
				IntConverter::optProp(&nOctaves, "nOctaves", opts) ||
				IntConverter::optProp(&nOctaveLayers, "nOctaveLayers", opts) ||
				IntConverter::optProp(&diffusivity, "diffusivity", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};
};

#endif