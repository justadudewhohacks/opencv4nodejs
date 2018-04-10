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
  
    FF_VAL getReturnValue() {
      FF_OBJ ret = FF_NEW_OBJ();
      Nan::Set(ret, FF_NEW_STRING("classes"), IntArrayConverter::wrap(clazz));
      Nan::Set(ret, FF_NEW_STRING("confidences"), DoubleArrayConverter::wrap(confidence));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return Mat::Converter::arg(0, &img, info);
    }
  };
  

}

#endif