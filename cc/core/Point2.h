#include <opencv2/core.hpp>
#include "coreUtils.h"
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_POINT2_H__
#define __FF_POINT2_H__

class Point2 : public FF::ObjectWrap<Point2, cv::Point2d> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "Point2";
	}

	static void Init(v8::Local<v8::FunctionTemplate> ctor) {
		FF_PROTO_SET_ARITHMETIC_OPERATIONS(ctor);
	}

	static NAN_METHOD(New) {
		Point2* self = new Point2();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	};

	static FF_GETTER(Point2, GetX, self.x);
	static FF_GETTER(Point2, GetY, self.y);

	FF_INIT_ARITHMETIC_OPERATIONS(Point2);

	static NAN_METHOD(Norm) {
		info.GetReturnValue().Set(Nan::New(cv::norm(Point2::Converter::unwrap(info.This()))));
	}

	static NAN_METHOD(At) {
		FF_METHOD_CONTEXT("Point2::At");
		FF_ASSERT_INDEX_RANGE(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), 1, "Point2");
		cv::Point2d ptSelf = Point2::Converter::unwrap(info.This());
		const double coords[] = { ptSelf.x, ptSelf.y };
		info.GetReturnValue().Set(coords[info[0]->ToUint32(Nan::GetCurrentContext()).ToLocalChecked()->Value()]);
	}
};

#endif