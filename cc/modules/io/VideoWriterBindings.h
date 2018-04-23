#include "VideoWriter.h"

#ifndef __FF_VIDEOWRITERBINDINGS_H_
#define __FF_VIDEOWRITERBINDINGS_H_

namespace VideoWriterBindings {

  struct NewWorker : CatchCvExceptionWorker {
  public:
    std::string fileName;
    int fourccCode;
    double fps;
    cv::Size2d frameSize;
    bool isColor = true;
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        StringConverter::arg(0, &fileName, info) ||
        IntConverter::arg(1, &fourccCode, info) ||
        DoubleConverter::arg(2, &fps, info) ||
        Size::Converter::arg(3, &frameSize, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return BoolConverter::optArg(4, &isColor, info);
    }
  
    std::string executeCatchCvExceptionWorker() {
      return "";
    }
  };
  
  struct FourccWorker : CatchCvExceptionWorker {
  public:
    std::string fourcc;
  
    int code;
  
    std::string executeCatchCvExceptionWorker() {
      code = cv::VideoWriter::fourcc(fourcc.at(0), fourcc.at(1), fourcc.at(2), fourcc.at(3));
      return "";
    }
  
    FF_VAL getReturnValue() {
      return IntConverter::wrap(code);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return StringConverter::arg(0, &fourcc, info);
    }
  };
  
  struct WriteWorker : CatchCvExceptionWorker {
  public:
    cv::VideoWriter writer;
    WriteWorker(cv::VideoWriter writer) {
      this->writer = writer;
    }
  
    cv::Mat frame;
  
    std::string executeCatchCvExceptionWorker() {
      writer.write(frame);
      return "";
    }
  
    FF_VAL getReturnValue() {
      return BoolConverter::wrap(true);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return Mat::Converter::arg(0, &frame, info);
    }
  };
  

}

#endif