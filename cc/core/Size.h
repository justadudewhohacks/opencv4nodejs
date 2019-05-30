#include <opencv2/core.hpp>
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_SIZE_H__
#define __FF_SIZE_H__

class Size : public FF::ObjectWrap<Size> {
public:
	typedef cv::Size2d Type;

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "Size";
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static FF_GETTER(Size, GetWidth, self.width);
	static FF_GETTER(Size, GetHeight, self.height);
};

#endif