#include "NativeNodeUtils.h"
#include "opencv2/dnn.hpp"
#include "CatchCvExceptionWorker.h"
#include "Mat.h"

#ifndef __FF_NET_H__
#define __FF_NET_H__

class Net : public Nan::ObjectWrap {
public:
	cv::dnn::Net net;

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::dnn::Net* getNativeObjectPtr() { return &net; }
	cv::dnn::Net getNativeObject() { return net; }

	typedef InstanceConverter<Net, cv::dnn::Net> Converter;

	static const char* getClassName() {
		return "Net";
	}

	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(New);
	static NAN_METHOD(SetInput);
	static NAN_METHOD(SetInputAsync);
	static NAN_METHOD(Forward);
	static NAN_METHOD(ForwardAsync);
  static NAN_METHOD(GetLayerNames);
  static NAN_METHOD(GetLayerNamesAsync);
  static NAN_METHOD(GetUnconnectedOutLayers);
  static NAN_METHOD(GetUnconnectedOutLayersAsync);
};

#endif