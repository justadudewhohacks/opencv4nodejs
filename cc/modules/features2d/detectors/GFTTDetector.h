#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_GFTTDETECTOR_H__
#define __FF_GFTTDETECTOR_H__

class GFTTDetector : public FeatureDetector {
public:
	cv::Ptr<cv::GFTTDetector> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(GFTTDetector, GetMaxFeatures, detector->getMaxFeatures());
	static FF_GETTER(GFTTDetector, GetQualityLevel, detector->getQualityLevel());
	static FF_GETTER(GFTTDetector, GetMinDistance, detector->getMinDistance());
	static FF_GETTER(GFTTDetector, GetBlockSize, detector->getBlockSize());
	static FF_GETTER(GFTTDetector, GetUseHarrisDetector, detector->getHarrisDetector());
	static FF_GETTER(GFTTDetector, GetK, detector->getK());

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}


	struct NewWorker : CatchCvExceptionWorker {
	public:
		int maxCorners = 1000;
		double qualityLevel = 0.01;
		double minDistance = 1;
		int blockSize = 3;
		bool useHarrisDetector = false;
		double k = 0.04;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				IntConverter::optArg(0, &maxCorners, info) ||
				DoubleConverter::optArg(1, &qualityLevel, info) ||
				DoubleConverter::optArg(2, &minDistance, info) ||
				IntConverter::optArg(3, &blockSize, info) ||
				BoolConverter::optArg(4, &useHarrisDetector, info) ||
				DoubleConverter::optArg(5, &k, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				IntConverter::optProp(&maxCorners, "maxCorners", opts) ||
				DoubleConverter::optProp(&qualityLevel, "qualityLevel", opts) ||
				DoubleConverter::optProp(&minDistance, "minDistance", opts) ||
				IntConverter::optProp(&blockSize, "blockSize", opts) ||
				BoolConverter::optProp(&useHarrisDetector, "useHarrisDetector", opts) ||
				DoubleConverter::optProp(&k, "k", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};
};

#endif