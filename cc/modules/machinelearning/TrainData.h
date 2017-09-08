#include <nan.h>
#include <opencv2/ml.hpp>
#include "macros.h"

#ifndef __FF_TRAINDATA_H__
#define __FF_TRAINDATA_H__

class TrainData: public Nan::ObjectWrap {
public:
	cv::Ptr<cv::ml::TrainData> trainData;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	// TODO Getters

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif