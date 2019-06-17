#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_MSERDETECTOR_H__
#define __FF_MSERDETECTOR_H__

class MSERDetector : public FeatureDetector, public FF::ObjectWrapTemplate<MSERDetector, cv::Ptr<cv::MSER>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "MSERDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector(void) {
		return self;
	}

	cv::Ptr<cv::MSER> getMSERDetector() {
		return self;
	}

	int delta ;
	int minArea;
	int maxArea;
	double maxVariation;
	double minDiversity;
	int maxEvolution;
	double areaThreshold;
	double minMargin;
	int edgeBlurSize;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	FF_GETTER_CUSTOM(delta, FF::IntConverter, delta);
	FF_GETTER_CUSTOM(minArea, FF::IntConverter, minArea);
	FF_GETTER_CUSTOM(maxArea, FF::IntConverter, maxArea);
	FF_GETTER_CUSTOM(maxVariation, FF::DoubleConverter, maxVariation);
	FF_GETTER_CUSTOM(minDiversity, FF::DoubleConverter, minDiversity);
	FF_GETTER_CUSTOM(maxEvolution, FF::IntConverter, maxEvolution);
	FF_GETTER_CUSTOM(areaThreshold, FF::DoubleConverter, areaThreshold);
	FF_GETTER_CUSTOM(minMargin, FF::DoubleConverter, minMargin);
	FF_GETTER_CUSTOM(edgeBlurSize, FF::IntConverter, edgeBlurSize);

    static NAN_METHOD(DetectRegions);
	static NAN_METHOD(DetectRegionsAsync);


	struct NewWorker : CatchCvExceptionWorker {
	public:
		int delta = 5;
		int minArea = 60;
		int maxArea = 14400;
		double maxVariation = 0.25;
		double minDiversity = 0.2;
		int maxEvolution = 200;
		double areaThreshold = 1.01;
		double minMargin = 0.003;
		int edgeBlurSize = 5;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::IntConverter::optArg(0, &delta, info) ||
				FF::IntConverter::optArg(1, &minArea, info) ||
				FF::IntConverter::optArg(2, &maxArea, info) ||
				FF::DoubleConverter::optArg(3, &maxVariation, info) ||
				FF::DoubleConverter::optArg(4, &minDiversity, info) ||
				FF::IntConverter::optArg(5, &maxEvolution, info) ||
				FF::DoubleConverter::optArg(6, &areaThreshold, info) ||
				FF::DoubleConverter::optArg(7, &minMargin, info) ||
				FF::IntConverter::optArg(8, &edgeBlurSize, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::IntConverter::optProp(&delta, "delta", opts) ||
				FF::IntConverter::optProp(&minArea, "minArea", opts) ||
				FF::IntConverter::optProp(&maxArea, "maxArea", opts) ||
				FF::DoubleConverter::optProp(&maxVariation, "maxVariation", opts) ||
				FF::DoubleConverter::optProp(&minDiversity, "minDiversity", opts) ||
				FF::IntConverter::optProp(&maxEvolution, "maxEvolution", opts) ||
				FF::DoubleConverter::optProp(&areaThreshold, "areaThreshold", opts) ||
				FF::DoubleConverter::optProp(&minMargin, "minMargin", opts) ||
				FF::IntConverter::optProp(&edgeBlurSize, "edgeBlurSize", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};
};

#endif