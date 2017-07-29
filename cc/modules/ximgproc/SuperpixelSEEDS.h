#include <nan.h>
#include <opencv2/ximgproc.hpp>
#include "Mat.h"
#include "macros.h"

#ifndef __FF_SUPERPIXELSEEDS_H__
#define __FF_SUPERPIXELSEEDS_H__

class SuperpixelSEEDS : public Nan::ObjectWrap {
public:
	cv::Ptr<cv::ximgproc::SuperpixelSEEDS> superpixelSeeds;
	Nan::Persistent<v8::Object> jsImg;
	int numSuperpixels;
	int numLevels;
	int prior = 2;
	int histogramBins = 5;
	bool doubleStep = false;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static NAN_GETTER(GetImg) {
		info.GetReturnValue().Set(Nan::New(Nan::ObjectWrap::Unwrap<SuperpixelSEEDS>(info.This())->jsImg));
	}
	static FF_GETTER(SuperpixelSEEDS, GetNumSuperpixels, numSuperpixels);
	static FF_GETTER(SuperpixelSEEDS, GeNumLevels, numLevels);
	static FF_GETTER(SuperpixelSEEDS, GetPrior, prior);
	static FF_GETTER(SuperpixelSEEDS, GetHistogramBins, histogramBins);
	static FF_GETTER(SuperpixelSEEDS, GetDoubleStep, doubleStep);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif