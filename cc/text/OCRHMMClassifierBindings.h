#include "OCRHMMClassifier.h"

#ifndef __FF_OCRHMMCLASSIFIERBINDINGS_H_
#define __FF_OCRHMMCLASSIFIERBINDINGS_H_

namespace OCRHMMClassifierBindings {

  struct EvalWorker : public CatchCvExceptionWorker {
  public:
    cv::Ptr <cv::text::OCRHMMDecoder::ClassifierCallback> classifier;
  
    EvalWorker(cv::Ptr <cv::text::OCRHMMDecoder::ClassifierCallback> classifier) {
      this->classifier = classifier;
    }
  
    cv::Mat img;
    std::vector<int> clazz;
    std::vector<double> confidence;
  
  
    std::string executeCatchCvExceptionWorker() {
      classifier->eval(img, clazz, confidence);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, FF::newString("classes"), FF::IntArrayConverter::wrap(clazz));
      Nan::Set(ret, FF::newString("confidences"), FF::DoubleArrayConverter::wrap(confidence));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return Mat::Converter::arg(0, &img, info);
    }
  };
  

}

#endif