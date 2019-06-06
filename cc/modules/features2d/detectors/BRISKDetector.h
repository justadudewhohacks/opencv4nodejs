#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_BRISKDETECTOR_H__
#define __FF_BRISKDETECTOR_H__


class BRISKDetector : public FeatureDetector, public FF::ObjectWrapTemplate<BRISKDetector, cv::Ptr<cv::BRISK>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "BRISKDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return self;
	}

	int thresh;
	int octaves;
	double patternScale;

	FF_GETTER_CUSTOM(thresh, FF::IntConverter, thresh);
	FF_GETTER_CUSTOM(octaves, FF::IntConverter, octaves);
	FF_GETTER_CUSTOM(patternScale, FF::DoubleConverter, patternScale);

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	struct NewWorker : CatchCvExceptionWorker {
	public:
		int thresh = 30;
		int octaves = 3;
		double patternScale = 1.0;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::IntConverter::optArg(0, &thresh, info) ||
				FF::IntConverter::optArg(1, &octaves, info) ||
				FF::DoubleConverter::optArg(2, &patternScale, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::IntConverter::optProp(&thresh, "thresh", opts) ||
				FF::IntConverter::optProp(&octaves, "octaves", opts) ||
				FF::DoubleConverter::optProp(&patternScale, "patternScale", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};
};

#endif