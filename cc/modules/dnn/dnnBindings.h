#include "dnn.h"

#ifndef __FF_DNNBINDINGS_H_
#define __FF_DNNBINDINGS_H_

namespace DnnBindings {

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
  struct ReadNetFromDarknetWorker : public CatchCvExceptionWorker{
  public:
    std::string cfgFile;
    std::string darknetModelFile = "";

    cv::dnn::Net net;

    std::string executeCatchCvExceptionWorker() {
      net = cv::dnn::readNetFromDarknet(cfgFile, darknetModelFile);
      if (net.empty()) {
        return std::string("failed to cfgFile: " + cfgFile + ", darknetModelFile: " + darknetModelFile).data();
      }
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Net::Converter::wrap(net);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
          FF::StringConverter::arg(0, &cfgFile, info));
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
          FF::StringConverter::optArg(1, &darknetModelFile, info));
    }
  };
#endif

  struct ReadNetFromTensorflowWorker : public CatchCvExceptionWorker {
  public:
    std::string modelFile;
    std::string configFile = "";

    cv::dnn::Net net;

    std::string executeCatchCvExceptionWorker() {
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
      net = cv::dnn::readNetFromTensorflow(modelFile, configFile);
#else
      net = cv::dnn::readNetFromTensorflow(modelFile);
#endif
      if (net.empty()) {
        return std::string("failed to load net: " + modelFile + "failed to load config: " + configFile).data();
      }
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Net::Converter::wrap(net);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
          FF::StringConverter::arg(0, &modelFile, info)
      );
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
          FF::StringConverter::optArg(1, &configFile, info)
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
        FF::StringConverter::arg(0, &prototxt, info)
      );
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::StringConverter::optArg(1, &modelFile, info)
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
    bool crop = true;
    int ddepth = CV_32F;
    cv::Mat returnValue;

    std::string executeCatchCvExceptionWorker() {
#if CV_VERSION_GREATER_EQUAL(3, 4, 0) && CV_VERSION_REVISION > 2
      if (isSingleImage) {
        returnValue = cv::dnn::blobFromImage(image, scalefactor, size, mean, swapRB, crop, ddepth);
      }
      else {
        returnValue = cv::dnn::blobFromImages(images, scalefactor, size, mean, swapRB, crop, ddepth);
      }
#else
      if (isSingleImage) {
        returnValue = cv::dnn::blobFromImage(image, scalefactor, size, mean, swapRB);
      }
      else {
        returnValue = cv::dnn::blobFromImages(images, scalefactor, size, mean, swapRB);
      }
#endif
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(returnValue);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        (isSingleImage && Mat::Converter::arg(0, &image, info)) ||
        (!isSingleImage && Mat::ArrayConverter::arg(0, &images, info))
      );
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::DoubleConverter::optArg(1, &scalefactor, info) ||
        Size::Converter::optArg(2, &size, info) ||
        Vec3::Converter::optArg(3, &mean, info) ||
        FF::BoolConverter::optArg(4, &swapRB, info) ||
        FF::BoolConverter::optArg(5, &crop, info) ||
        FF::IntConverter::optArg(6, &ddepth, info)
      );
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 1);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        FF::DoubleConverter::optProp(&scalefactor, "scalefactor", opts) ||
        FF::BoolConverter::optProp(&swapRB, "swapRB", opts) ||
        Size::Converter::optProp(&size, "size", opts) ||
        Vec3::Converter::optProp(&mean, "mean", opts) ||
        FF::BoolConverter::optProp(&crop, "crop", opts) ||
        FF::IntConverter::optProp(&ddepth, "ddepth", opts)
      );
    }
  };

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
  struct NMSBoxes : public CatchCvExceptionWorker {
  public:
    std::vector<cv::Rect> bboxes;
    std::vector<float> scores;
    float score_threshold;
    float nms_threshold;
    std::vector<int> indices;

    std::string executeCatchCvExceptionWorker() {
      cv::dnn::NMSBoxes(bboxes, scores, score_threshold,
          nms_threshold, indices);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return FF::IntArrayConverter::wrap(indices);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Rect::ArrayWithCastConverter<cv::Rect>::arg(0, &bboxes, info) ||
        FF::FloatArrayConverter::arg(1, &scores, info) ||
        FF::FloatConverter::arg(2, &score_threshold, info) ||
        FF::FloatConverter::arg(3, &nms_threshold, info)
      );
    }
  };
#endif
}

#endif
