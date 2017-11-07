#include <opencv2/ximgproc.hpp>
#include "Mat.h"
#include "macros.h"

#if CV_MINOR_VERSION > 0

#ifndef __FF_SUPERPIXELSLIC_H__
#define __FF_SUPERPIXELSLIC_H__

class SuperpixelSLIC : public Nan::ObjectWrap {
public:
	cv::Ptr<cv::ximgproc::SuperpixelSLIC> superpixelSlic;
	cv::Mat img;
	cv::Mat labels;
	cv::Mat labelContourMask;
	int algorithm;
	int regionSize = 10;
	float ruler = 10.0;
	int numCalculatedSuperpixels = 0;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);
	static NAN_METHOD(Iterate);

	static FF_GETTER_JSOBJ(SuperpixelSLIC, GetImg, img, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(SuperpixelSLIC, GetLabels, labels, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER_JSOBJ(SuperpixelSLIC, GetLabelContourMask, labelContourMask, FF_UNWRAP_MAT_AND_GET, Mat::constructor);
	static FF_GETTER(SuperpixelSLIC, GetAlgorithm, algorithm);
	static FF_GETTER(SuperpixelSLIC, GetRegionSize, regionSize);
	static FF_GETTER(SuperpixelSLIC, GetRuler, ruler);
	static FF_GETTER(SuperpixelSLIC, GetNumCalculatedSuperpixels, numCalculatedSuperpixels);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif

#endif