#include "NativeNodeUtils.h"
#include "macros.h"
#include "OCRHMMClassifier.h"
#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include "Rect.h"
#include <opencv2/text.hpp>

#ifndef __FF_OCRHMMDECODER_H__
#define __FF_OCRHMMDECODER_H__

class OCRHMMDecoder : public Nan::ObjectWrap {
public:
	cv::Ptr <cv::text::OCRHMMDecoder> decoder;

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr <cv::text::OCRHMMDecoder>* getNativeObjectPtr() { return &decoder; }
	cv::Ptr <cv::text::OCRHMMDecoder> getNativeObject() { return decoder; }

	typedef InstanceConverter<OCRHMMDecoder, cv::Ptr <cv::text::OCRHMMDecoder>> Converter;

	static const char* getClassName() {
		return "OCRHMMDecoder";
	}

	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(New);
	static NAN_METHOD(Run);
	static NAN_METHOD(RunAsync);
	static NAN_METHOD(RunWithInfo);
	static NAN_METHOD(RunWithInfoAsync);
};

#endif