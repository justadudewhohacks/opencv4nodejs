#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_COREUTILS_H__
#define __FF_COREUTILS_H__

#define FF_ASSERT_INDEX_RANGE(idx, max, what)																										\
	if (idx < 0 || max < idx) {																																		\
		return tryCatch.throwError("Index out of bounds: " + std::string(what) + " at index " + std::to_string(idx));	\
	}				

#define FF_APPLY_FUNC(func, arg0, arg1, ret) func(arg0, arg1, ret);
#define FF_APPLY_CLASS_FUNC(func, arg0, arg1, ret) ret = ((arg0).*(func))(arg1);
#define FF_APPLY_OPERATOR(op, arg0, arg1, ret) ret = arg0 op arg1;


/* TODO fix non scalar matrix multiplication, division */

#define FF_SELF_OPERATOR(func)							\
	v8::Local<v8::Object> jsObj = FF::newInstance(Nan::New(constructor));	\
	func(unwrapSelf(info), unwrapClassPtrUnchecked(jsObj)->self);			\
	return info.GetReturnValue().Set(jsObj);					

#define FF_SCALAR_OPERATOR(func, applyFunc, clazz, methodName) \
	FF::TryCatch tryCatch(methodName); \
	if (!info[0]->IsNumber()) {	\
		return tryCatch.throwError("expected arg to be a Scalar"); \
	}																																\
	v8::Local<v8::Object> jsObj = FF::newInstance(Nan::New(constructor));							\
	applyFunc(																											\
		func,																													\
		unwrapSelf(info),																				\
		info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value(),																				\
		unwrapClassPtrUnchecked(jsObj)->self																							\
	);																															\
	return info.GetReturnValue().Set(jsObj);																																																										

