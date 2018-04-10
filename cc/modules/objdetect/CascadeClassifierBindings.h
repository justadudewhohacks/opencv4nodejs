#include "CascadeClassifier.h"

#ifndef __FF_CASCADECLASSIFIERBINDINGS_H_
#define __FF_CASCADECLASSIFIERBINDINGS_H_

namespace CascadeClassifierBindings {

  struct DetectMultiScaleWorker : CatchCvExceptionWorker {
  public:
    cv::CascadeClassifier classifier;
    bool isGpu;
  
    DetectMultiScaleWorker(cv::CascadeClassifier classifier, bool isGpu = false) {
      this->classifier = classifier;
      this->isGpu = isGpu;
    }
  
    cv::Mat img;
    double scaleFactor = 1.1;
    uint minNeighbors = 3;
    uint flags = 0;
    cv::Size2d minSize;
    cv::Size2d maxSize;
  
    std::vector<cv::Rect> objectRects;
    std::vector<int> numDetections;
  
    std::string executeCatchCvExceptionWorker() {
      if (isGpu) {
        cv::UMat oclMat = img.getUMat(cv::ACCESS_READ);
        classifier.detectMultiScale(oclMat, objectRects, scaleFactor, (int)minNeighbors, (int)flags, minSize, maxSize);
      }
      else {
        classifier.detectMultiScale(img, objectRects, numDetections, scaleFactor, (int)minNeighbors, (int)flags, minSize, maxSize);
      }
      return "";
    }
  
    FF_VAL getReturnValue() {
      if (isGpu) {
        return ObjectArrayConverter<Rect, cv::Rect>::wrap(objectRects);
      }
      else {
        FF_OBJ ret = FF_NEW_OBJ();
        Nan::Set(ret, FF_NEW_STRING("objects"), ObjectArrayConverter<Rect, cv::Rect>::wrap(objectRects));
        Nan::Set(ret, FF_NEW_STRING("numDetections"), IntArrayConverter::wrap(numDetections));
        return ret;
      }
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return Mat::Converter::arg(0, &img, info);
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(1, &scaleFactor, info) ||
        UintConverter::optArg(2, &minNeighbors, info) ||
        UintConverter::optArg(3, &flags, info) ||
        Size::Converter::optArg(4, &minSize, info) ||
        Size::Converter::optArg(5, &maxSize, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(1);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      FF_OBJ opts = info[1]->ToObject();
      return (
        DoubleConverter::optProp(&scaleFactor, "scaleFactor", opts) ||
        UintConverter::optProp(&minNeighbors, "minNeighbors", opts) ||
        UintConverter::optProp(&flags, "flags", opts) ||
        Size::Converter::optProp(&minSize, "minSize", opts) ||
        Size::Converter::optProp(&maxSize, "maxSize", opts)
      );
    }
  };
  
  struct DetectMultiScaleWithRejectLevelsWorker : public DetectMultiScaleWorker {
  public:
    DetectMultiScaleWithRejectLevelsWorker(cv::CascadeClassifier classifier, bool isGpu = false) : DetectMultiScaleWorker(classifier, isGpu) {}
  
    std::vector<int> rejectLevels;
    std::vector<double> levelWeights;
  
    std::string executeCatchCvExceptionWorker() {
      if (isGpu) {
        cv::UMat oclMat = img.getUMat(cv::ACCESS_READ);
        classifier.detectMultiScale(oclMat, objectRects, rejectLevels, levelWeights, scaleFactor, (int)minNeighbors, (int)flags, minSize, maxSize, true);
      }
      else {
        classifier.detectMultiScale(img, objectRects, rejectLevels, levelWeights, scaleFactor, (int)minNeighbors, (int)flags, minSize, maxSize, true);
      }
      return "";
    }
  
    FF_VAL getReturnValue() {
      FF_OBJ ret = FF_NEW_OBJ();
      Nan::Set(ret, FF_NEW_STRING("objects"), ObjectArrayConverter<Rect, cv::Rect>::wrap(objectRects));
      Nan::Set(ret, FF_NEW_STRING("rejectLevels"), IntArrayConverter::wrap(rejectLevels));
      Nan::Set(ret, FF_NEW_STRING("levelWeights"), DoubleArrayConverter::wrap(levelWeights));
      return ret;
    }
  };
  

}

#endif