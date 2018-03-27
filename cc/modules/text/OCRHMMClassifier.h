#include "Converters.h"
#include "macros.h"
#include <opencv2/text.hpp>

#ifndef __FF_OCRHMMCLASSIFIER_H__
#define __FF_OCRHMMCLASSIFIER_H__

class OCRHMMClassifier : public Nan::ObjectWrap {
public:
	cv::Ptr <cv::text::OCRHMMDecoder::ClassifierCallback> classifier;

	static NAN_METHOD(New) {
		OCRHMMClassifier* self = new OCRHMMClassifier();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static NAN_MODULE_INIT(Init);

	struct EvalWorker;
	static NAN_METHOD(Eval);
	static NAN_METHOD(EvalAsync);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr <cv::text::OCRHMMDecoder::ClassifierCallback>* getNativeObjectPtr() { return &classifier; }
	cv::Ptr <cv::text::OCRHMMDecoder::ClassifierCallback> getNativeObject() { return classifier; }

	typedef InstanceConverter<OCRHMMClassifier, cv::Ptr <cv::text::OCRHMMDecoder::ClassifierCallback>> Converter;

	static const char* getClassName() {
		return "OCRHMMClassifier";
	}
};

#endif