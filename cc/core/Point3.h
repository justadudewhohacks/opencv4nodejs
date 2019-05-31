#include <opencv2/core.hpp>
#include "coreUtils.h"
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_POINT3_H__
#define __FF_POINT3_H__

class Point3 : public FF::ObjectWrap<Point3, cv::Point3d> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "Point3";
	}

	static void Init(v8::Local<v8::FunctionTemplate> ctor) {
		FF_PROTO_SET_ARITHMETIC_OPERATIONS(ctor);
	}

	static NAN_METHOD(New) {
		Point3* self = new Point3();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	};

	static FF_GETTER(Point3, GetX, self.x);
	static FF_GETTER(Point3, GetY, self.y);
	static FF_GETTER(Point3, GetZ, self.z);

	FF_INIT_ARITHMETIC_OPERATIONS(Point3);

	static NAN_METHOD(Norm) {
		info.GetReturnValue().Set(Nan::New(cv::norm(Point3::unwrapSelf(info))));
	}

	static NAN_METHOD(At) {
		FF_METHOD_CONTEXT("Point3::At");
		FF_ASSERT_INDEX_RANGE(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), 2, "Point3");
		cv::Point3d ptSelf = Point3::unwrapSelf(info);
		const double coords[] = { ptSelf.x, ptSelf.y, ptSelf.z };
		info.GetReturnValue().Set(coords[info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value()]);
	}
};

#endif