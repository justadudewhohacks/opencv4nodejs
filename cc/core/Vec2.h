#include <opencv2/core.hpp>
#include "coreUtils.h"
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_VEC2_H__
#define __FF_VEC2_H__

class Vec2 : public FF::ObjectWrap<Vec2, cv::Vec2d> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "Vec2";
	}

	static NAN_METHOD(New) {
		Vec2* self = new Vec2();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static void Init(v8::Local<v8::FunctionTemplate> ctor) {
		FF_PROTO_SET_MATRIX_OPERATIONS(ctor);
	}

	FF_GETTER_CUSTOM(x, FF::DoubleConverter, self[0]);
	FF_GETTER_CUSTOM(y, FF::DoubleConverter, self[1]);

	FF_INIT_VEC2_OPERATIONS();
	static NAN_METHOD(Dot) {
		FF_OPERATOR_RET_SCALAR(&cv::Vec2d::dot, FF_APPLY_CLASS_FUNC, Vec2, "Dot");
	}
	static NAN_METHOD(Norm) {
		info.GetReturnValue().Set(Nan::New(cv::norm(Vec2::unwrapSelf(info))));
	}

	static NAN_METHOD(At) {
		FF::TryCatch tryCatch("Vec2::At");
		FF_ASSERT_INDEX_RANGE(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), 1, "Vec2");
		cv::Vec2d vecSelf = Vec2::unwrapSelf(info);
		info.GetReturnValue().Set(vecSelf[info[0]->ToUint32(Nan::GetCurrentContext()).ToLocalChecked()->Value()]);
	}
};

#endif