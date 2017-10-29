#ifdef HAVE_TEXT

#include "OCRHMMDecoder.h"
#include "OCRHMMClassifier.h"
#include "Workers.h"
#include "Mat.h"
#include "Rect.h"

Nan::Persistent<v8::FunctionTemplate> OCRHMMDecoder::constructor;

NAN_MODULE_INIT(OCRHMMDecoder::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(OCRHMMDecoder::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("OCRHMMDecoder"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetPrototypeMethod(ctor, "run", Run);
	Nan::SetPrototypeMethod(ctor, "runAsync", RunAsync);
	Nan::SetPrototypeMethod(ctor, "runWithInfo", RunWithInfo);
	Nan::SetPrototypeMethod(ctor, "runWithInfoAsync", RunWithInfoAsync);

	target->Set(FF_NEW_STRING("OCRHMMDecoder"), ctor->GetFunction());
};

struct OCRHMMDecoder::NewWorker : public SimpleWorker {
public:
	cv::Ptr <cv::text::OCRHMMDecoder::ClassifierCallback> classifier;
	std::string vocabulary;
	cv::Mat transition_probabilities_table;
	cv::Mat emission_probabilities_table;
	int mode = cv::text::OCR_DECODER_VITERBI;

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			OCRHMMClassifier::Converter::arg(0, &classifier, info) ||
			StringConverter::arg(1, &vocabulary, info) ||
			Mat::Converter::arg(2, &transition_probabilities_table, info) ||
			Mat::Converter::arg(3, &emission_probabilities_table, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(4, &mode, info)
		);
	}
};

NAN_METHOD(OCRHMMDecoder::New) {
	NewWorker worker;
	FF_TRY_UNWRAP_ARGS("OCRHMMDecoder::New", worker);
	OCRHMMDecoder* self = new OCRHMMDecoder();
	self->decoder = cv::text::OCRHMMDecoder::create(
		worker.classifier,
		worker.vocabulary,
		worker.transition_probabilities_table,
		worker.emission_probabilities_table
#if CV_MINOR_VERSION > 0
		, worker.mode
#endif
	);

	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

struct OCRHMMDecoder::BaseRunWorker : public SimpleWorker {
public:
	cv::Ptr <cv::text::OCRHMMDecoder> decoder;

	BaseRunWorker(cv::Ptr<cv::text::OCRHMMDecoder> decoder) {
		this->decoder = decoder;
	}

	cv::Mat img;
	int min_confidence;
	cv::Mat mask = cv::noArray().getMat();
	int component_level = 0;

	std::string output_text;
};

struct OCRHMMDecoder::RunWorker : public BaseRunWorker {
public:
	RunWorker(cv::Ptr<cv::text::OCRHMMDecoder> decoder) : BaseRunWorker(decoder) {
	}

	const char* execute() {
#if CV_MINOR_VERSION > 0
		if (mask.empty()) {
			output_text = decoder->run(img, min_confidence, component_level);
		}
		else {
			output_text = decoder->run(img, mask, min_confidence, component_level);
		}
#else
		decoder->run(img, output_text);
#endif
		return "";
	}

	FF_VAL getReturnValue() {
		return StringConverter::wrap(output_text);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &img, info) ||
			IntConverter::arg(1, &min_confidence, info)
		);
	}

#if CV_MINOR_VERSION > 0
	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::optArg(2, &mask, info) ||
			IntConverter::optArg(3, &component_level, info)
		);
	}
#endif
};

NAN_METHOD(OCRHMMDecoder::Run) {
	RunWorker worker(OCRHMMDecoder::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("OCRHMMDecoder::Run", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(OCRHMMDecoder::RunAsync) {
	RunWorker worker(OCRHMMDecoder::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("OCRHMMDecoder::RunAsync", RunWorker, worker);
}


struct OCRHMMDecoder::RunWithInfoWorker : public BaseRunWorker {
public:
	RunWithInfoWorker(cv::Ptr<cv::text::OCRHMMDecoder> decoder) : BaseRunWorker(decoder) {
	}

	std::vector<cv::Rect> component_rects;
	std::vector<std::string> component_texts;
	std::vector<float> component_confidences;


	const char* execute() {
#if CV_MINOR_VERSION > 0
		if (mask.empty()) {
			decoder->run(img, output_text, &component_rects, &component_texts, &component_confidences, component_level);
		}
		else {
			decoder->run(img, mask, output_text, &component_rects, &component_texts, &component_confidences, component_level);
		}
#else
		decoder->run(img, output_text, &component_rects, &component_texts, &component_confidences, component_level);
#endif
		return "";
	}

	FF_VAL getReturnValue() {
		FF_OBJ ret = FF_NEW_OBJ();
		Nan::Set(ret, FF_NEW_STRING("outputText"), StringConverter::wrap(output_text));
		Nan::Set(ret, FF_NEW_STRING("rects"), ObjectArrayConverter<Rect, cv::Rect2d, cv::Rect>::wrap(component_rects));
		Nan::Set(ret, FF_NEW_STRING("words"), StringArrayConverter::wrap(component_texts));
		Nan::Set(ret, FF_NEW_STRING("confidences"), FloatArrayConverter::wrap(component_confidences));
		return ret;
	}



	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &img, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::optArg(1, &mask, info) ||
			IntConverter::optArg(2, &component_level, info)
		);
	}
};

NAN_METHOD(OCRHMMDecoder::RunWithInfo) {
	RunWithInfoWorker worker(OCRHMMDecoder::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("OCRHMMDecoder::RunWithInfo", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(OCRHMMDecoder::RunWithInfoAsync) {
	RunWithInfoWorker worker(OCRHMMDecoder::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("OCRHMMDecoder::RunWithInfoAsync", RunWithInfoWorker, worker);
}

#endif