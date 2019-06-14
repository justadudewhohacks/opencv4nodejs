#include "FeatureDetector.h"

#ifndef __FF_FEATUREDETECTORBINDINGS_H_
#define __FF_FEATUREDETECTORBINDINGS_H_

namespace FeatureDetectorBindings {

  struct DetectWorker : public CatchCvExceptionWorker {
  public:
    cv::Ptr<cv::FeatureDetector> det;
    DetectWorker(cv::Ptr<cv::FeatureDetector> _det) {
      this->det = _det;
    }
  
    cv::Mat img;
    std::vector<cv::KeyPoint> kps;
  
    std::string executeCatchCvExceptionWorker() {
      det->detect(img, kps);
      return "";
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return Mat::Converter::arg(0, &img, info);
    }
  
  
    v8::Local<v8::Value> getReturnValue() {
      return KeyPoint::ArrayConverter::wrap(kps);
    }
  };
  
  struct ComputeWorker : public CatchCvExceptionWorker {
  public:
    cv::Ptr<cv::FeatureDetector> det;
    ComputeWorker(cv::Ptr<cv::FeatureDetector> _det) {
      this->det = _det;
    }
  
    cv::Mat img;
    std::vector<cv::KeyPoint> kps;
    cv::Mat desc;
  
    std::string executeCatchCvExceptionWorker() {
      det->compute(img, kps, desc);
      return "";
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &img, info)
        || KeyPoint::ArrayConverter::arg(1, &kps, info)
      );
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(desc);
    }
  };
  

}

#endif