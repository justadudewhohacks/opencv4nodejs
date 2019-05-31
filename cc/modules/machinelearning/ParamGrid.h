#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/ml.hpp>

#ifndef __FF_PARAMGRID_H__
#define __FF_PARAMGRID_H__

class ParamGrid: public FF::ObjectWrap<ParamGrid, cv::ml::ParamGrid>{
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "ParamGrid";
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static FF_GETTER(ParamGrid, minVal, self.minVal);
	static FF_GETTER(ParamGrid, maxVal, self.maxVal);
	static FF_GETTER(ParamGrid, logStep, self.logStep);
};

#endif