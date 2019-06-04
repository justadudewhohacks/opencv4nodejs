#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_AKAZEDETECTOR_H__
#define __FF_AKAZEDETECTOR_H__

class AKAZEDetector : public FeatureDetector, public FF::ObjectWrapTemplate<AKAZEDetector, cv::Ptr<cv::AKAZE>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "AKAZEDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return self;
	}

	FF_GETTER_CUSTOM(descriptorType, FF::IntConverter, self->getDescriptorType());
	FF_GETTER_CUSTOM(descriptorSize, FF::IntConverter, self->getDescriptorSize());
	FF_GETTER_CUSTOM(descriptorChannels, FF::IntConverter, self->getDescriptorChannels());
	FF_GETTER_CUSTOM(threshold, FF::DoubleConverter, self->getThreshold());
	FF_GETTER_CUSTOM(nOctaves, FF::IntConverter, self->getNOctaves());
	FF_GETTER_CUSTOM(nOctaveLayers, FF::IntConverter, self->getNOctaveLayers());
	FF_GETTER_CUSTOM(diffusivity, FF::IntConverter, self->getDiffusivity());

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	struct NewWorker : CatchCvExceptionWorker {
	public:
		int descriptorType = cv::AKAZE::DESCRIPTOR_MLDB;
		int descriptorSize = 0;
		int descriptorChannels = 3;
		double threshold = 0.001f;
		int nOctaves = 4;
		int nOctaveLayers = 4;
		int diffusivity = cv::KAZE::DIFF_PM_G2;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::IntConverter::optArg(0, &descriptorType, info) ||
				FF::IntConverter::optArg(1, &descriptorSize, info) ||
				FF::IntConverter::optArg(2, &descriptorChannels, info) ||
				FF::DoubleConverter::optArg(3, &threshold, info) ||
				FF::IntConverter::optArg(4, &nOctaves, info) ||
				FF::IntConverter::optArg(5, &nOctaveLayers, info) ||
				FF::IntConverter::optArg(6, &diffusivity, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::IntConverter::optProp(&descriptorType, "descriptorType", opts) ||
				FF::IntConverter::optProp(&descriptorSize, "descriptorSize", opts) ||
				FF::IntConverter::optProp(&descriptorChannels, "descriptorChannels", opts) ||
				FF::DoubleConverter::optProp(&threshold, "threshold", opts) ||
				FF::IntConverter::optProp(&nOctaves, "nOctaves", opts) ||
				FF::IntConverter::optProp(&nOctaveLayers, "nOctaveLayers", opts) ||
				FF::IntConverter::optProp(&diffusivity, "diffusivity", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};
};

#endif