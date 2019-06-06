#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include "Size.h"
#include "Mat.h"
#include "Rect.h"
#include "Point.h"
#include "DetectionROI.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_HOGDESCRIPTOR_H__
#define __FF_HOGDESCRIPTOR_H__

class HOGDescriptor : public FF::ObjectWrap<HOGDescriptor, std::shared_ptr<cv::HOGDescriptor>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "HOGDescriptor";
	}

	FF_ACCESSORS_PTR(winSize, Size::Converter);
	FF_ACCESSORS_PTR(blockSize, Size::Converter);
	FF_ACCESSORS_PTR(blockStride, Size::Converter);
	FF_ACCESSORS_PTR(cellSize, Size::Converter);
	FF_ACCESSORS_PTR(nbins, FF::IntConverter);
	FF_ACCESSORS_PTR(derivAperture, FF::IntConverter);
	FF_ACCESSORS_PTR(winSigma, FF::DoubleConverter);
	FF_ACCESSORS_PTR(histogramNormType, FF::IntConverter);
	FF_ACCESSORS_PTR(L2HysThreshold, FF::DoubleConverter);
	FF_ACCESSORS_PTR(gammaCorrection, FF::BoolConverter);
	FF_ACCESSORS_PTR(nlevels, FF::IntConverter);
	FF_ACCESSORS_PTR(signedGradient, FF::BoolConverter);

	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(New);
	static NAN_METHOD(GetDaimlerPeopleDetector);
	static NAN_METHOD(GetDefaultPeopleDetector);
	static NAN_METHOD(CheckDetectorSize);
	static NAN_METHOD(SetSVMDetector);
	static NAN_METHOD(Save);
	static NAN_METHOD(Load);
	static NAN_METHOD(Compute);
	static NAN_METHOD(ComputeAsync);
	static NAN_METHOD(ComputeGradient);
	static NAN_METHOD(ComputeGradientAsync);
	static NAN_METHOD(Detect);
	static NAN_METHOD(DetectAsync);
	static NAN_METHOD(DetectROI);
	static NAN_METHOD(DetectROIAsync);
	static NAN_METHOD(DetectMultiScale);
	static NAN_METHOD(DetectMultiScaleAsync);
	static NAN_METHOD(DetectMultiScaleROI);
	static NAN_METHOD(DetectMultiScaleROIAsync);
	static NAN_METHOD(GroupRectangles);
	static NAN_METHOD(GroupRectanglesAsync);
};

#endif