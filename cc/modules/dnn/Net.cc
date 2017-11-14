#include "opencv2/core.hpp"

#if CV_VERSION_MINOR > 2

// cv 3.3+ should have dnn by default
//#ifdef HAVE_DNN

#include "Net.h"
#include "Workers.h"
#include "Mat.h"

Nan::Persistent<v8::FunctionTemplate> Net::constructor;

NAN_MODULE_INIT(Net::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Net::New);
	Net::constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("Net").ToLocalChecked());

	Nan::SetPrototypeMethod(ctor, "setInput", SetInput);
	Nan::SetPrototypeMethod(ctor, "setInputAsync", SetInputAsync);
	Nan::SetPrototypeMethod(ctor, "forward", Forward);
	Nan::SetPrototypeMethod(ctor, "forwardAsync", ForwardAsync);

	target->Set(Nan::New("Net").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Net::New) {
	Net* self = new Net();
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

struct Net::SetInputWorker : public SimpleWorker {
public:
	cv::dnn::Net self;
	SetInputWorker(cv::dnn::Net self) {
		this->self = self;
	}

	cv::Mat blob;
	std::string name = "";


	const char* execute() {
		self.setInput(blob, name);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &blob, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			StringConverter::optArg(1, &name, info)
		);
	}
};

NAN_METHOD(Net::SetInput) {
	SetInputWorker worker(Net::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Net::SetInput", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Net::SetInputAsync) {
	SetInputWorker worker(Net::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Net::SetInputAsync", SetInputWorker, worker);
}


struct Net::ForwardWorker : public SimpleWorker {
public:
	cv::dnn::Net self;
	ForwardWorker(cv::dnn::Net self) {
		this->self = self;
	}

	std::string outputName = "";

	cv::Mat returnValue;

	const char* execute() {
		returnValue = self.forward(outputName);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(returnValue);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			StringConverter::optArg(0, &outputName, info)
		);
	}
};

NAN_METHOD(Net::Forward) {
	ForwardWorker worker(Net::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Net::Forward", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Net::ForwardAsync) {
	ForwardWorker worker(Net::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Net::ForwardAsync", ForwardWorker, worker);
}

//#endif

#endif