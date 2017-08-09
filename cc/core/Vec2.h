#include <nan.h>
#include <opencv2/core.hpp>
#include "macros.h"
#include "coreUtils.h"

#ifndef __FF_VEC2_H__
#define __FF_VEC2_H__

class Vec2 : public Nan::ObjectWrap {
public:
	cv::Vec2d vec;

	static NAN_METHOD(New) {
		Vec2* self = new Vec2();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static void Init(v8::Local<v8::FunctionTemplate> ctor) {
		FF_PROTO_SET_MATRIX_OPERATIONS(ctor);
	}

	static FF_GETTER(Vec2, GetX, vec[0]);
	static FF_GETTER(Vec2, GetY, vec[1]);

	FF_INIT_VEC2_OPERATIONS();

	static NAN_METHOD(At) {
		FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), 1);
		cv::Vec2d vecSelf = Nan::ObjectWrap::Unwrap<Vec2>(info.This())->vec;
		info.GetReturnValue().Set(vecSelf[info[0]->Uint32Value()]);
	}

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif