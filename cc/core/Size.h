#include <opencv2/core.hpp>
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_SIZE_H__
#define __FF_SIZE_H__

class Size : public Nan::ObjectWrap {
public:
	cv::Size2d size;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER(Size, GetWidth, size.width);
	static FF_GETTER(Size, GetHeight, size.height);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Size2d* getNativeObjectPtr() { return &size; }
	cv::Size2d getNativeObject() { return size; }

	typedef InstanceConverter<Size, cv::Size2d> Converter;

	static const char* getClassName() {
		return "Size";
	}
};

#endif