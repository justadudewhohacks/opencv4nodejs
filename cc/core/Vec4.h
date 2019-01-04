#include <opencv2/core.hpp>
#include "coreUtils.h"
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_VEC4_H__
#define __FF_VEC4_H__

class Vec4 : public Nan::ObjectWrap {
public:
	cv::Vec4d vec;

	static NAN_METHOD(New) {
		Vec4* self = new Vec4();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static void Init(v8::Local<v8::FunctionTemplate> ctor) {
		FF_PROTO_SET_MATRIX_OPERATIONS(ctor);
	}

	static FF_GETTER(Vec4, GetW, vec[0]);
	static FF_GETTER(Vec4, GetX, vec[1]);
	static FF_GETTER(Vec4, GetY, vec[2]);
	static FF_GETTER(Vec4, GetZ, vec[3]);

	FF_INIT_VEC4_OPERATIONS();
	static NAN_METHOD(Dot) {
		FF_OPERATOR_RET_SCALAR(&cv::Vec4d::dot, FF_APPLY_CLASS_FUNC, FF_UNWRAP_VEC4_AND_GET, Vec4);
	}
	static NAN_METHOD(Norm) {
		info.GetReturnValue().Set(Nan::New(cv::norm(FF_UNWRAP_VEC4_AND_GET(info.This()))));
	}

	static NAN_METHOD(At) {
		FF_METHOD_CONTEXT("Vec4::At");
		FF_ASSERT_INDEX_RANGE(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), 3, "Vec4");
		cv::Vec4d vecSelf = FF_UNWRAP_VEC4_AND_GET(info.This());
		info.GetReturnValue().Set(vecSelf[info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value()]);
	}

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Vec4d* getNativeObjectPtr() { return &vec; }
	cv::Vec4d getNativeObject() { return vec; }

	typedef InstanceConverter<Vec4, cv::Vec4d> Converter;

	static const char* getClassName() {
		return "Vec4";
	}
};

#endif