#include <opencv2/ximgproc.hpp>
#include "Mat.h"
#include "macros.h"

#if CV_MINOR_VERSION > 0

#ifndef __FF_SUPERPIXELLSC_H__
#define __FF_SUPERPIXELLSC_H__

class SuperpixelLSC : public Nan::ObjectWrap {
public:
	cv::Ptr<cv::ximgproc::SuperpixelLSC> superpixelLsc;
	cv::Mat img;
	cv::Mat labels;
	cv::Mat labelContourMask;
	int regionSize = 10;
	float ratio = 0.075;
	int numCalculatedSuperpixels = 0;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);
	static NAN_METHOD(Iterate);

	static FF_GETTER_JSOBJ(SuperpixelLSC, GetImg, img, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(SuperpixelLSC, GetLabels, labels, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(SuperpixelLSC, GetLabelContourMask, labelContourMask, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER(SuperpixelLSC, GetRegionSize, regionSize);
	static FF_GETTER(SuperpixelLSC, GetRatio, ratio);
	static FF_GETTER(SuperpixelLSC, GetNumCalculatedSuperpixels, numCalculatedSuperpixels);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif

#endif