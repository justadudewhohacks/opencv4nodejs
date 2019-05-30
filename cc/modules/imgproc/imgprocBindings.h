#include "imgproc.h"
#include <opencv2/imgproc.hpp>

#ifndef __FF_IMGPROCBINDINGS_H_
#define __FF_IMGPROCBINDINGS_H_

namespace ImgprocBindings {

  struct GetTextSizeWorker : public CatchCvExceptionWorker {
  public:
    std::string text;
    int fontFace;
    double fontScale;
    int thickness;

    cv::Size2d returnValue;
    int baseLine;

    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::getTextSize(text, fontFace, fontScale, thickness, &baseLine);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("size").ToLocalChecked(), Size::Converter::wrap(returnValue));
      Nan::Set(ret, Nan::New("baseLine").ToLocalChecked(), FF::IntConverter::wrap(baseLine));
      return ret;
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::StringConverter::arg(0, &text, info) ||
        FF::IntConverter::arg(1, &fontFace, info) ||
        FF::DoubleConverter::arg(2, &fontScale, info) ||
        FF::IntConverter::arg(3, &thickness, info)
      );
    }
  };

#if CV_VERSION_MINOR > 1
  struct CannyWorker : public CatchCvExceptionWorker {
  public:

	  cv::Mat dx;
	  cv::Mat dy;
	  double threshold1;
	  double threshold2;
	  bool L2gradient = false;

	  cv::Mat returnValue;

	  std::string executeCatchCvExceptionWorker() {
		  cv::Canny(dx, dy, returnValue, threshold1, threshold2, L2gradient);
		  return "";
	  }

	  v8::Local<v8::Value> getReturnValue() {
		  return Mat::Converter::wrap(returnValue);
	  }

	  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  Mat::Converter::arg(0, &dx, info) ||
			  Mat::Converter::arg(1, &dy, info) ||
			  FF::DoubleConverter::arg(2, &threshold1, info) ||
			  FF::DoubleConverter::arg(3, &threshold2, info)
			  );
	  }

	  bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  FF::BoolConverter::optArg(4, &L2gradient, info)
			  );
	  }
  };
#endif

  struct ApplyColorMapWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat src;
    cv::Mat dst;
    cv::Mat userColor;
    int colormap;
    bool useUserColor = 0;

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
#if CV_VERSION_MINOR < 3
      return (Mat::Converter::arg(0, &src, info) ||
              FF::IntConverter::optArg(1, &colormap, info));
#endif

#if CV_VERSION_MINOR >= 3
      if (info[1]->IsNumber()) {
        return (Mat::Converter::arg(0, &src, info) ||
                FF::IntConverter::optArg(1, &colormap, info));
      }

      useUserColor = 1;

      return (Mat::Converter::arg(0, &src, info) ||
              Mat::Converter::arg(1, &userColor, info));
#endif
    }

    std::string executeCatchCvExceptionWorker() {
#if CV_VERSION_MINOR < 3
      cv::applyColorMap(src, dst, colormap);
      return "";
#endif

#if CV_VERSION_MINOR >= 3
      if (useUserColor) {
        cv::applyColorMap(src, dst, userColor);
      } else {
        cv::applyColorMap(src, dst, colormap);
      }
      return "";
#endif
    }

    v8::Local<v8::Value> getReturnValue() { return Mat::Converter::wrap(dst); }
  };
  struct UndistortPointsWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat distCoeffs;
    cv::Mat cameraMatrix;
    std::vector<cv::Point2f> srcPoints;
    std::vector<cv::Point2f> destPoints; 

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Point2::ArrayWithCastConverter<cv::Point2f>::arg(0, &srcPoints, info) ||
        Mat::Converter::arg(1, &cameraMatrix, info) ||
        Mat::Converter::arg(2, &distCoeffs, info)
      );
    }

    std::string executeCatchCvExceptionWorker() {
      cv::undistortPoints(srcPoints, destPoints, cameraMatrix, distCoeffs, cameraMatrix);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() { 
      return Point2::ArrayWithCastConverter<cv::Point2f>::wrap(destPoints);
    }
  };
}

#endif
