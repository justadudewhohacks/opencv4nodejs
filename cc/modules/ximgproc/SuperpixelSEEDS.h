#include <opencv2/ximgproc.hpp>
#include "Mat.h"
#include "macros.h"

#ifndef __FF_SUPERPIXELSEEDS_H__
#define __FF_SUPERPIXELSEEDS_H__

class SuperpixelSEEDS : public Nan::ObjectWrap {
public:
	cv::Ptr<cv::ximgproc::SuperpixelSEEDS> superpixelSeeds;
	cv::Mat img;
	cv::Mat labels;
	cv::Mat labelContourMask;
	int num_superpixels;
	int num_levels;
	int prior = 2;
	int histogram_bins = 5;
	bool double_step = false;
	int numCalculatedSuperpixels = 0;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);
	static NAN_METHOD(Iterate);

	static FF_GETTER_JSOBJ(SuperpixelSEEDS, GetImg, img, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(SuperpixelSEEDS, GetLabels, labels, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(SuperpixelSEEDS, GetLabelContourMask, labelContourMask, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER(SuperpixelSEEDS, GetNumSuperpixels, num_superpixels);
	static FF_GETTER(SuperpixelSEEDS, GeNumLevels, num_levels);
	static FF_GETTER(SuperpixelSEEDS, GetPrior, prior);
	static FF_GETTER(SuperpixelSEEDS, GetHistogramBins, histogram_bins);
	static FF_GETTER(SuperpixelSEEDS, GetDoubleStep, double_step);
	static FF_GETTER(SuperpixelSEEDS, GetNumCalculatedSuperpixels, numCalculatedSuperpixels);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  struct NewWorker : public CatchCvExceptionWorker {
  public:
	  cv::Mat img;
	  int num_superpixels;
	  int num_levels;
	  int histogram_bins = 5;
	  int prior = 2;
	  bool double_step = false;


	  std::string executeCatchCvExceptionWorker() {
		  return "";
	  }

	  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  Mat::Converter::arg(0, &img, info) ||
			  IntConverter::arg(1, &num_superpixels, info) ||
			  IntConverter::arg(2, &num_levels, info)
			);
	  }

	  bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (
			  IntConverter::optArg(3, &histogram_bins, info) ||
			  IntConverter::optArg(4, &prior, info) ||
			  BoolConverter::optArg(5, &double_step, info)
			  );
	  }

	  bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return FF::isArgObject(info, 3);
	  }

	  bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		  v8::Local<v8::Object> opts = info[3]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
		  return (
			  IntConverter::optProp(&histogram_bins, "histogram_bins", opts) ||
			  IntConverter::optProp(&prior, "prior", opts) ||
			  BoolConverter::optProp(&double_step, "double_step", opts)
			);
	  }
  };
};

#endif