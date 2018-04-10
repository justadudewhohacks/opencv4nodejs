#include "text.h"

#ifndef __FF_TEXTBINDINGS_H_
#define __FF_TEXTBINDINGS_H_

namespace TextBindings {

  struct LoadOCRHMMClassifierWorker : public CatchCvExceptionWorker {
  public:
    cv::Ptr <cv::text::OCRHMMDecoder::ClassifierCallback> classifier;
    std::string file;
  
    FF_VAL getReturnValue() {
      FF_OBJ jsClassifier = FF_NEW_INSTANCE(OCRHMMClassifier::constructor);
      FF_UNWRAP(jsClassifier, OCRHMMClassifier)->classifier = classifier;
      return jsClassifier;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return StringConverter::arg(0, &file, info);
    }
  };
  
  struct LoadOCRHMMClassifierNMWorker : public LoadOCRHMMClassifierWorker {
    std::string executeCatchCvExceptionWorker() {
      classifier = cv::text::loadOCRHMMClassifierNM(file);
      return "";
    }
  };
  
  struct LoadOCRHMMClassifierCNNWorker : public LoadOCRHMMClassifierWorker {
    std::string executeCatchCvExceptionWorker() {
      classifier = cv::text::loadOCRHMMClassifierCNN(file);
      return "";
    }
  };
  
  struct CreateOCRHMMTransitionsTableWorker : public CatchCvExceptionWorker {
  public:
    std::string vocabulary;
    std::vector<std::string> lexicon;
  
    cv::Mat transition_probabilities_table;
  
    std::string executeCatchCvExceptionWorker() {
      cv::text::createOCRHMMTransitionsTable(vocabulary, lexicon, transition_probabilities_table);
      return "";
    }
  
    FF_VAL getReturnValue() {
      return Mat::Converter::wrap(transition_probabilities_table);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        StringConverter::arg(0, &vocabulary, info) ||
        StringArrayConverter::arg(1, &lexicon, info)
      );
    }
  };
  

}

#endif