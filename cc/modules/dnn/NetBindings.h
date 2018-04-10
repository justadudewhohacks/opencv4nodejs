#include "Net.h"

#ifndef __FF_NETBINDINGS_H_
#define __FF_NETBINDINGS_H_

namespace NetBindings {

  struct SetInputWorker : public CatchCvExceptionWorker {
  public:
    cv::dnn::Net self;
    SetInputWorker(cv::dnn::Net self) {
      this->self = self;
    }
  
    cv::Mat blob;
    std::string name = "";
  
  
    std::string executeCatchCvExceptionWorker() {
      self.setInput(blob, name);
      return "";
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &blob, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        StringConverter::optArg(1, &name, info)
      );
    }
  };
  
  struct ForwardWorker : public CatchCvExceptionWorker {
  public:
    cv::dnn::Net self;
    ForwardWorker(cv::dnn::Net self) {
      this->self = self;
    }
  
    std::string outputName = "";
  
    cv::Mat returnValue;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = self.forward(outputName);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(returnValue);
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        StringConverter::optArg(0, &outputName, info)
      );
    }
  };
  

}

#endif