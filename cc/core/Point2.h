#include <opencv2/core.hpp>
#include "coreUtils.h"
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_POINT2_H__
#define __FF_POINT2_H__

class Point2 : public Nan::ObjectWrap {
public:
	cv::Point2d pt;

	static void Init(v8::Local<v8::FunctionTemplate> ctor) {
		FF_PROTO_SET_ARITHMETIC_OPERATIONS(ctor);
	}

	static NAN_METHOD(New) {
		Point2* self = new Point2();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	};

	static FF_GETTER(Point2, GetX, pt.x);
	static FF_GETTER(Point2, GetY, pt.y);

	FF_INIT_ARITHMETIC_OPERATIONS(Point2, FF_UNWRAP_PT2_AND_GET);

	static NAN_METHOD(Norm) {
		info.GetReturnValue().Set(Nan::New(cv::norm(FF_UNWRAP_PT2_AND_GET(info.This()))));
	}

	static NAN_METHOD(At) {
		FF_METHOD_CONTEXT("Point2::At");
		FF_ASSERT_INDEX_RANGE(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), 1, "Point2");
		cv::Point2d ptSelf = FF_UNWRAP_PT2_AND_GET(info.This());
		const double coords[] = { ptSelf.x, ptSelf.y };
		info.GetReturnValue().Set(coords[info[0]->ToUint32(Nan::GetCurrentContext()).ToLocalChecked()->Value()]);
	}

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Point2d* getNativeObjectPtr() { return &pt; }
	cv::Point2d getNativeObject() { return pt; }

	typedef InstanceConverter<Point2, cv::Point2d> Converter;

	static const char* getClassName() {
		return "Point2";
	}
};

#endif