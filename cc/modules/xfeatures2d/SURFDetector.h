#include "macros.h"
#include <opencv2/xfeatures2d.hpp>
#include "features2d/FeatureDetector.h"

#ifndef __FF_SURFDETECTOR_H__
#define __FF_SURFDETECTOR_H__

class SURFDetector : public FeatureDetector {
public:
	cv::Ptr<cv::xfeatures2d::SURF> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(SURFDetector, GetHessianThreshold, detector->getHessianThreshold());
	static FF_GETTER(SURFDetector, GetNOctaves, detector->getNOctaves());
	static FF_GETTER(SURFDetector, GetNOctaveLayers, detector->getNOctaveLayers());
	static FF_GETTER(SURFDetector, GetExtended, detector->getExtended());
	static FF_GETTER(SURFDetector, GetUpright, detector->getUpright());

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}

	struct NewWorker : CatchCvExceptionWorker {
	public:

		double hessianThreshold = 100;
		int nOctaves = 4;
		int nOctaveLayers = 3;
		bool extended = false;
		bool upright = false;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				DoubleConverter::optArg(0, &hessianThreshold, info) ||
				IntConverter::optArg(1, &nOctaves, info) ||
				IntConverter::optArg(2, &nOctaveLayers, info) ||
				BoolConverter::optArg(3, &extended, info) ||
				BoolConverter::optArg(4, &upright, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				DoubleConverter::optProp(&hessianThreshold, "hessianThreshold", opts) ||
				IntConverter::optProp(&nOctaves, "nOctaves", opts) ||
				IntConverter::optProp(&nOctaveLayers, "nOctaveLayers", opts) ||
				BoolConverter::optProp(&extended, "extended", opts) ||
				BoolConverter::optProp(&upright, "upright", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};

};

#endif