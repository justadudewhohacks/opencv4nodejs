#include <opencv2/core.hpp>
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_SIZE_H__
#define __FF_SIZE_H__

class Size : public FF::ObjectWrap<Size, cv::Size2d> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "Size";
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	FF_ACCESSORS(width, FF::DoubleConverter);
	FF_ACCESSORS(height, FF::DoubleConverter);
};

#endif