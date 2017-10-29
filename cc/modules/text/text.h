#include "Converters.h"
#include "OCRHMMClassifier.h"
#include "OCRHMMDecoder.h"

#ifndef __FF_TEXT_H__
#define __FF_TEXT_H__

class Text {
public:
	static NAN_MODULE_INIT(Init);

	struct LoadOCRHMMClassifierWorker;
	struct LoadOCRHMMClassifierNMWorker;
	static NAN_METHOD(LoadOCRHMMClassifierNM);
	static NAN_METHOD(LoadOCRHMMClassifierNMAsync);

#if CV_MINOR_VERSION > 0
	struct LoadOCRHMMClassifierCNNWorker;
	static NAN_METHOD(LoadOCRHMMClassifierCNN);
	static NAN_METHOD(LoadOCRHMMClassifierCNNAsync);

	struct CreateOCRHMMTransitionsTableWorker;
	static NAN_METHOD(CreateOCRHMMTransitionsTable);
	static NAN_METHOD(CreateOCRHMMTransitionsTableAsync);
#endif
};

#endif