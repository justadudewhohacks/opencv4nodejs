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
        FF::StringConverter::optArg(1, &name, info)
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
    std::vector<std::string> outBlobNames;
    std::vector<cv::Mat> outputBlobs;

    cv::Mat returnValue;

    std::string executeCatchCvExceptionWorker() {
      if (outBlobNames.size() > 0) {
        std::vector<cv::String> strings(
            outBlobNames.begin(),
            outBlobNames.end());
        self.forward(outputBlobs, strings);
      } else {
        returnValue = self.forward(outputName);
      }
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      if (outBlobNames.size() > 0) {
        return Mat::ArrayConverter::wrap(outputBlobs);
      }

      return Mat::Converter::wrap(returnValue);
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
      if (info[0]->IsArray()) {
        return FF::StringArrayConverter::optArg(0, &outBlobNames, info);
      }
#endif
      return (
        FF::StringConverter::optArg(0, &outputName, info)
      );
    }
  };

  struct GetLayerNamesWorker : public CatchCvExceptionWorker {
  public:
    cv::dnn::Net self;
    GetLayerNamesWorker(cv::dnn::Net self) {
      this->self = self;
    }

    std::vector<std::string> returnValue;

    std::string executeCatchCvExceptionWorker() {
      std::vector<cv::String> layerNames = self.getLayerNames();
      std::vector<std::string> strings(
        layerNames.begin(),
        layerNames.end());
      returnValue = strings;
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return FF::StringArrayConverter::wrap(returnValue);
    }
  };

  struct GetUnconnectedOutLayersWorker : public CatchCvExceptionWorker {
  public:
    cv::dnn::Net self;
    GetUnconnectedOutLayersWorker(cv::dnn::Net self) {
      this->self = self;
    }

    std::vector<int> layerIndexes;

    std::string executeCatchCvExceptionWorker() {
      layerIndexes = self.getUnconnectedOutLayers();
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return FF::IntArrayConverter::wrap(layerIndexes);
    }
  };

}

#endif
