#include "Converters.h"
#include "opencv2/dnn.hpp"

#ifndef __FF_NET_H__
#define __FF_NET_H__

class Net : public Nan::ObjectWrap {
public:
	cv::dnn::Net net;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	struct SetInputWorker;
	static NAN_METHOD(SetInput);
	static NAN_METHOD(SetInputAsync);

	struct ForwardWorker;
	static NAN_METHOD(Forward);
	static NAN_METHOD(ForwardAsync);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::dnn::Net* getNativeObjectPtr() { return &net; }
	cv::dnn::Net getNativeObject() { return net; }

	typedef InstanceConverter<Net, cv::dnn::Net> Converter;

	static const char* getClassName() {
		return "Net";
	}
};

#endif