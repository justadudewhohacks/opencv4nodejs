#include <opencv2/ximgproc.hpp>
#include "Mat.h"
#include "macros.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

#ifndef __FF_SUPERPIXELLSC_H__
#define __FF_SUPERPIXELLSC_H__

class SuperpixelLSC : public FF::ObjectWrap<SuperpixelLSC, cv::Ptr<cv::ximgproc::SuperpixelLSC>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "SuperpixelLSC";
	}

	cv::Mat image;
	cv::Mat labels;
	cv::Mat labelContourMask;
	int region_size = 10;
	double ratio = 0.075;
	int numCalculatedSuperpixels = 0;

	FF_GETTER_CUSTOM(image, Mat::Converter, image);
	FF_GETTER_CUSTOM(labels, Mat::Converter, labels);
	FF_GETTER_CUSTOM(labelContourMask, Mat::Converter, labelContourMask);
	FF_GETTER_CUSTOM(region_size, FF::IntConverter, region_size);
	FF_GETTER_CUSTOM(ratio, FF::DoubleConverter, ratio);
	FF_GETTER_CUSTOM(numCalculatedSuperpixels, FF::IntConverter, numCalculatedSuperpixels);

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);
	static NAN_METHOD(Iterate);


  struct NewWorker : public CatchCvExceptionWorker {
  public:
	  cv::Mat image;
	  int region_size = 10;
	  float ratio = 0.075f;


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
			  FF::IntConverter::optArg(1, &region_size, info) ||
			  FF::FloatConverter::optArg(2, &ratio, info)
			  );
	  }

	  bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return FF::isArgObject(info, 1);
	  }

	  bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		  v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
		  return (
			  FF::IntConverter::optProp(&region_size, "region_size", opts) ||
			  FF::FloatConverter::optProp(&ratio, "ratio", opts)
			  );
	  }
  };
};

#endif

#endif