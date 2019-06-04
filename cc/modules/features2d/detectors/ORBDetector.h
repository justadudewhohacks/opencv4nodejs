#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_ORBDETECTOR_H__
#define __FF_ORBDETECTOR_H__


class ORBDetector : public FeatureDetector, public FF::ObjectWrapTemplate<ORBDetector, cv::Ptr<cv::ORB>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "ORBDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return self;
	}

	FF_GETTER_CUSTOM(maxFeatures, FF::IntConverter, self->getMaxFeatures());
	FF_GETTER_CUSTOM(scaleFactor, FF::FloatConverter, self->getScaleFactor());
	FF_GETTER_CUSTOM(nLevels, FF::IntConverter, self->getNLevels());
	FF_GETTER_CUSTOM(edgeThreshold, FF::IntConverter, self->getEdgeThreshold());
	FF_GETTER_CUSTOM(firstLevel, FF::IntConverter, self->getFirstLevel());
	FF_GETTER_CUSTOM(WTA_K, FF::IntConverter, self->getWTA_K());
	FF_GETTER_CUSTOM(scoreType, FF::IntConverter, self->getScoreType());
	FF_GETTER_CUSTOM(patchSize, FF::IntConverter, self->getPatchSize());
	FF_GETTER_CUSTOM(fastThreshold, FF::IntConverter, self->getFastThreshold());

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	struct NewWorker : CatchCvExceptionWorker {
	public:
		int maxFeatures = 500;
		double scaleFactor = 1.2f;
		int nLevels = 8;
		int edgeThreshold = 31;
		int firstLevel = 0;
		int WTA_K = 2;
		int scoreType = cv::ORB::HARRIS_SCORE;
		int patchSize = 31;
		int fastThreshold = 20;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::IntConverter::optArg(0, &maxFeatures, info) ||
				FF::DoubleConverter::optArg(1, &scaleFactor, info) ||
				FF::IntConverter::optArg(2, &nLevels, info) ||
				FF::IntConverter::optArg(3, &edgeThreshold, info) ||
				FF::IntConverter::optArg(4, &firstLevel, info) ||
				FF::IntConverter::optArg(5, &WTA_K, info) ||
				FF::IntConverter::optArg(6, &scoreType, info) ||
				FF::IntConverter::optArg(7, &patchSize, info) ||
				FF::IntConverter::optArg(8, &fastThreshold, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::IntConverter::optProp(&maxFeatures, "maxFeatures", opts) ||
				FF::DoubleConverter::optProp(&scaleFactor, "scaleFactor", opts) ||
				FF::IntConverter::optProp(&nLevels, "nLevels", opts) ||
				FF::IntConverter::optProp(&edgeThreshold, "edgeThreshold", opts) ||
				FF::IntConverter::optProp(&firstLevel, "firstLevel", opts) ||
				FF::IntConverter::optProp(&WTA_K, "WTA_K", opts) ||
				FF::IntConverter::optProp(&scoreType, "scoreType", opts) ||
				FF::IntConverter::optProp(&patchSize, "patchSize", opts) ||
				FF::IntConverter::optProp(&fastThreshold, "fastThreshold", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};

};

#endif