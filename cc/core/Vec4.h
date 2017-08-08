#include <nan.h>
#include <opencv2/core.hpp>
#include "macros.h"
#include "coreUtils.h"

#ifndef __FF_VEC4_H__
#define __FF_VEC4_H__

class Vec4 : public Nan::ObjectWrap {
public:
	cv::Vec4d vec;

	static NAN_METHOD(New) {
		Vec4* self = new Vec4();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	};

	static FF_GETTER(Vec4, GetW, vec[0]);
	static FF_GETTER(Vec4, GetX, vec[1]);
	static FF_GETTER(Vec4, GetY, vec[2]);
	static FF_GETTER(Vec4, GetZ, vec[3]);

	static NAN_METHOD(At) {
		FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), 3);
		cv::Vec4d vecSelf = Nan::ObjectWrap::Unwrap<Vec4>(info.This())->vec;
		info.GetReturnValue().Set(vecSelf[info[0]->Int32Value()]);
	}

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif