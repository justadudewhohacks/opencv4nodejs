#include "SVM.h"

#ifndef __FF_SVMBINDINGS_H_
#define __FF_SVMBINDINGS_H_

namespace SVMBindings {

  struct TrainFromTrainDataWorker : CatchCvExceptionWorker {
  public:
    cv::Ptr<cv::ml::SVM> svm;
  
    TrainFromTrainDataWorker(cv::Ptr<cv::ml::SVM> svm) {
      this->svm = svm;
    }
  
    cv::Ptr<cv::ml::TrainData> trainData;
    uint flags;
  
    bool ret;
  
    std::string executeCatchCvExceptionWorker() {
      ret = svm->train(trainData, (int)flags);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return Nan::New(ret);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return TrainData::Converter::arg(0, &trainData, info);
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::UintConverter::optArg(1, &flags, info);
    }
  };
  
  struct TrainFromMatWorker : CatchCvExceptionWorker {
  public:
    cv::Ptr<cv::ml::SVM> svm;
  
    TrainFromMatWorker(cv::Ptr<cv::ml::SVM> svm) {
      this->svm = svm;
    }
  
    cv::Mat samples;
    uint layout;
    cv::Mat responses;
  
    bool ret;
  
    std::string executeCatchCvExceptionWorker() {
      ret = svm->train(samples, (int)layout, responses);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return Nan::New(ret);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &samples, info) ||
        FF::UintConverter::arg(1, &layout, info) ||
        Mat::Converter::arg(2, &responses, info)
      );
    }
  };
  
  struct TrainAutoWorker : CatchCvExceptionWorker  {
  public:
    cv::Ptr<cv::ml::SVM> svm;
  
    TrainAutoWorker(cv::Ptr<cv::ml::SVM> svm) {
      this->svm = svm;
    }
  
    cv::Ptr<cv::ml::TrainData> trainData;
    uint kFold = 10;
    cv::ml::ParamGrid cGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::C);
    cv::ml::ParamGrid gammaGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::GAMMA);
    cv::ml::ParamGrid pGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::P);
    cv::ml::ParamGrid nuGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::NU);
    cv::ml::ParamGrid coeffGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::COEF);
    cv::ml::ParamGrid degreeGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::DEGREE);
    bool balanced = false;
  
    bool ret;
  
    std::string executeCatchCvExceptionWorker() {
      ret = svm->trainAuto(trainData, (int)kFold, cGrid, gammaGrid, pGrid, nuGrid, coeffGrid, degreeGrid, balanced);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return Nan::New(ret);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return TrainData::Converter::arg(0, &trainData, info);
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::UintConverter::optArg(1, &kFold, info) ||
        ParamGrid::Converter::optArg(2, &cGrid, info) ||
        ParamGrid::Converter::optArg(3, &gammaGrid, info) ||
        ParamGrid::Converter::optArg(4, &pGrid, info) ||
        ParamGrid::Converter::optArg(5, &nuGrid, info) ||
        ParamGrid::Converter::optArg(6, &coeffGrid, info) ||
        ParamGrid::Converter::optArg(7, &degreeGrid, info) ||
        FF::BoolConverter::optArg(8, &balanced, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 1);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        FF::UintConverter::optProp(&kFold, "kFold", opts) ||
        ParamGrid::Converter::optProp(&cGrid, "cGrid", opts) ||
        ParamGrid::Converter::optProp(&gammaGrid, "gammaGrid", opts) ||
        ParamGrid::Converter::optProp(&pGrid, "pGrid", opts) ||
        ParamGrid::Converter::optProp(&nuGrid, "nuGrid", opts) ||
        ParamGrid::Converter::optProp(&coeffGrid, "coeffGrid", opts) ||
        ParamGrid::Converter::optProp(&degreeGrid, "degreeGrid", opts) ||
        FF::BoolConverter::optProp(&balanced, "balanced", opts)
      );
    }
  };
  

}

#endif