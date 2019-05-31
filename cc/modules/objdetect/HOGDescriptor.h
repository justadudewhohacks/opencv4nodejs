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

	static NAN_GETTER(winSize) {
		info.GetReturnValue().Set(Size::Converter::wrap(unwrapThis(info)->winSize));
	}
	static NAN_GETTER(blockSize) {
		info.GetReturnValue().Set(Size::Converter::wrap(unwrapThis(info)->blockSize));
	}
	static NAN_GETTER(blockStride) {
		info.GetReturnValue().Set(Size::Converter::wrap(unwrapThis(info)->blockStride));
	}
	static NAN_GETTER(cellSize) {
		info.GetReturnValue().Set(Size::Converter::wrap(unwrapThis(info)->cellSize));
	}

	static FF_GETTER(HOGDescriptor, nbins, self->nbins);
	static FF_GETTER(HOGDescriptor, derivAperture, self->derivAperture);
	static FF_GETTER(HOGDescriptor, histogramNormType, self->histogramNormType);
	static FF_GETTER(HOGDescriptor, nlevels, self->nlevels);
	static FF_GETTER(HOGDescriptor, winSigma, self->winSigma);
	static FF_GETTER(HOGDescriptor, L2HysThreshold, self->L2HysThreshold);
	static FF_GETTER(HOGDescriptor, gammaCorrection, self->gammaCorrection);
	static FF_GETTER(HOGDescriptor, signedGradient, self->signedGradient);

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