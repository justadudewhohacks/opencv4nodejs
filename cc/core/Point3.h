#include <nan.h>
#include <opencv2/core.hpp>
#include "macros.h"

#ifndef __FF_POINT3_H__
#define __FF_POINT3_H__

class Point3 : public Nan::ObjectWrap {
public:
	cv::Point3d pt;

	static NAN_METHOD(New) {
		Point3* self = new Point3();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	};

	static FF_GETTER(Point3, GetX, pt.x);
	static FF_GETTER(Point3, GetY, pt.y);
	static FF_GETTER(Point3, GetZ, pt.z);

  static Nan::Persistent<v8::FunctionTemplate> Point3::constructor;
};

#endif