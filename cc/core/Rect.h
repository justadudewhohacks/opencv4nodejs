#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_RECT_H__
#define __FF_RECT_H__

class Rect : public Nan::ObjectWrap {
public:
	cv::Rect2d rect;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER(Rect, GetX, rect.x);
	static FF_GETTER(Rect, GetY, rect.y);
	static FF_GETTER(Rect, GetWidth, rect.width);
	static FF_GETTER(Rect, GetHeight, rect.height);

	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif