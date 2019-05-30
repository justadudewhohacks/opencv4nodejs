#include "VideoCapture.h"

#ifndef __FF_VIDEOCAPTUREBINDINGS_H_
#define __FF_VIDEOCAPTUREBINDINGS_H_

namespace VideoCaptureBindings {

	struct GetWorker : public CatchCvExceptionWorker {
	public:
		cv::VideoCapture self;
		GetWorker(cv::VideoCapture self) {
			this->self = self;
		}
		int prop;
		double val;

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
          FF::IntConverter::arg(0, &prop, info)
      );
    }

		std::string executeCatchCvExceptionWorker() {
			val = self.get(prop);
			return "";
		}

		v8::Local<v8::Value> getReturnValue() {
			return FF::DoubleConverter::wrap(val);
		}
	};

  struct ReadWorker : public CatchCvExceptionWorker {
  public:
    cv::VideoCapture self;
    ReadWorker(cv::VideoCapture self) {
      this->self = self;
    }
    cv::Mat frame;

    std::string executeCatchCvExceptionWorker() {
      self.read(frame);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(frame);
    }
  };

  struct SetWorker : public CatchCvExceptionWorker {
  public:
    cv::VideoCapture self;
    SetWorker(cv::VideoCapture self) {
      this->self = self;
    }

    // required fn args
    int prop;
    double value;
    bool ret;

    std::string executeCatchCvExceptionWorker() {
      ret = this->self.set(prop, value);
      return "";
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
          FF::IntConverter::arg(0, &prop, info) ||
          FF::DoubleConverter::arg(1, &value, info)
      );
    }

    v8::Local<v8::Value> getReturnValue() {
      return Nan::New(ret);
    }
  };


}

#endif