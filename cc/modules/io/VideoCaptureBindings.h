#include "VideoCapture.h"

#ifndef __FF_VIDEOCAPTUREBINDINGS_H_
#define __FF_VIDEOCAPTUREBINDINGS_H_

namespace VideoCaptureBindings {

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
  
    FF_VAL getReturnValue() {
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
          IntConverter::arg(0, &prop, info) ||
          DoubleConverter::arg(1, &value, info)
      );
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return Nan::New(ret);
    }
  };
  

}

#endif