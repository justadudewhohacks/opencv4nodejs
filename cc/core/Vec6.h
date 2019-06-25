#include <opencv2/core.hpp>
#include "coreUtils.h"
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_VEC6_H__
#define __FF_VEC6_H__

class Vec6 : public FF::ObjectWrap<Vec6, cv::Vec6d> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "Vec6";
	}

	static NAN_METHOD(New) {
		Vec6* self = new Vec6();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static void Init(v8::Local<v8::FunctionTemplate> ctor) {
		FF_PROTO_SET_MATRIX_OPERATIONS(ctor);
	}

	FF_GETTER_CUSTOM(u, FF::DoubleConverter, self[0]);
	FF_GETTER_CUSTOM(v, FF::DoubleConverter, self[1]);
	FF_GETTER_CUSTOM(w, FF::DoubleConverter, self[2]);
	FF_GETTER_CUSTOM(x, FF::DoubleConverter, self[3]);
	FF_GETTER_CUSTOM(y, FF::DoubleConverter, self[4]);
	FF_GETTER_CUSTOM(z, FF::DoubleConverter, self[5]);

	FF_INIT_VEC6_OPERATIONS();
	static NAN_METHOD(Dot) {
		FF_OPERATOR_RET_SCALAR(&cv::Vec6d::dot, FF_APPLY_CLASS_FUNC, Vec6, "Dot");
	}
	static NAN_METHOD(Norm) {
		info.GetReturnValue().Set(Nan::New(cv::norm(Vec6::unwrapSelf(info))));
	}

	static NAN_METHOD(At) {
		FF::TryCatch tryCatch("Vec6::At");
		FF_ASSERT_INDEX_RANGE(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), 5, "Vec6");
		cv::Vec6d vecSelf = Vec6::unwrapSelf(info);
		info.GetReturnValue().Set(vecSelf[info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value()]);
	}
};

#endif