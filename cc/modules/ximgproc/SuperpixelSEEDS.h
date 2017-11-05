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
	int numSuperpixels;
	int numLevels;
	int prior = 2;
	int histogramBins = 5;
	bool doubleStep = false;
	int numCalculatedSuperpixels = 0;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);
	static NAN_METHOD(Iterate);

	static FF_GETTER_JSOBJ(SuperpixelSEEDS, GetImg, img, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(SuperpixelSEEDS, GetLabels, labels, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(SuperpixelSEEDS, GetLabelContourMask, labelContourMask, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER(SuperpixelSEEDS, GetNumSuperpixels, numSuperpixels);
	static FF_GETTER(SuperpixelSEEDS, GeNumLevels, numLevels);
	static FF_GETTER(SuperpixelSEEDS, GetPrior, prior);
	static FF_GETTER(SuperpixelSEEDS, GetHistogramBins, histogramBins);
	static FF_GETTER(SuperpixelSEEDS, GetDoubleStep, doubleStep);
	static FF_GETTER(SuperpixelSEEDS, GetNumCalculatedSuperpixels, numCalculatedSuperpixels);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif