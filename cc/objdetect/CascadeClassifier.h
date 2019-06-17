#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include "Mat.h"
#include "Rect.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_CASCADECLASSIFIER_H__
#define __FF_CASCADECLASSIFIER_H__

class CascadeClassifier : public FF::ObjectWrap<CascadeClassifier, cv::CascadeClassifier> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "CascadeClassifier";
	}

	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(New);
	static NAN_METHOD(DetectMultiScale);
	static NAN_METHOD(DetectMultiScaleAsync);
	static NAN_METHOD(DetectMultiScaleGpu);
	static NAN_METHOD(DetectMultiScaleWithRejectLevels);
	static NAN_METHOD(DetectMultiScaleWithRejectLevelsAsync);
	static NAN_METHOD(DetectMultiScaleWithRejectLevelsGpu);
};

#endif