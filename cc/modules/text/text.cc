#ifdef HAVE_TEXT

#include "text.h"
#include "Workers.h"
#include "Mat.h"

NAN_MODULE_INIT(Text::Init) {
	OCRHMMDecoder::Init(target);
	OCRHMMClassifier::Init(target);
	Nan::SetMethod(target, "loadOCRHMMClassifierNM", LoadOCRHMMClassifierNM);
	Nan::SetMethod(target, "loadOCRHMMClassifierNMAsync", LoadOCRHMMClassifierNMAsync);
#if CV_MINOR_VERSION > 0
	Nan::SetMethod(target, "loadOCRHMMClassifierCNN", LoadOCRHMMClassifierCNN);
	Nan::SetMethod(target, "loadOCRHMMClassifierCNNAsync", LoadOCRHMMClassifierCNNAsync);
	Nan::SetMethod(target, "createOCRHMMTransitionsTable", CreateOCRHMMTransitionsTable);
	Nan::SetMethod(target, "createOCRHMMTransitionsTableAsync", CreateOCRHMMTransitionsTableAsync);
#endif
}

struct Text::LoadOCRHMMClassifierWorker : public SimpleWorker {
public:
	cv::Ptr <cv::text::OCRHMMDecoder::ClassifierCallback> classifier;
	std::string file;

	FF_VAL getReturnValue() {
		FF_OBJ jsClassifier = FF_NEW_INSTANCE(OCRHMMClassifier::constructor);
		FF_UNWRAP(jsClassifier, OCRHMMClassifier)->classifier = classifier;
		return jsClassifier;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return StringConverter::arg(0, &file, info);
	}
};

struct Text::LoadOCRHMMClassifierNMWorker : public LoadOCRHMMClassifierWorker {
	const char* execute() {
		classifier = cv::text::loadOCRHMMClassifierNM(file);
		return "";
	}
};


NAN_METHOD(Text::LoadOCRHMMClassifierNM) {
	LoadOCRHMMClassifierNMWorker worker;
	FF_WORKER_SYNC("Text::LoadOCRHMMClassifierNM", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Text::LoadOCRHMMClassifierNMAsync) {
	LoadOCRHMMClassifierNMWorker worker;
	FF_WORKER_ASYNC("Text::LoadOCRHMMClassifierNMAsync", LoadOCRHMMClassifierWorker, worker);
}

#if CV_MINOR_VERSION > 0

struct Text::LoadOCRHMMClassifierCNNWorker : public LoadOCRHMMClassifierWorker {
	const char* execute() {
		classifier = cv::text::loadOCRHMMClassifierCNN(file);
		return "";
	}
};

NAN_METHOD(Text::LoadOCRHMMClassifierCNN) {
	LoadOCRHMMClassifierCNNWorker worker;
	FF_WORKER_SYNC("Text::LoadOCRHMMClassifierCNN", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Text::LoadOCRHMMClassifierCNNAsync) {
	LoadOCRHMMClassifierCNNWorker worker;
	FF_WORKER_ASYNC("Text::LoadOCRHMMClassifierCNNAsync", LoadOCRHMMClassifierWorker, worker);
}


struct Text::CreateOCRHMMTransitionsTableWorker : public SimpleWorker {
public:
	std::string vocabulary;
	std::vector<std::string> lexicon;

	cv::Mat transition_probabilities_table;

	const char* execute() {
		cv::text::createOCRHMMTransitionsTable(vocabulary, lexicon, transition_probabilities_table);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(transition_probabilities_table);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			StringConverter::arg(0, &vocabulary, info) ||
			StringArrayConverter::arg(1, &lexicon, info)
		);
	}
};

NAN_METHOD(Text::CreateOCRHMMTransitionsTable) {
	CreateOCRHMMTransitionsTableWorker worker;
	FF_WORKER_SYNC("Text::CreateOCRHMMTransitionsTable", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Text::CreateOCRHMMTransitionsTableAsync) {
	CreateOCRHMMTransitionsTableWorker worker;
	FF_WORKER_ASYNC("Text::CreateOCRHMMTransitionsTableAsync", CreateOCRHMMTransitionsTableWorker, worker);
}

#endif

#endif