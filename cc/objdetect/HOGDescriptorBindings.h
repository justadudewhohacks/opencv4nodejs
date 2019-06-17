#include "HOGDescriptor.h"
#include "CvBinding.h"

#ifndef __FF_HOGDESCRIPTORBINDINGS_H_
#define __FF_HOGDESCRIPTORBINDINGS_H_

namespace HOGDescriptorBindings {
  struct ComputeWorker : CatchCvExceptionWorker  {
  public:
    std::shared_ptr<cv::HOGDescriptor> hog;

    ComputeWorker(	std::shared_ptr<cv::HOGDescriptor> hog) {
      this->hog = hog;
    }

    cv::Mat img;
    cv::Size2d winStride;
    cv::Size2d padding;
    std::vector<cv::Point2i> locations;

    std::vector<float> descriptors;

    std::string executeCatchCvExceptionWorker() {
      hog->compute(img, descriptors, winStride, padding, locations);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return FF::FloatArrayConverter::wrap(descriptors);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return Mat::Converter::arg(0, &img, info);
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Size::Converter::optArg(1, &winStride, info) ||
        Size::Converter::optArg(2, &padding, info) ||
        Point2::ArrayWithCastConverter<cv::Point2i>::optArg(3, &locations, info)
      );
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 1) && !Size::hasInstance(info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        Size::Converter::optProp(&winStride, "winStride", opts) ||
        Size::Converter::optProp(&padding, "padding", opts) ||
        Point2::ArrayWithCastConverter<cv::Point2i>::optProp(&locations, "locations", opts)
      );
    }
  };

  struct ComputeGradientWorker : public CatchCvExceptionWorker {
  public:
    std::shared_ptr<cv::HOGDescriptor> self;

    ComputeGradientWorker(std::shared_ptr<cv::HOGDescriptor> self) {
      this->self = self;
    }

    cv::Mat img;
    cv::Size2d paddingTL = cv::Size2d();
    cv::Size2d paddingBR = cv::Size2d();

    cv::Mat grad;
    cv::Mat angleOfs;

    std::string executeCatchCvExceptionWorker() {
      self->computeGradient(img, grad, angleOfs, paddingTL, paddingBR);
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
      return FF::isArgObject(info, 1);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        Size::Converter::optProp(&paddingTL, "paddingTL", opts) ||
        Size::Converter::optProp(&paddingBR, "paddingBR", opts)
        );
    }
  };

  struct DetectWorker : public CatchCvExceptionWorker {
  public:
    std::shared_ptr<cv::HOGDescriptor> self;
    DetectWorker(std::shared_ptr<cv::HOGDescriptor> self) {
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
      self->detect(img, foundLocations, weights, hitThreshold, winStride, padding, searchLocations);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("foundLocations").ToLocalChecked(), Point2::ArrayWithCastConverter<cv::Point2i>::wrap(foundLocations));
      Nan::Set(ret, Nan::New("weights").ToLocalChecked(), FF::DoubleArrayConverter::wrap(weights));
      return ret;
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &img, info)
      );
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::DoubleConverter::optArg(1, &hitThreshold, info) ||
        Size::Converter::optArg(2, &winStride, info) ||
        Size::Converter::optArg(3, &padding, info) ||
        Point2::ArrayWithCastConverter<cv::Point2i>::optArg(4, &searchLocations, info)
      );
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 1);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        FF::DoubleConverter::optProp(&hitThreshold, "hitThreshold", opts) ||
        Size::Converter::optProp(&winStride, "winStride", opts) ||
        Size::Converter::optProp(&padding, "padding", opts) ||
        Point2::ArrayWithCastConverter<cv::Point2i>::optProp(&searchLocations, "searchLocations", opts)
      );
    }
  };

  struct DetectROIWorker : public CatchCvExceptionWorker {
  public:
    std::shared_ptr<cv::HOGDescriptor> self;
    DetectROIWorker(std::shared_ptr<cv::HOGDescriptor> self) {
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
      self->detectROI(img, locations, foundLocations, confidences, hitThreshold, winStride, padding);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("foundLocations").ToLocalChecked(), Point2::ArrayWithCastConverter<cv::Point2i>::wrap(foundLocations));
      Nan::Set(ret, Nan::New("confidences").ToLocalChecked(), FF::DoubleArrayConverter::wrap(confidences));
      return ret;
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &img, info) ||
        Point2::ArrayWithCastConverter<cv::Point2i>::arg(1, &locations, info)
      );
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::DoubleConverter::optArg(2, &hitThreshold, info) ||
        Size::Converter::optArg(3, &winStride, info) ||
        Size::Converter::optArg(4, &padding, info)
        );
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 2);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[2]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        FF::DoubleConverter::optProp(&hitThreshold, "hitThreshold", opts) ||
        Size::Converter::optProp(&winStride, "winStride", opts) ||
        Size::Converter::optProp(&padding, "padding", opts)
      );
    }
  };

  struct DetectMultiScaleWorker : public CatchCvExceptionWorker {
  public:
    std::shared_ptr<cv::HOGDescriptor> self;
    DetectMultiScaleWorker(std::shared_ptr<cv::HOGDescriptor> self) {
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
      self->detectMultiScale(img, foundLocations, foundWeights, hitThreshold, winStride, padding, scale, finalThreshold, useMeanshiftGrouping);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("foundLocations").ToLocalChecked(), Rect::ArrayWithCastConverter<cv::Rect>::wrap(foundLocations));
      Nan::Set(ret, Nan::New("foundWeights").ToLocalChecked(), FF::DoubleArrayConverter::wrap(foundWeights));
      return ret;
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &img, info)
      );
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::DoubleConverter::optArg(1, &hitThreshold, info) ||
        Size::Converter::optArg(2, &winStride, info) ||
        Size::Converter::optArg(3, &padding, info) ||
        FF::DoubleConverter::optArg(4, &scale, info) ||
        FF::DoubleConverter::optArg(5, &finalThreshold, info) ||
        FF::BoolConverter::optArg(6, &useMeanshiftGrouping, info)
      );
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 1);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        FF::DoubleConverter::optProp(&hitThreshold, "hitThreshold", opts) ||
        Size::Converter::optProp(&winStride, "winStride", opts) ||
        Size::Converter::optProp(&padding, "padding", opts) ||
        FF::DoubleConverter::optProp(&scale, "scale", opts) ||
        FF::DoubleConverter::optProp(&finalThreshold, "finalThreshold", opts) ||
        FF::BoolConverter::optProp(&useMeanshiftGrouping, "useMeanshiftGrouping", opts)
      );
    }
  };

  struct DetectMultiScaleROIWorker : public CatchCvExceptionWorker {
  public:
    std::shared_ptr<cv::HOGDescriptor> self;
    DetectMultiScaleROIWorker(std::shared_ptr<cv::HOGDescriptor> self) {
      this->self = self;
    }

    cv::Mat img;
    std::vector<cv::DetectionROI> locations;
    double hitThreshold = 0;
    int groupThreshold = 0;

    std::vector<cv::Rect> foundLocations;

    std::string executeCatchCvExceptionWorker() {
      self->detectMultiScaleROI(img, foundLocations, locations, hitThreshold, groupThreshold);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Rect::ArrayWithCastConverter<cv::Rect>::wrap(foundLocations);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &img, info) ||
        DetectionROI::ArrayConverter::arg(1, &locations, info)
      );
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::DoubleConverter::optArg(2, &hitThreshold, info) ||
        FF::IntConverter::optArg(3, &groupThreshold, info)
      );
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 2);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[2]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        FF::DoubleConverter::optProp(&hitThreshold, "hitThreshold", opts) ||
        FF::IntConverter::optProp(&groupThreshold, "groupThreshold", opts)
      );
    }
  };

  struct GroupRectanglesWorker : public CatchCvExceptionWorker {
  public:
    std::shared_ptr<cv::HOGDescriptor> self;
    GroupRectanglesWorker(std::shared_ptr<cv::HOGDescriptor> self) {
      this->self = self;
    }

    std::vector<cv::Rect> rectList;
    std::vector<double> weights;
    int groupThreshold;
    double eps;


    std::string executeCatchCvExceptionWorker() {
      self->groupRectangles(rectList, weights, groupThreshold, eps);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Rect::ArrayWithCastConverter<cv::Rect>::wrap(rectList);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Rect::ArrayWithCastConverter<cv::Rect>::arg(0, &rectList, info) ||
        FF::DoubleArrayConverter::arg(1, &weights, info) ||
        FF::IntConverter::arg(2, &groupThreshold, info) ||
        FF::DoubleConverter::arg(3, &eps, info)
      );
    }
  };


}

#endif