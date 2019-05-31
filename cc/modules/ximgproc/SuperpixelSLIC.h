#include <opencv2/ximgproc.hpp>
#include "Mat.h"
#include "macros.h"

#if CV_MINOR_VERSION > 0

#ifndef __FF_SUPERPIXELSLIC_H__
#define __FF_SUPERPIXELSLIC_H__

class SuperpixelSLIC : public FF::ObjectWrap<SuperpixelSLIC, cv::Ptr<cv::ximgproc::SuperpixelSLIC>> {
public:
	cv::Ptr<cv::ximgproc::SuperpixelSLIC> superpixelSlic;
	cv::Mat image;
	cv::Mat labels;
	cv::Mat labelContourMask;
	int algorithm;
	int region_size;
	float ruler;
	int numCalculatedSuperpixels = 0;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);
	static NAN_METHOD(Iterate);

	static NAN_GETTER(GetImg) {
		info.GetReturnValue().Set(Mat::Converter::wrap(unwrapThis(info)->image));
	}
	static NAN_GETTER(GetLabels) {
		info.GetReturnValue().Set(Mat::Converter::wrap(unwrapThis(info)->labels));
	}
	static NAN_GETTER(GetLabelContourMask) {
		info.GetReturnValue().Set(Mat::Converter::wrap(unwrapThis(info)->labelContourMask));
	}

	static FF_GETTER(SuperpixelSLIC, GetAlgorithm, algorithm);
	static FF_GETTER(SuperpixelSLIC, GetRegionSize, region_size);
	static FF_GETTER(SuperpixelSLIC, GetRuler, ruler);
	static FF_GETTER(SuperpixelSLIC, GetNumCalculatedSuperpixels, numCalculatedSuperpixels);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  struct NewWorker : public CatchCvExceptionWorker {
  public:
	  cv::Mat image;
	  int algorithm = cv::ximgproc::SLICO;
	  int region_size = 10;
	  float ruler = 10.0f;

	  std::string executeCatchCvExceptionWorker() {
		  return "";
	  }

	  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  Mat::Converter::arg(0, &image, info)
			  );
	  }

	  bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  FF::IntConverter::optArg(1, &algorithm, info) ||
			  FF::IntConverter::optArg(2, &region_size, info) ||
			  FF::FloatConverter::optArg(3, &ruler, info)
			  );
	  }

	  bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return FF::isArgObject(info, 1);
	  }

	  bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		  v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
		  return (
			  FF::IntConverter::optProp(&algorithm, "algorithm", opts) ||
			  FF::IntConverter::optProp(&region_size, "region_size", opts) ||
			  FF::FloatConverter::optProp(&ruler, "ruler", opts)
			  );
	  }
  };
};

#endif

#endif