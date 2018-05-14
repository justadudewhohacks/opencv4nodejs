#include "HOGDescriptor.h"

#ifndef __FF_HOGDESCRIPTORBINDINGS_H_
#define __FF_HOGDESCRIPTORBINDINGS_H_

namespace HOGDescriptorBindings {

  struct ComputeWorker : CatchCvExceptionWorker  {
  public:
    cv::HOGDescriptor hog;
  
    ComputeWorker(cv::HOGDescriptor hog) {
      this->hog = hog;
    }
  
    cv::Mat img;
    cv::Size2d winStride;
    cv::Size2d padding;
    std::vector<cv::Point2i> locations;
  
    std::vector<float> descriptors;
  
    std::string executeCatchCvExceptionWorker() {
      hog.compute(img, descriptors, winStride, padding, locations);
      return "";
    }
  
    FF_VAL getReturnValue() {
      return FloatArrayConverter::wrap(descriptors);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return Mat::Converter::arg(0, &img, info);
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Size::Converter::optArg(1, &winStride, info) ||
        Size::Converter::optArg(2, &padding, info) ||
        ObjectArrayConverter<Point2, cv::Point2d, cv::Point2i>::optArg(3, &locations, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(1) && !FF_IS_INSTANCE(Size::constructor, info[1]->ToObject());
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      FF_OBJ opts = info[1]->ToObject();
      return (
        Size::Converter::optProp(&winStride, "winStride", opts) ||
        Size::Converter::optProp(&padding, "padding", opts) ||
        ObjectArrayConverter<Point2, cv::Point2d, cv::Point2i>::optProp(&locations, "locations", opts)
      );
    }
  };
  
  struct ComputeGradientWorker : public CatchCvExceptionWorker {
  public:
    cv::HOGDescriptor self;
    ComputeGradientWorker(cv::HOGDescriptor self) {
      this->self = self;
    }
  
    cv::Mat img;
    cv::Size2d paddingTL = cv::Size2d();
    cv::Size2d paddingBR = cv::Size2d();
  
    cv::Mat grad;
    cv::Mat angleOfs;
  
    std::string executeCatchCvExceptionWorker() {
      self.computeGradient(img, grad, angleOfs, paddingTL, paddingBR);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("grad").ToLocalChecked(), Mat::Converter::wrap(grad));
      Nan::Set(ret, Nan::New("angleOfs").ToLocalChecked(), Mat::Converter::wrap(angleOfs));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &img, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Size::Converter::optArg(1, &paddingTL, info) ||
        Size::Converter::optArg(2, &paddingBR, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(1);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject();
      return (
        Size::Converter::optProp(&paddingTL, "paddingTL", opts) ||
        Size::Converter::optProp(&paddingBR, "paddingBR", opts)
        );
    }
  };
  
  struct DetectWorker : public CatchCvExceptionWorker {
  public:
    cv::HOGDescriptor self;
    DetectWorker(cv::HOGDescriptor self) {
      this->self = self;
    }
  
    cv::Mat img;
    double hitThreshold = 0;
    cv::Size2d winStride = cv::Size2d();
    cv::Size2d padding = cv::Size2d();
    std::vector<cv::Point> searchLocations;
  
    std::vector<cv::Point> foundLocations;
    std::vector<double> weights;
  
    std::string executeCatchCvExceptionWorker() {
      self.detect(img, foundLocations, weights, hitThreshold, winStride, padding, searchLocations);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("foundLocations").ToLocalChecked(), ObjectArrayConverter<Point2, cv::Point2d, cv::Point>::wrap(foundLocations));
      Nan::Set(ret, Nan::New("weights").ToLocalChecked(), DoubleArrayConverter::wrap(weights));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &img, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(1, &hitThreshold, info) ||
        Size::Converter::optArg(2, &winStride, info) ||
        Size::Converter::optArg(3, &padding, info) ||
        ObjectArrayConverter<Point2, cv::Point2d, cv::Point>::optArg(4, &searchLocations, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(1);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject();
      return (
        DoubleConverter::optProp(&hitThreshold, "hitThreshold", opts) ||
        Size::Converter::optProp(&winStride, "winStride", opts) ||
        Size::Converter::optProp(&padding, "padding", opts) ||
        ObjectArrayConverter<Point2, cv::Point2d, cv::Point>::optProp(&searchLocations, "searchLocations", opts)
      );
    }
  };
  
  struct DetectROIWorker : public CatchCvExceptionWorker {
  public:
    cv::HOGDescriptor self;
    DetectROIWorker(cv::HOGDescriptor self) {
      this->self = self;
    }
  
    cv::Mat img;
    std::vector<cv::Point> locations;
    double hitThreshold = 0;
    cv::Size2d winStride = cv::Size2d();
    cv::Size2d padding = cv::Size2d();
  
    std::vector<cv::Point> foundLocations;
    std::vector<double> confidences;
  
