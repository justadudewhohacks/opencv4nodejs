#include <nan.h>
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include "macros.h"
#include "Size.h"

#ifndef __FF_HOGDESCRIPTOR_H__
#define __FF_HOGDESCRIPTOR_H__

class HOGDescriptor : public Nan::ObjectWrap {
public:
	cv::HOGDescriptor hog;

	static FF_GETTER_JSOBJ(HOGDescriptor, winSize, hog.winSize, FF_UNWRAP_SIZE_AND_GET, Size::constructor);
	static FF_GETTER_JSOBJ(HOGDescriptor, blockSize, hog.blockSize, FF_UNWRAP_SIZE_AND_GET, Size::constructor);
	static FF_GETTER_JSOBJ(HOGDescriptor, blockStride, hog.blockStride, FF_UNWRAP_SIZE_AND_GET, Size::constructor);
	static FF_GETTER_JSOBJ(HOGDescriptor, cellSize, hog.cellSize, FF_UNWRAP_SIZE_AND_GET, Size::constructor);
	static FF_GETTER(HOGDescriptor, nbins, hog.nbins);
	static FF_GETTER(HOGDescriptor, derivAperture, hog.derivAperture);
	static FF_GETTER(HOGDescriptor, histogramNormType, hog.histogramNormType);
	static FF_GETTER(HOGDescriptor, nlevels, hog.nlevels);
	static FF_GETTER(HOGDescriptor, winSigma, hog.winSigma);
	static FF_GETTER(HOGDescriptor, L2HysThreshold, hog.L2HysThreshold);
	static FF_GETTER(HOGDescriptor, gammaCorrection, hog.gammaCorrection);
	static FF_GETTER(HOGDescriptor, signedGradient, hog.signedGradient);

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);
	static NAN_METHOD(Compute);

	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif