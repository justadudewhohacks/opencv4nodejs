#include "photo.h"

#ifndef __FF_PHOTOBINDINGS_H_
#define __FF_PHOTOBINDINGS_H_

namespace PhotoBindings {

	struct FastNlMeansDenoisingColoredWorker : public CatchCvExceptionWorker {
	public:
		cv::Mat src;
		float h = 3;
		float hColor = 3;
		int templateWindowSize = 7;
		int searchWindowSize = 21;

		cv::Mat returnValue;

		std::string executeCatchCvExceptionWorker() {
			cv::fastNlMeansDenoisingColored(src, returnValue, h, hColor, templateWindowSize, searchWindowSize);
			return "";
		}

		v8::Local<v8::Value> getReturnValue() {
			return Mat::Converter::wrap(returnValue);
		}

		bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				Mat::Converter::arg(0, &src, info)
			);
		}

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FloatConverter::optArg(1, &h, info) ||
				FloatConverter::optArg(2, &hColor, info) ||
				IntConverter::optArg(3, &templateWindowSize, info) ||
				IntConverter::optArg(4, &searchWindowSize, info)
			);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 1);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FloatConverter::optProp(&h, "h", opts) ||
				FloatConverter::optProp(&hColor, "hColor", opts) ||
				IntConverter::optProp(&templateWindowSize, "templateWindowSize", opts) ||
				IntConverter::optProp(&searchWindowSize, "searchWindowSize", opts)
				);
		}
	};

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
  
    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(dst);
    }
  };
  

}

#endif