    std::string executeCatchCvExceptionWorker() {
      self.detectROI(img, locations, foundLocations, confidences, hitThreshold, winStride, padding);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("foundLocations").ToLocalChecked(), ObjectArrayConverter<Point2, cv::Point2d, cv::Point>::wrap(foundLocations));
      Nan::Set(ret, Nan::New("confidences").ToLocalChecked(), DoubleArrayConverter::wrap(confidences));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &img, info) ||
        ObjectArrayConverter<Point2, cv::Point2d, cv::Point>::arg(1, &locations, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(2, &hitThreshold, info) ||
        Size::Converter::optArg(3, &winStride, info) ||
        Size::Converter::optArg(4, &padding, info)
        );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(2);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[2]->ToObject();
      return (
        DoubleConverter::optProp(&hitThreshold, "hitThreshold", opts) ||
        Size::Converter::optProp(&winStride, "winStride", opts) ||
        Size::Converter::optProp(&padding, "padding", opts)
      );
    }
  };
  
  struct DetectMultiScaleWorker : public CatchCvExceptionWorker {
  public:
    cv::HOGDescriptor self;
    DetectMultiScaleWorker(cv::HOGDescriptor self) {
      this->self = self;
    }
  
    cv::Mat img;
    double hitThreshold = 0;
    cv::Size2d winStride = cv::Size2d();
    cv::Size2d padding = cv::Size2d();
    double scale = 1.05;
    double finalThreshold = 2.0;
    bool useMeanshiftGrouping = false;
  
    std::vector<cv::Rect> foundLocations;
    std::vector<double> foundWeights;
  
  
    std::string executeCatchCvExceptionWorker() {
      self.detectMultiScale(img, foundLocations, foundWeights, hitThreshold, winStride, padding, scale, finalThreshold, useMeanshiftGrouping);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("foundLocations").ToLocalChecked(), ObjectArrayConverter<Rect, cv::Rect2d, cv::Rect>::wrap(foundLocations));
      Nan::Set(ret, Nan::New("foundWeights").ToLocalChecked(), DoubleArrayConverter::wrap(foundWeights));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &img, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(1, &hitThreshold, info) ||
        Size::Converter::optArg(2, &winStride, info) ||
        Size::Converter::optArg(3, &padding, info) ||
        DoubleConverter::optArg(4, &scale, info) ||
        DoubleConverter::optArg(5, &finalThreshold, info) ||
        BoolConverter::optArg(6, &useMeanshiftGrouping, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(1);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject();
      return (
        DoubleConverter::optProp(&hitThreshold, "hitThreshold", opts) ||
        Size::Converter::optProp(&winStride, "winStride", opts) ||
        Size::Converter::optProp(&padding, "padding", opts) ||
        DoubleConverter::optProp(&scale, "scale", opts) ||
        DoubleConverter::optProp(&finalThreshold, "finalThreshold", opts) ||
        BoolConverter::optProp(&useMeanshiftGrouping, "useMeanshiftGrouping", opts)
      );
    }
  };
  
  struct DetectMultiScaleROIWorker : public CatchCvExceptionWorker {
  public:
    cv::HOGDescriptor self;
    DetectMultiScaleROIWorker(cv::HOGDescriptor self) {
      this->self = self;
    }
  
    cv::Mat img;
    std::vector<cv::DetectionROI> locations;
    double hitThreshold = 0;
    int groupThreshold = 0;
  
    std::vector<cv::Rect> foundLocations;
  
    std::string executeCatchCvExceptionWorker() {
      self.detectMultiScaleROI(img, foundLocations, locations, hitThreshold, groupThreshold);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return ObjectArrayConverter<Rect, cv::Rect2d, cv::Rect>::wrap(foundLocations);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &img, info) ||
        ObjectArrayConverter<DetectionROI, cv::DetectionROI>::arg(1, &locations, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(2, &hitThreshold, info) ||
        IntConverter::optArg(3, &groupThreshold, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(2);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[2]->ToObject();
      return (
        DoubleConverter::optProp(&hitThreshold, "hitThreshold", opts) ||
        IntConverter::optProp(&groupThreshold, "groupThreshold", opts)
      );
    }
  };
  
  struct GroupRectanglesWorker : public CatchCvExceptionWorker {
  public:
    cv::HOGDescriptor self;
    GroupRectanglesWorker(cv::HOGDescriptor self) {
      this->self = self;
    }
  
    std::vector<cv::Rect> rectList;
    std::vector<double> weights;
    int groupThreshold;
    double eps;
  
  
    std::string executeCatchCvExceptionWorker() {
      self.groupRectangles(rectList, weights, groupThreshold, eps);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return ObjectArrayConverter<Rect, cv::Rect2d, cv::Rect>::wrap(rectList);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        ObjectArrayConverter<Rect, cv::Rect2d, cv::Rect>::arg(0, &rectList, info) ||
        DoubleArrayConverter::arg(1, &weights, info) ||
        IntConverter::arg(2, &groupThreshold, info) ||
        DoubleConverter::arg(3, &eps, info)
      );
    }
  };
  

}

#endif