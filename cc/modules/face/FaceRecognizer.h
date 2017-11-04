#include "Converters.h"
#include "Workers.h"
#include "Mat.h"
#include <opencv2/face.hpp>

#ifndef __FF_FACERECOGNIZER_H__
#define __FF_FACERECOGNIZER_H__

class FaceRecognizer : public Nan::ObjectWrap {
public:
	virtual cv::Ptr<cv::face::FaceRecognizer> getFaceRecognizer() = 0;
	virtual void save(std::string) = 0;
	virtual void load(std::string) = 0;

	static void Init(v8::Local<v8::FunctionTemplate>);

	struct TrainWorker;
	static NAN_METHOD(Train);
	static NAN_METHOD(TrainAsync);

	struct PredictWorker;
	static NAN_METHOD(Predict);
	static NAN_METHOD(PredictAsync);

	static NAN_METHOD(Save);
	static NAN_METHOD(Load);

	struct NewWorker : public SimpleWorker {
	public:
		int num_components = 0;
		double threshold = DBL_MAX;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				IntConverter::optArg(0, &num_components, info) ||
				DoubleConverter::optArg(1, &threshold, info)
			);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF_ARG_IS_OBJECT(0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject();
			return (
				IntConverter::optProp(&num_components, "num_components", opts) ||
				DoubleConverter::optProp(&threshold, "threshold", opts)
			);
		}
	};
};

#endif