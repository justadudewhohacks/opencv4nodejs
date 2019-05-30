#include "text.h"

#ifndef __FF_TEXTBINDINGS_H_
#define __FF_TEXTBINDINGS_H_

namespace TextBindings {

  struct LoadOCRHMMClassifierWorker : public CatchCvExceptionWorker {
  public:
    cv::Ptr <cv::text::OCRHMMDecoder::ClassifierCallback> classifier;
    std::string file;

    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> jsClassifier = FF::newInstance(Nan::New(OCRHMMClassifier::constructor));
      FF_UNWRAP(jsClassifier, OCRHMMClassifier)->classifier = classifier;
      return jsClassifier;
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::StringConverter::arg(0, &file, info);
    }
  };

  struct LoadOCRHMMClassifierNMWorker : public LoadOCRHMMClassifierWorker {
    std::string executeCatchCvExceptionWorker() {
      classifier = cv::text::loadOCRHMMClassifierNM(file);
      return "";
    }
  };


#if CV_MINOR_VERSION > 0

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

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(transition_probabilities_table);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::StringConverter::arg(0, &vocabulary, info) ||
        StringArrayConverter::arg(1, &lexicon, info)
      );
    }
  };

#endif

}

#endif