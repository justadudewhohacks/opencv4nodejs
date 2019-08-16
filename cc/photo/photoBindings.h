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
				FF::FloatConverter::optArg(1, &h, info) ||
				FF::FloatConverter::optArg(2, &hColor, info) ||
				FF::IntConverter::optArg(3, &templateWindowSize, info) ||
				FF::IntConverter::optArg(4, &searchWindowSize, info)
			);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 1);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::FloatConverter::optProp(&h, "h", opts) ||
				FF::FloatConverter::optProp(&hColor, "hColor", opts) ||
				FF::IntConverter::optProp(&templateWindowSize, "templateWindowSize", opts) ||
				FF::IntConverter::optProp(&searchWindowSize, "searchWindowSize", opts)
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
        FF::DoubleConverter::arg(2, &inpaintRadius, info) ||
        FF::IntConverter::arg(3, &flags, info)
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

  struct SeamlessCloningWorker : public CatchCvExceptionWorker {
  public:
    // required function arguments
    cv::Mat src;
    cv::Mat dst;
    cv::Mat mask;
    cv::Point2d p;
    int flags;

    // return value
    cv::Mat blend;

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &src, info) ||
        Mat::Converter::arg(1, &dst, info) ||
        Mat::Converter::arg(2, &mask, info) ||
        Point2::Converter::arg(3, &p, info) ||
        FF::IntConverter::arg(4, &flags, info)
      );
    }

    std::string executeCatchCvExceptionWorker() {
      cv::seamlessClone(
        src, dst, mask, p, blend, flags
      );
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(blend);
    }
  };

}

#endif