#include "ImgHashBase.h"

#ifndef __FF_IMGHASHBASEBINDINGS_H_
#define __FF_IMGHASHBASEBINDINGS_H_

namespace ImgHashBaseBindings {

  struct CompareWorker : public CatchCvExceptionWorker {
  public:
    cv::Ptr<cv::img_hash::ImgHashBase> self;
    CompareWorker(cv::Ptr<cv::img_hash::ImgHashBase> self) { this->self = self; }

    std::vector<uchar> hashOne;
    std::vector<uchar> hashTwo;
    double returnValue;

    std::string executeCatchCvExceptionWorker() {
      returnValue = self->compare(hashOne, hashTwo);
      return "";
    }

	  v8::Local<v8::Value> getReturnValue() {
		  v8::Local<v8::Value> ret = FF::DoubleConverter::wrap(returnValue);
		  return ret;
	  }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (FF::UcharArrayConverter::arg(0, &hashOne, info) ||
        FF::UcharArrayConverter::arg(1, &hashTwo, info));
    }
  };

  struct ComputeWorker : public CatchCvExceptionWorker {
  public:
	  cv::Ptr<cv::img_hash::ImgHashBase> self;
	  ComputeWorker(cv::Ptr<cv::img_hash::ImgHashBase> self) { this->self = self; }

	  cv::Mat inputArr;
    std::vector<uchar> outputArr;

	  std::string executeCatchCvExceptionWorker() {
		  self->compute(inputArr, outputArr);
		  return "";
	  }

	  v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Value> ret = FF::UcharArrayConverter::wrap(outputArr);
		  return ret;
	  }

	  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (Mat::Converter::arg(0, &inputArr, info));
	  }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (FF::UcharArrayConverter::optArg(1, &outputArr, info));
    }
    
  };

}

#endif


