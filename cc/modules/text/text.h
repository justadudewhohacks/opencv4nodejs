#include "NativeNodeUtils.h"
#include "macros.h"
#include "OCRHMMClassifier.h"
#include "OCRHMMDecoder.h"
#include "CatchCvExceptionWorker.h"
#include "Mat.h"

#ifndef __FF_TEXT_H__
#define __FF_TEXT_H__

class Text {
public:
	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(LoadOCRHMMClassifierNM);
	static NAN_METHOD(LoadOCRHMMClassifierNMAsync);

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
	static NAN_METHOD(LoadOCRHMMClassifierCNN);
	static NAN_METHOD(LoadOCRHMMClassifierCNNAsync);

	static NAN_METHOD(CreateOCRHMMTransitionsTable);
	static NAN_METHOD(CreateOCRHMMTransitionsTableAsync);
#endif
};

#endif
