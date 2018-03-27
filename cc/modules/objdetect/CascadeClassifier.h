#include "Converters.h"
#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include "Mat.h"
#include "Rect.h"

#ifndef __FF_CASCADECLASSIFIER_H__
#define __FF_CASCADECLASSIFIER_H__

class CascadeClassifier : public Nan::ObjectWrap {
public:
	cv::CascadeClassifier classifier;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	struct DetectMultiScaleWorker;
	static NAN_METHOD(DetectMultiScale);
	static NAN_METHOD(DetectMultiScaleAsync); 
	static NAN_METHOD(DetectMultiScaleGpu);

	struct DetectMultiScaleWithRejectLevelsWorker;
	static NAN_METHOD(DetectMultiScaleWithRejectLevels);
	static NAN_METHOD(DetectMultiScaleWithRejectLevelsAsync);
	static NAN_METHOD(DetectMultiScaleWithRejectLevelsGpu);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::CascadeClassifier* getNativeObjectPtr() { return &classifier; }
	cv::CascadeClassifier getNativeObject() { return classifier; }

	typedef InstanceConverter<CascadeClassifier, cv::CascadeClassifier> Converter;

	static const char* getClassName() {
		return "CascadeClassifier";
	}
};

#endif