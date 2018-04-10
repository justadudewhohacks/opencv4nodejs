#include "FaceRecognizer.h"

#ifndef __FF_FACERECOGNIZERBINDINGS_H_
#define __FF_FACERECOGNIZERBINDINGS_H_

namespace FaceRecognizerBindings {
	struct NewWorker : public FF::SimpleWorker {
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

  struct TrainWorker : public CatchCvExceptionWorker {
  public:
    cv::Ptr<cv::face::FaceRecognizer> self;
    TrainWorker(cv::Ptr<cv::face::FaceRecognizer> self) {
      this->self = self;
    }
  
    std::vector<cv::Mat> images;
    std::vector<int> labels;
  
    std::string executeCatchCvExceptionWorker() {
      self->train(images, labels);
      return "";
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        ObjectArrayConverter<Mat, cv::Mat>::arg(0, &images, info) ||
        IntArrayConverter::arg(1, &labels, info)
      );
    }
  };
  
  struct PredictWorker : public CatchCvExceptionWorker {
  public:
    cv::Ptr<cv::face::FaceRecognizer> self;
    PredictWorker(cv::Ptr<cv::face::FaceRecognizer> self) {
      this->self = self;
    }
  
    cv::Mat image;
    int label;
    double confidence;
  
    std::string executeCatchCvExceptionWorker() {
      self->predict(image, label, confidence);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("label").ToLocalChecked(), Nan::New(label));
      Nan::Set(ret, Nan::New("confidence").ToLocalChecked(), Nan::New(confidence));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &image, info)
      );
    }
  };
  

}

#endif