#include <nan.h>
#include <opencv2/core.hpp>
#include "macros.h"

#ifndef __FF_POINT2_H__
#define __FF_POINT2_H__

class Point2 : public Nan::ObjectWrap {
public:
	cv::Point2d pt;

	static NAN_METHOD(New) {
		Point2* self = new Point2();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	};

	static FF_GETTER(Point2, GetX, pt.x);
	static FF_GETTER(Point2, GetY, pt.y);

  static Nan::Persistent<v8::FunctionTemplate> Point2::constructor;
};

#endif