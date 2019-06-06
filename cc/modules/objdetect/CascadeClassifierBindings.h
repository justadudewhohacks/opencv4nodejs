#include "CascadeClassifier.h"

#ifndef __FF_CASCADECLASSIFIERBINDINGS_H_
#define __FF_CASCADECLASSIFIERBINDINGS_H_

namespace CascadeClassifierBindings {

	struct NewWorker : CatchCvExceptionWorker {
	public:
		std::string xmlFilePath;

		bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::StringConverter::arg(0, &xmlFilePath, info);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};

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
  
    v8::Local<v8::Value> getReturnValue() {
      if (isGpu) {
        return Rect::ArrayWithCastConverter<cv::Rect>::wrap(objectRects);
      }
      else {
        v8::Local<v8::Object> ret = Nan::New<v8::Object>();
        Nan::Set(ret, FF::newString("objects"), Rect::ArrayWithCastConverter<cv::Rect>::wrap(objectRects));
        Nan::Set(ret, FF::newString("numDetections"), FF::IntArrayConverter::wrap(numDetections));
        return ret;
      }
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return Mat::Converter::arg(0, &img, info);
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::DoubleConverter::optArg(1, &scaleFactor, info) ||
        FF::UintConverter::optArg(2, &minNeighbors, info) ||
        FF::UintConverter::optArg(3, &flags, info) ||
        Size::Converter::optArg(4, &minSize, info) ||
        Size::Converter::optArg(5, &maxSize, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 1);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        FF::DoubleConverter::optProp(&scaleFactor, "scaleFactor", opts) ||
        FF::UintConverter::optProp(&minNeighbors, "minNeighbors", opts) ||
        FF::UintConverter::optProp(&flags, "flags", opts) ||
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
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, FF::newString("objects"), Rect::ArrayWithCastConverter<cv::Rect>::wrap(objectRects));
      Nan::Set(ret, FF::newString("rejectLevels"), FF::IntArrayConverter::wrap(rejectLevels));
      Nan::Set(ret, FF::newString("levelWeights"), FF::DoubleArrayConverter::wrap(levelWeights));
      return ret;
    }
  };
  

}

#endif