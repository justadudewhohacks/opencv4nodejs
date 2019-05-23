#include <opencv2/ximgproc.hpp>
#include "Mat.h"
#include "macros.h"

#if CV_MINOR_VERSION > 0

#ifndef __FF_SUPERPIXELSLIC_H__
#define __FF_SUPERPIXELSLIC_H__

class SuperpixelSLIC : public Nan::ObjectWrap {
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

	static FF_GETTER_JSOBJ(SuperpixelSLIC, GetImg, image, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(SuperpixelSLIC, GetLabels, labels, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(SuperpixelSLIC, GetLabelContourMask, labelContourMask, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
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
			  IntConverter::optArg(1, &algorithm, info) ||
			  IntConverter::optArg(2, &region_size, info) ||
			  FloatConverter::optArg(3, &ruler, info)
			  );
	  }

	  bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return FF::isArgObject(info, 1);
	  }

	  bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		  v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
		  return (
			  IntConverter::optProp(&algorithm, "algorithm", opts) ||
			  IntConverter::optProp(&region_size, "region_size", opts) ||
			  FloatConverter::optProp(&ruler, "ruler", opts)
			  );
	  }
  };
};

#endif

#endif