#include "Converters.h"
#include <opencv2/text.hpp>

#ifndef __FF_OCRHMMDECODER_H__
#define __FF_OCRHMMDECODER_H__

class OCRHMMDecoder : public Nan::ObjectWrap {
public:
	cv::Ptr <cv::text::OCRHMMDecoder> decoder;

	static NAN_MODULE_INIT(Init);

	struct NewWorker;
	static NAN_METHOD(New);

	struct BaseRunWorker;
	struct RunWorker;
	struct RunWithInfoWorker;
	static NAN_METHOD(Run);
	static NAN_METHOD(RunAsync);
	static NAN_METHOD(RunWithInfo);
	static NAN_METHOD(RunWithInfoAsync);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr <cv::text::OCRHMMDecoder>* getNativeObjectPtr() { return &decoder; }
	cv::Ptr <cv::text::OCRHMMDecoder> getNativeObject() { return decoder; }

	typedef InstanceConverter<OCRHMMDecoder, cv::Ptr <cv::text::OCRHMMDecoder>> Converter;

	static const char* getClassName() {
		return "OCRHMMDecoder";
	}
};

#endif