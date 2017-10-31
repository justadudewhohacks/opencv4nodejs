#include "VideoWriter.h"
#include "Workers.h"

Nan::Persistent<v8::FunctionTemplate> VideoWriter::constructor;

NAN_MODULE_INIT(VideoWriter::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(VideoWriter::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF_NEW_STRING("VideoWriter"));
	Nan::SetMethod(ctor, "fourcc", Fourcc);
	Nan::SetPrototypeMethod(ctor, "write", Write);
	Nan::SetPrototypeMethod(ctor, "writeAsync", WriteAsync);
	Nan::SetPrototypeMethod(ctor, "get", Get);
	Nan::SetPrototypeMethod(ctor, "set", Set);
	Nan::SetPrototypeMethod(ctor, "release", Release);
  target->Set(FF_NEW_STRING("VideoWriter"), ctor->GetFunction());
};

struct VideoWriter::NewWorker : SimpleWorker {
public:
	std::string fileName;
	int fourccCode;
	double fps;
	cv::Size2d frameSize;
	bool isColor = true;

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			StringConverter::arg(0, &fileName, info) ||
			IntConverter::arg(1, &fourccCode, info) ||
			DoubleConverter::arg(2, &fps, info) ||
			Size::Converter::arg(3, &frameSize, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return BoolConverter::optArg(4, &isColor, info);
	}
};

NAN_METHOD(VideoWriter::New) {
	NewWorker worker;
	FF_TRY_UNWRAP_ARGS("VideoWriter::New", worker);

	VideoWriter* self = new VideoWriter();
	self->writer.open(worker.fileName, worker.fourccCode, worker.fps, (cv::Size)worker.frameSize, worker.isColor);
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
}

struct VideoWriter::FourccWorker : SimpleWorker {
public:
	std::string fourcc;

	int code;

	const char* execute() {
		code = cv::VideoWriter::fourcc(fourcc.at(0), fourcc.at(1), fourcc.at(2), fourcc.at(3));
		return "";
	}

	FF_VAL getReturnValue() {
		return IntConverter::wrap(code);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return StringConverter::arg(0, &fourcc, info);
	}
};

NAN_METHOD(VideoWriter::Fourcc) {
	FourccWorker worker;
	FF_TRY_UNWRAP_ARGS("VideoWriter::Fourcc", worker);
	if (worker.fourcc.size() != 4) {
		FF_METHOD_CONTEXT("VideoWriter::Fourcc");
		FF_THROW("expected charCode to be a string of 4 characters");
	}
	worker.execute();
	FF_RETURN(worker.getReturnValue());
}

struct VideoWriter::WriteWorker : SimpleWorker {
public:
	cv::VideoWriter writer;
	WriteWorker(cv::VideoWriter writer) {
		this->writer = writer;
	}

	cv::Mat frame;

	const char* execute() {
		writer.write(frame);
		return "";
	}

	FF_VAL getReturnValue() {
		return BoolConverter::wrap(true);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Mat::Converter::arg(0, &frame, info);
	}
};

NAN_METHOD(VideoWriter::Write) {
	WriteWorker worker(VideoWriter::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("VideoWriter::Write", worker);
}

NAN_METHOD(VideoWriter::WriteAsync) {
	WriteWorker worker(VideoWriter::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("VideoWriter::WriteAsync", WriteWorker, worker);
}

NAN_METHOD(VideoWriter::Get) {
	FF_METHOD_CONTEXT("VideoWriter::Get");
	FF_ARG_INT(0, int prop);
	FF_RETURN(FF_UNWRAP(info.This(), VideoWriter)->writer.get(prop));
}

NAN_METHOD(VideoWriter::Set) {
	FF_METHOD_CONTEXT("VideoWriter::Set");
	FF_ARG_INT(0, int prop);
	FF_ARG_NUMBER(1, double value);
	FF_UNWRAP(info.This(), VideoWriter)->writer.set(prop, value);
}

NAN_METHOD(VideoWriter::Release) {
	FF_UNWRAP(info.This(), VideoWriter)->writer.release();
}