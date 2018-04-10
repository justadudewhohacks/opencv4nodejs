#include "dnn.h"

#ifndef __FF_DNNBINDINGS_H_
#define __FF_DNNBINDINGS_H_

namespace DnnBindings {

  struct ReadNetFromTensorflowWorker : public CatchCvExceptionWorker {
  public:
    std::string modelFile;
  
    cv::dnn::Net net;
  
    std::string executeCatchCvExceptionWorker() {
      net = cv::dnn::readNetFromTensorflow(modelFile);
      if (net.empty()) {
        return std::string("failed to load net: " + modelFile).data();
      }
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return Net::Converter::wrap(net);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        StringConverter::arg(0, &modelFile, info)
      );
    }
  };
  
  struct ReadNetFromCaffeWorker : public CatchCvExceptionWorker {
  public:
    std::string prototxt;
    std::string modelFile = "";
  
    cv::dnn::Net net;
  
    std::string executeCatchCvExceptionWorker() {
      net = cv::dnn::readNetFromCaffe(prototxt, modelFile);
      if (net.empty()) {
        return std::string("failed to prototxt: " + prototxt + ", modelFile: " + modelFile).data();
      }
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return Net::Converter::wrap(net);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        StringConverter::arg(0, &prototxt, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        StringConverter::optArg(1, &modelFile, info)
      );
    }
  };
  
  struct BlobFromImageWorker : public CatchCvExceptionWorker {
  public:
    bool isSingleImage;
    BlobFromImageWorker(bool isSingleImage = true) {
      this->isSingleImage = isSingleImage;
    }
  
    cv::Mat image;
    std::vector<cv::Mat> images;
    double scalefactor = 1.0;
    cv::Size2d size = cv::Size2d();
    cv::Vec3d mean = cv::Vec3d();
    bool swapRB = true;
  
    cv::Mat returnValue;
  
    std::string executeCatchCvExceptionWorker() {
      if (isSingleImage) {
        returnValue = cv::dnn::blobFromImage(image, scalefactor, size, mean, swapRB);
      }
      else {
        returnValue = cv::dnn::blobFromImages(images, scalefactor, size, mean, swapRB);
      }
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(returnValue);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        isSingleImage && Mat::Converter::arg(0, &image, info) ||
        !isSingleImage && ObjectArrayConverter<Mat, cv::Mat>::arg(0, &images, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(1, &scalefactor, info) ||
        Size::Converter::optArg(2, &size, info) ||
        Vec3::Converter::optArg(3, &mean, info) ||
        BoolConverter::optArg(4, &swapRB, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(1);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject();
      return (
        DoubleConverter::optProp(&scalefactor, "scalefactor", opts) ||
        BoolConverter::optProp(&swapRB, "swapRB", opts) ||
        Size::Converter::optProp(&size, "size", opts) ||
        Vec3::Converter::optProp(&mean, "mean", opts)
      );
    }
  };
  

}

#endif