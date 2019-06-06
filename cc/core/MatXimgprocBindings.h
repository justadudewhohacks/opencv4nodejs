#include "MatXimgproc.h"

#ifndef __FF_MATXIMGPROCBINDINGS_H__
#define __FF_MATXIMGPROCBINDINGS_H__

namespace MatXimgprocBindings {

  struct GuidedFilterWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    GuidedFilterWorker(cv::Mat self) {
      this->self = self;
    }

    cv::Mat guide;
    int radius;
    double eps;
    int ddepth = -1;

    cv::Mat dst;

    std::string executeCatchCvExceptionWorker() {
      cv::ximgproc::guidedFilter(guide, self, dst, radius, eps, ddepth);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(dst);
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &guide, info) ||
        FF::IntConverter::arg(1, &radius, info) ||
		  FF::DoubleConverter::arg(2, &eps, info)
        );
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
		  FF::IntConverter::optArg(3, &ddepth, info)
        );
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 3);
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[3]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
		  FF::IntConverter::optProp(&ddepth, "ddepth", opts)
      );
    }
  };

}

#endif