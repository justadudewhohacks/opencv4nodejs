#include <nan.h>
#include <opencv2/core.hpp>
#include "macros.h"
#include "coreUtils.h"

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

	static NAN_METHOD(Norm) {
		info.GetReturnValue().Set(Nan::New(cv::norm(FF_UNWRAP_PT3_AND_GET(info.This()))));
	}

	static NAN_METHOD(At) {
		FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), 2, "Point3");
		cv::Point3d ptSelf = Nan::ObjectWrap::Unwrap<Point3>(info.This())->pt;
		const double coords[] = { ptSelf.x, ptSelf.y, ptSelf.z };
		info.GetReturnValue().Set(coords[info[0]->Int32Value()]);
	}

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif