#include "photo.h"

#ifndef __FF_PHOTOBINDINGS_H_
#define __FF_PHOTOBINDINGS_H_

namespace PhotoBindings {

  struct InpaintWorker : public CatchCvExceptionWorker {
  public:
    // required function arguments
    cv::Mat src;
    cv::Mat inpaintMask;
    double inpaintRadius;
    int flags;
  
    // function return value
    cv::Mat dst;
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &src, info) ||
        Mat::Converter::arg(1, &inpaintMask, info) ||
        DoubleConverter::arg(2, &inpaintRadius, info) ||
        IntConverter::arg(3, &flags, info)
      );
    }
  
    std::string executeCatchCvExceptionWorker() {
      cv::inpaint(
          src, inpaintMask, dst,
          inpaintRadius, flags
      );
      return "";
    }
  
    FF_VAL getReturnValue() {
      return Mat::Converter::wrap(dst);
    }
  };
  

}

#endif