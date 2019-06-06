#include "OCRHMMDecoder.h"

#ifndef __FF_OCRHMMDECODERBINDINGS_H_
#define __FF_OCRHMMDECODERBINDINGS_H_

namespace OCRHMMDecoderBindings {

  struct NewWorker : public FF::SimpleWorker  {
  public:
    cv::Ptr <cv::text::OCRHMMDecoder::ClassifierCallback> classifier;
    std::string vocabulary;
    cv::Mat transition_probabilities_table;
    cv::Mat emission_probabilities_table;
    int mode = cv::text::OCR_DECODER_VITERBI;
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        OCRHMMClassifier::Converter::arg(0, &classifier, info) ||
        FF::StringConverter::arg(1, &vocabulary, info) ||
        Mat::Converter::arg(2, &transition_probabilities_table, info) ||
        Mat::Converter::arg(3, &emission_probabilities_table, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::IntConverter::optArg(4, &mode, info)
      );
    }
  };
  
  struct BaseRunWorker : public CatchCvExceptionWorker {
  public:
    cv::Ptr <cv::text::OCRHMMDecoder> decoder;
  
    BaseRunWorker(cv::Ptr<cv::text::OCRHMMDecoder> decoder) {
      this->decoder = decoder;
    }
  
    cv::Mat img;
    int min_confidence;
    cv::Mat mask = cv::noArray().getMat();
    int component_level = 0;
  
    std::string output_text;
  };
  
  struct RunWorker : public BaseRunWorker {
  public:
    RunWorker(cv::Ptr<cv::text::OCRHMMDecoder> decoder) : BaseRunWorker(decoder) {
    }
  
    std::string executeCatchCvExceptionWorker() {
  #if CV_VERSION_GREATER_EQUAL(3, 1, 0)
      if (mask.empty()) {
        output_text = decoder->run(img, min_confidence, component_level);
      }
      else {
        output_text = decoder->run(img, mask, min_confidence, component_level);
      }
  #else
      decoder->run(img, output_text);
  #endif
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return FF::StringConverter::wrap(output_text);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &img, info) ||
        FF::IntConverter::arg(1, &min_confidence, info)
      );
    }
  
  #if CV_VERSION_GREATER_EQUAL(3, 1, 0)
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::optArg(2, &mask, info) ||
        FF::IntConverter::optArg(3, &component_level, info)
      );
    }
  #endif
  };
  
  struct RunWithInfoWorker : public BaseRunWorker {
  public:
    RunWithInfoWorker(cv::Ptr<cv::text::OCRHMMDecoder> decoder) : BaseRunWorker(decoder) {
    }
  
    std::vector<cv::Rect> component_rects;
    std::vector<std::string> component_texts;
    std::vector<float> component_confidences;
  
  
    std::string executeCatchCvExceptionWorker() {
  #if CV_VERSION_GREATER_EQUAL(3, 1, 0)
      if (mask.empty()) {
        decoder->run(img, output_text, &component_rects, &component_texts, &component_confidences, component_level);
      }
      else {
        decoder->run(img, mask, output_text, &component_rects, &component_texts, &component_confidences, component_level);
      }
  #else
      decoder->run(img, output_text, &component_rects, &component_texts, &component_confidences, component_level);
  #endif
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, FF::newString("outputText"), FF::StringConverter::wrap(output_text));
      Nan::Set(ret, FF::newString("rects"), Rect::ArrayWithCastConverter<cv::Rect>::wrap(component_rects));
      Nan::Set(ret, FF::newString("words"), FF::StringArrayConverter::wrap(component_texts));
      Nan::Set(ret, FF::newString("confidences"), FF::FloatArrayConverter::wrap(component_confidences));
      return ret;
    }
  
  
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &img, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::optArg(1, &mask, info) ||
        FF::IntConverter::optArg(2, &component_level, info)
      );
    }
  };
  

}

#endif