#define FF_OPERATOR(func, applyFunc, clazz, methodName) \
	FF::TryCatch tryCatch(methodName); \
	if (!Nan::New(constructor)->HasInstance(info[0])) { \
			return tryCatch.throwError("expected arg to be an instance of " + std::string(#clazz)); \
	} \
	v8::Local<v8::Object> jsObj = FF::newInstance(Nan::New(constructor));															\
	applyFunc(																																			\
		func,																																					\
		unwrapSelf(info),																												\
		unwrapClassPtrUnchecked(info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked())->self,																								\
		unwrapClassPtrUnchecked(jsObj)->self																																\
	);																																							\
	return info.GetReturnValue().Set(jsObj);

#define FF_OPERATOR_RET_SCALAR(func, applyFunc, clazz, methodName) \
	FF::TryCatch tryCatch(methodName); \
	if (!Nan::New(constructor)->HasInstance(info[0])) { \
			return tryCatch.throwError("expected arg to be an instance of " + std::string(#clazz)); \
	} \
	double ret;																																			\
	applyFunc(																																			\
		func,																																					\
		unwrapSelf(info),																												\
		unwrapClassPtrUnchecked(info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked())->self,																								\
		ret																																						\
	);																																							\
	return info.GetReturnValue().Set(ret);

#define FF_PROTO_SET_ARITHMETIC_OPERATIONS(ctor)						\
	Nan::SetPrototypeMethod(ctor, "add", Add);								\
	Nan::SetPrototypeMethod(ctor, "sub", Sub);								\
	Nan::SetPrototypeMethod(ctor, "mul", Mul);								\
	Nan::SetPrototypeMethod(ctor, "div", Div);								\

#define FF_PROTO_SET_MATRIX_OPERATIONS(ctor)								\
	FF_PROTO_SET_ARITHMETIC_OPERATIONS(ctor)									\
	Nan::SetPrototypeMethod(ctor, "hMul", HMul);							\
	Nan::SetPrototypeMethod(ctor, "hDiv", HDiv);							\
	Nan::SetPrototypeMethod(ctor, "absdiff", Absdiff);				\
	Nan::SetPrototypeMethod(ctor, "exp", Exp);								\
	Nan::SetPrototypeMethod(ctor, "log", Log);								\
	Nan::SetPrototypeMethod(ctor, "sqrt", Sqrt);							\
	Nan::SetPrototypeMethod(ctor, "dot", Dot);

#define FF_PROTO_SET_MAT_OPERATIONS(ctor)										\
	FF_PROTO_SET_MATRIX_OPERATIONS(ctor)											\
	Nan::SetPrototypeMethod(ctor, "and", And);								\
	Nan::SetPrototypeMethod(ctor, "or", Or);									\
	Nan::SetPrototypeMethod(ctor, "bitwiseAnd", BitwiseAnd);	\
	Nan::SetPrototypeMethod(ctor, "bitwiseNot", BitwiseNot);	\
	Nan::SetPrototypeMethod(ctor, "bitwiseOr", BitwiseOr);		\
	Nan::SetPrototypeMethod(ctor, "bitwiseXor", BitwiseXor);	\
	Nan::SetPrototypeMethod(ctor, "abs", Abs);								\
	Nan::SetPrototypeMethod(ctor, "transpose", Transpose);		\
	Nan::SetPrototypeMethod(ctor, "inv", Inv);		\
	Nan::SetPrototypeMethod(ctor, "determinant", Determinant);\
	Nan::SetPrototypeMethod(ctor, "matMul", MatMul);

#define FF_INIT_ARITHMETIC_OPERATIONS(clazz)					\
	static NAN_METHOD(Add) {																			\
		FF_OPERATOR(+, FF_APPLY_OPERATOR, clazz, "Add");				\
	}																															\
	static NAN_METHOD(Sub) {																			\
		FF_OPERATOR(-, FF_APPLY_OPERATOR, clazz, "Sub");				\
	}																															\
	static NAN_METHOD(Mul) {																			\
		FF_SCALAR_OPERATOR(*, FF_APPLY_OPERATOR, clazz, "Mul");	\
	}																															\
	static NAN_METHOD(Div) {																			\
		FF_SCALAR_OPERATOR(/, FF_APPLY_OPERATOR, clazz, "Div");	\
	}																															\

#define FF_INIT_MATRIX_OPERATIONS(clazz)											\
	FF_INIT_ARITHMETIC_OPERATIONS(clazz)												\
	static NAN_METHOD(HMul) {																							\
		FF_OPERATOR(cv::multiply, FF_APPLY_FUNC, clazz, "HMul");					\
	}																																			\
	static NAN_METHOD(HDiv) {																							\
		FF_OPERATOR(cv::divide, FF_APPLY_FUNC, clazz, "HDiv");						\
	}																																			\
	static NAN_METHOD(Absdiff) {																					\
		FF_OPERATOR(cv::absdiff, FF_APPLY_FUNC, clazz, "Absdiff");					\
	}																																			\
	static NAN_METHOD(Exp) {																							\
		FF_SELF_OPERATOR(cv::exp);																\
	}																																			\
	static NAN_METHOD(Log) {																							\
		FF_SELF_OPERATOR(cv::log);																\
	}																																		\
	static NAN_METHOD(Sqrt) {																							\
		FF_SELF_OPERATOR(cv::sqrt);															\
	}																																			\

#define FF_INIT_MAT_OPERATIONS()																						\
	FF_INIT_MATRIX_OPERATIONS(Mat);										\
	static NAN_METHOD(And) {																									\
		FF_OPERATOR(&, FF_APPLY_OPERATOR, Mat, "And");					\
	}																																					\
	static NAN_METHOD(Or) {																										\
		FF_OPERATOR(|, FF_APPLY_OPERATOR, Mat, "Or");					\
	}																																					\
	static NAN_METHOD(BitwiseAnd) {																						\
		FF_OPERATOR(cv::bitwise_and, FF_APPLY_FUNC, Mat, "BitwiseAnd");\
	}																																					\
	static NAN_METHOD(BitwiseNot) {																						\
		FF_SELF_OPERATOR(cv::bitwise_not);								\
	}																																					\
	static NAN_METHOD(BitwiseOr) {																						\
		FF_OPERATOR(cv::bitwise_or, FF_APPLY_FUNC, Mat, "BitwiseOr");	\
	}																																					\
	static NAN_METHOD(BitwiseXor) {																						\
		FF_OPERATOR(cv::bitwise_xor, FF_APPLY_FUNC, Mat, "BitwiseXor");\
	}																																					\
	static NAN_METHOD(Abs) {																									\
		return info.GetReturnValue().Set(Converter::wrap(cv::abs(unwrapSelf(info))));\
	}																																					\
	static NAN_METHOD(Determinant) {																					\
		return info.GetReturnValue().Set(																				\
			cv::determinant(Mat::unwrapSelf(info)));									\
	}																																					\
	static NAN_METHOD(Transpose) {																						\
		FF_SELF_OPERATOR(cv::transpose);									\
	}																																					\
	static NAN_METHOD(Inv) {																						\
		FF_SELF_OPERATOR(cv::invert);									\
	}																																					\
	static NAN_METHOD(MatMul) {																								\
		FF_OPERATOR(*, FF_APPLY_OPERATOR, Mat, "MatMul");					\
	}																																					

#define FF_INIT_VEC2_OPERATIONS()	FF_INIT_MATRIX_OPERATIONS(Vec2);
#define FF_INIT_VEC3_OPERATIONS()	FF_INIT_MATRIX_OPERATIONS(Vec3);
#define FF_INIT_VEC4_OPERATIONS()	FF_INIT_MATRIX_OPERATIONS(Vec4);
#define FF_INIT_VEC6_OPERATIONS()	FF_INIT_MATRIX_OPERATIONS(Vec6);

namespace FF {
	template<int cn>
	static v8::Local<v8::Array> vecToJsArr(cv::Vec<double, cn> vec) {
		v8::Local<v8::Array> jsVec = Nan::New<v8::Array>(cn);
		for (int i = 0; i < cn; i++) Nan::Set(jsVec, i, Nan::New(vec[i]));
		return jsVec;
	}
}

#endif