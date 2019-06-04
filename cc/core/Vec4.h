#include <opencv2/core.hpp>
#include "coreUtils.h"
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_VEC4_H__
#define __FF_VEC4_H__

class Vec4 : public FF::ObjectWrap<Vec4, cv::Vec4d> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "Vec4";
	}

	static NAN_METHOD(New) {
		Vec4* self = new Vec4();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static void Init(v8::Local<v8::FunctionTemplate> ctor) {
		FF_PROTO_SET_MATRIX_OPERATIONS(ctor);
	}

	FF_GETTER_CUSTOM(w, FF::DoubleConverter, self[0]);
	FF_GETTER_CUSTOM(x, FF::DoubleConverter, self[1]);
	FF_GETTER_CUSTOM(y, FF::DoubleConverter, self[2]);
	FF_GETTER_CUSTOM(z, FF::DoubleConverter, self[3]);

	FF_INIT_VEC4_OPERATIONS();
	static NAN_METHOD(Dot) {
		FF_OPERATOR_RET_SCALAR(&cv::Vec4d::dot, FF_APPLY_CLASS_FUNC, Vec4, "Dot");
	}
	static NAN_METHOD(Norm) {
		info.GetReturnValue().Set(Nan::New(cv::norm(Vec4::unwrapSelf(info))));
	}

	static NAN_METHOD(At) {
		FF::TryCatch tryCatch("Vec4::At");
		FF_ASSERT_INDEX_RANGE(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), 3, "Vec4");
		cv::Vec4d vecSelf = Vec4::unwrapSelf(info);
		info.GetReturnValue().Set(vecSelf[info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value()]);
	}
};

#endif