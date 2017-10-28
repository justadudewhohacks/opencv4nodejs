#include "Converters.h"

#ifndef __FF_TEXT_H__
#define __FF_TEXT_H__

class Text {
public:
	static NAN_MODULE_INIT(Init);

	struct LoadOCRHMMClassifierWorker;
	struct LoadOCRHMMClassifierCNNWorker;
	struct LoadOCRHMMClassifierNMWorker;
	static NAN_METHOD(LoadOCRHMMClassifierCNN);
	static NAN_METHOD(LoadOCRHMMClassifierCNNAsync);
	static NAN_METHOD(LoadOCRHMMClassifierNM);
	static NAN_METHOD(LoadOCRHMMClassifierNMAsync);

	struct CreateOCRHMMTransitionsTableWorker;
	static NAN_METHOD(CreateOCRHMMTransitionsTable);
	static NAN_METHOD(CreateOCRHMMTransitionsTableAsync);
};

#endif