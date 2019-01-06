#include <opencv2/core.hpp>
#include "coreUtils.h"
#include "NativeNodeUtils.h"
#include "macros.h"

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
	static NAN_METHOD(Dot) {
		FF_OPERATOR_RET_SCALAR(&cv::Vec2d::dot, FF_APPLY_CLASS_FUNC, FF_UNWRAP_VEC2_AND_GET, Vec2);
	}
	static NAN_METHOD(Norm) {
		info.GetReturnValue().Set(Nan::New(cv::norm(FF_UNWRAP_VEC2_AND_GET(info.This()))));
	}

	static NAN_METHOD(At) {
		FF_METHOD_CONTEXT("Vec2::At");
		FF_ASSERT_INDEX_RANGE(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), 1, "Vec2");
		cv::Vec2d vecSelf = FF_UNWRAP_VEC2_AND_GET(info.This());
		info.GetReturnValue().Set(vecSelf[info[0]->ToUint32(Nan::GetCurrentContext()).ToLocalChecked()->Value()]);
	}

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Vec2d* getNativeObjectPtr() { return &vec; }
	cv::Vec2d getNativeObject() { return vec; }

	typedef InstanceConverter<Vec2, cv::Vec2d> Converter;

	static const char* getClassName() {
		return "Vec2";
	}
};

#endif