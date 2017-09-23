#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>

#ifndef __FF_CASCADECLASSIFIER_H__
#define __FF_CASCADECLASSIFIER_H__

class CascadeClassifier : public Nan::ObjectWrap {
public:
	cv::CascadeClassifier classifier;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);
	static NAN_METHOD(DetectMultiScale);
	static NAN_METHOD(DetectMultiScaleWithRejectLevels);

	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif