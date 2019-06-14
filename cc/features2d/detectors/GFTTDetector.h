#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_GFTTDETECTOR_H__
#define __FF_GFTTDETECTOR_H__

class GFTTDetector : public FeatureDetector, public FF::ObjectWrapTemplate<GFTTDetector, cv::Ptr<cv::GFTTDetector>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "GFTTDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return self;
	}

	FF_GETTER_CUSTOM(maxFeatures, FF::IntConverter, self->getMaxFeatures());
	FF_GETTER_CUSTOM(qualityLevel, FF::DoubleConverter, self->getQualityLevel());
	FF_GETTER_CUSTOM(minDistance, FF::DoubleConverter, self->getMinDistance());
	FF_GETTER_CUSTOM(blockSize, FF::IntConverter, self->getBlockSize());
	FF_GETTER_CUSTOM(harrisDetector, FF::BoolConverter, self->getHarrisDetector());
	FF_GETTER_CUSTOM(k, FF::DoubleConverter, self->getK());

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	struct NewWorker : CatchCvExceptionWorker {
	public:
		int maxFeatures = 1000;
		double qualityLevel = 0.01;
		double minDistance = 1;
		int blockSize = 3;
		bool harrisDetector = false;
		double k = 0.04;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::IntConverter::optArg(0, &maxFeatures, info) ||
				FF::DoubleConverter::optArg(1, &qualityLevel, info) ||
				FF::DoubleConverter::optArg(2, &minDistance, info) ||
				FF::IntConverter::optArg(3, &blockSize, info) ||
				FF::BoolConverter::optArg(4, &harrisDetector, info) ||
				FF::DoubleConverter::optArg(5, &k, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::IntConverter::optProp(&maxFeatures, "maxFeatures", opts) ||
				FF::DoubleConverter::optProp(&qualityLevel, "qualityLevel", opts) ||
				FF::DoubleConverter::optProp(&minDistance, "minDistance", opts) ||
				FF::IntConverter::optProp(&blockSize, "blockSize", opts) ||
				FF::BoolConverter::optProp(&harrisDetector, "harrisDetector", opts) ||
				FF::DoubleConverter::optProp(&k, "k", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};
};

#endif