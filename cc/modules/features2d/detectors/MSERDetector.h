#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_MSERDETECTOR_H__
#define __FF_MSERDETECTOR_H__

class MSERDetector : public FeatureDetector {
public:
	cv::Ptr<cv::MSER> detector;
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

	static FF_GETTER(MSERDetector, GetDelta, delta);
	static FF_GETTER(MSERDetector, GetMinArea, minArea);
	static FF_GETTER(MSERDetector, GetMaxArea, maxArea);
	static FF_GETTER(MSERDetector, GetMaxVariation, maxVariation);
	static FF_GETTER(MSERDetector, GetMinDiversity, minDiversity);
	static FF_GETTER(MSERDetector, GetMaxEvolution, maxEvolution);
	static FF_GETTER(MSERDetector, GetAreaThreshold, areaThreshold);
	static FF_GETTER(MSERDetector, GetMinMargin, minMargin);
	static FF_GETTER(MSERDetector, GetEdgeBlurSize, edgeBlurSize);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  
    cv::Ptr<cv::FeatureDetector> getDetector(void){
		return detector;
    }
  
	cv::Ptr<cv::MSER> getMSERDetector() {
		return detector;
	}
    
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