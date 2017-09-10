#include "macros.h"
#include <opencv2/core.hpp>

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
};

#endif