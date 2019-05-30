#include <opencv2/core.hpp>
#include "coreUtils.h"
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_VEC3_H__
#define __FF_VEC3_H__

class Vec3 : public FF::ObjectWrap<Vec3, cv::Vec3d> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "Vec3";
	}

	static NAN_METHOD(New) {
		Vec3* self = new Vec3();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static void Init(v8::Local<v8::FunctionTemplate> ctor) {
		FF_PROTO_SET_MATRIX_OPERATIONS(ctor);
	}

	static FF_GETTER(Vec3, GetX, self[0]);
	static FF_GETTER(Vec3, GetY, self[1]);
	static FF_GETTER(Vec3, GetZ, self[2]);

	FF_INIT_VEC3_OPERATIONS();
	static NAN_METHOD(Dot) {
		FF_OPERATOR_RET_SCALAR(&cv::Vec3d::dot, FF_APPLY_CLASS_FUNC, Vec3);
	}
	static NAN_METHOD(Cross) {
		FF_OPERATOR(&cv::Vec3d::cross, FF_APPLY_CLASS_FUNC, Vec3);
	}
	static NAN_METHOD(Norm) {
		info.GetReturnValue().Set(Nan::New(cv::norm(Vec3::Converter::unwrap(info.This()))));
	}

	static NAN_METHOD(At) {
		FF_METHOD_CONTEXT("Vec3::At");
		FF_ASSERT_INDEX_RANGE(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), 2, "Vec3");
		cv::Vec3d vecSelf = Vec3::Converter::unwrap(info.This());
		info.GetReturnValue().Set(vecSelf[info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value()]);
	}
};

#endif