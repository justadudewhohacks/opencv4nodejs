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
    bool crop = true;
    int ddepth = CV_32F;

    cv::Mat returnValue;

    std::string executeCatchCvExceptionWorker() {
      if (isSingleImage) {
        returnValue = cv::dnn::blobFromImage(image, scalefactor, size, mean, swapRB, crop, ddepth);
      }
      else {
        returnValue = cv::dnn::blobFromImages(images, scalefactor, size, mean, swapRB, crop, ddepth);
      }
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(returnValue);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        (isSingleImage && Mat::Converter::arg(0, &image, info)) ||
        (!isSingleImage && ObjectArrayConverter<Mat, cv::Mat>::arg(0, &images, info))
      );
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(1, &scalefactor, info) ||
        Size::Converter::optArg(2, &size, info) ||
        Vec3::Converter::optArg(3, &mean, info) ||
        BoolConverter::optArg(4, &swapRB, info) ||
        BoolConverter::optArg(5, &crop, info) ||
        IntConverter::optArg(6, &ddepth, info)
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
        Vec3::Converter::optProp(&mean, "mean", opts) ||
        BoolConverter::optProp(&crop, "crop", opts) ||
        IntConverter::optProp(&ddepth, "ddepth", opts)
      );
    }
  };

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
      return IntArrayConverter::wrap(indices);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        ObjectArrayConverter<Rect, cv::Rect>::arg(0, &bboxes, info) ||
        FloatArrayConverter::arg(1, &scores, info) ||
        FloatConverter::arg(2, &score_threshold, info) ||
        FloatConverter::arg(3, &nms_threshold, info)
      );
    }
  };
}

#endif
