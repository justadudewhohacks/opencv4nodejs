#include "macros.h"
#include <opencv2/xfeatures2d.hpp>
#include "features2d/FeatureDetector.h"

#ifndef __FF_SIFTDETECTOR_H__
#define __FF_SIFTDETECTOR_H__

class SIFTDetector : public FeatureDetector {
public:
	cv::Ptr<cv::xfeatures2d::SIFT> detector;
	int nFeatures;
	int nOctaveLayers;
	double contrastThreshold;
	double edgeThreshold;
	double sigma;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(SIFTDetector, GetNFeatures, nFeatures);
	static FF_GETTER(SIFTDetector, GeNOctaveLayers, nOctaveLayers);
	static FF_GETTER(SIFTDetector, GetContrastThreshold, contrastThreshold);
	static FF_GETTER(SIFTDetector, GetEdgeThreshold, edgeThreshold);
	static FF_GETTER(SIFTDetector, GetSigma, sigma);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}

	struct NewWorker : CatchCvExceptionWorker {
	public:

		int nFeatures = 0;
		int nOctaveLayers = 3;
		double contrastThreshold = 0.04;
		double edgeThreshold = 10;
		double sigma = 1.6;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::IntConverter::optArg(0, &nFeatures, info) ||
				FF::IntConverter::optArg(1, &nOctaveLayers, info) ||
				FF::DoubleConverter::optArg(2, &contrastThreshold, info) ||
				FF::DoubleConverter::optArg(3, &edgeThreshold, info) ||
				FF::DoubleConverter::optArg(4, &sigma, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::IntConverter::optProp(&nFeatures, "nFeatures", opts) ||
				FF::IntConverter::optProp(&nOctaveLayers, "nOctaveLayers", opts) ||
				FF::DoubleConverter::optProp(&contrastThreshold, "contrastThreshold", opts) ||
				FF::DoubleConverter::optProp(&edgeThreshold, "edgeThreshold", opts) ||
				FF::DoubleConverter::optProp(&sigma, "sigma", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};
};

#endif