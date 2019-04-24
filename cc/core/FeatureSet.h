#include "macros.h"
#include <opencv2/core/cuda.hpp>

#ifndef __FF_FEATURESET_H__
#define __FF_FEATURESET_H__

class FeatureSet: public Nan::ObjectWrap {
public:
	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif