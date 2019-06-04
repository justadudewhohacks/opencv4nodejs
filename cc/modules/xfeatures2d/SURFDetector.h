#include "macros.h"
#include <opencv2/xfeatures2d.hpp>
#include "features2d/FeatureDetector.h"

#ifndef __FF_SURFDETECTOR_H__
#define __FF_SURFDETECTOR_H__

class SURFDetector : public FeatureDetector, public FF::ObjectWrapTemplate<SURFDetector, cv::Ptr<cv::xfeatures2d::SURF>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "SURFDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector(void) {
		return self;
	}

	FF_GETTER_CUSTOM(hessianThreshold, FF::DoubleConverter, self->getHessianThreshold());
	FF_GETTER_CUSTOM(nOctaves, FF::IntConverter, self->getNOctaves());
	FF_GETTER_CUSTOM(nOctaveLayers, FF::IntConverter, self->getNOctaveLayers());
	FF_GETTER_CUSTOM(extended, FF::BoolConverter, self->getExtended());
	FF_GETTER_CUSTOM(upright, FF::BoolConverter, self->getUpright());

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	struct NewWorker : CatchCvExceptionWorker {
	public:

		double hessianThreshold = 100;
		int nOctaves = 4;
		int nOctaveLayers = 3;
		bool extended = false;
		bool upright = false;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::DoubleConverter::optArg(0, &hessianThreshold, info) ||
				FF::IntConverter::optArg(1, &nOctaves, info) ||
				FF::IntConverter::optArg(2, &nOctaveLayers, info) ||
				FF::BoolConverter::optArg(3, &extended, info) ||
				FF::BoolConverter::optArg(4, &upright, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::DoubleConverter::optProp(&hessianThreshold, "hessianThreshold", opts) ||
				FF::IntConverter::optProp(&nOctaves, "nOctaves", opts) ||
				FF::IntConverter::optProp(&nOctaveLayers, "nOctaveLayers", opts) ||
				FF::BoolConverter::optProp(&extended, "extended", opts) ||
				FF::BoolConverter::optProp(&upright, "upright", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};

};

#endif