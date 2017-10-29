#ifdef HAVE_TEXT

#include "OCRHMMClassifier.h"
#include "Workers.h"
#include "Mat.h"

Nan::Persistent<v8::FunctionTemplate> OCRHMMClassifier::constructor;

NAN_MODULE_INIT(OCRHMMClassifier::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(OCRHMMClassifier::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("OCRHMMClassifier"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetPrototypeMethod(ctor, "eval", Eval);
	Nan::SetPrototypeMethod(ctor, "evalAsync", EvalAsync);

	target->Set(FF_NEW_STRING("OCRHMMClassifier"), ctor->GetFunction());
};


struct OCRHMMClassifier::EvalWorker : public SimpleWorker {
public:
	cv::Ptr <cv::text::OCRHMMDecoder::ClassifierCallback> classifier;

	EvalWorker(cv::Ptr <cv::text::OCRHMMDecoder::ClassifierCallback> classifier) {
		this->classifier = classifier;
	}

	cv::Mat img;
	std::vector<int> clazz;
	std::vector<double> confidence;


	const char* execute() {
		classifier->eval(img, clazz, confidence);
		return "";
	}

	FF_VAL getReturnValue() {
		FF_OBJ ret = FF_NEW_OBJ();
		Nan::Set(ret, FF_NEW_STRING("classes"), IntArrayConverter::wrap(clazz));
		Nan::Set(ret, FF_NEW_STRING("confidences"), DoubleArrayConverter::wrap(confidence));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Mat::Converter::arg(0, &img, info);
	}
};

NAN_METHOD(OCRHMMClassifier::Eval) {
	EvalWorker worker(OCRHMMClassifier::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("OCRHMMClassifier::Eval", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(OCRHMMClassifier::EvalAsync) {
	EvalWorker worker(OCRHMMClassifier::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("OCRHMMClassifier::EvalAsync", EvalWorker, worker);
}

#endif