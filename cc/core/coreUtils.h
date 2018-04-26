#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_COREUTILS_H__
#define __FF_COREUTILS_H__

#define FF_ASSERT_INDEX_RANGE(idx, max, what)																										\
	if (idx < 0 || max < idx) {																																		\
		FF_THROW("Index out of bounds: " + std::string(what) + " at index " + std::to_string(idx));	\
	}				

#define FF_APPLY_FUNC(func, arg0, arg1, ret) func(arg0, arg1, ret);
#define FF_APPLY_CLASS_FUNC(func, arg0, arg1, ret) ret = ((arg0).*(func))(arg1);
#define FF_APPLY_OPERATOR(op, arg0, arg1, ret) ret = arg0 op arg1;


/* TODO fix non scalar matrix multiplication, division */

#define FF_ERR_WHERE(func, clazz) std::string(#clazz) + "  " + std::string(#func) + " : "

#define FF_SELF_OPERATOR_RET(func, unwrapper)					\
	v8::Local<v8::Object> jsObj = FF_NEW_INSTANCE(constructor);	\
	unwrapper(jsObj) = func(unwrapper(info.This()));		\
	return info.GetReturnValue().Set(jsObj);		

#define FF_SELF_OPERATOR(func, unwrapper)							\
	v8::Local<v8::Object> jsObj = FF_NEW_INSTANCE(constructor);	\
	func(unwrapper(info.This()), unwrapper(jsObj));			\
	return info.GetReturnValue().Set(jsObj);					

#define FF_SCALAR_OPERATOR(func, applyFunc, unwrapper, clazz)			\
	if (!info[0]->IsNumber()) {																			\
		return Nan::ThrowError(FF_NEW_STRING(FF_ERR_WHERE(func, clazz)	\
			+ std::string("expected arg to be a Scalar")));							\
	}																																\
	v8::Local<v8::Object> jsObj = FF_NEW_INSTANCE(constructor);							\
	applyFunc(																											\
		func,																													\
		unwrapper(info.This()),																				\
		info[0]->NumberValue(),																				\
		unwrapper(jsObj)																							\
	);																															\
	return info.GetReturnValue().Set(jsObj);																																																										

#define FF_OPERATOR(func, applyFunc, unwrapper, clazz)														\
	FF_REQUIRE_INSTANCE(constructor, info[0],	FF_NEW_STRING(FF_ERR_WHERE(func, clazz) \
		+ std::string("expected arg to be an instance of ") + std::string(#clazz)));	\
	v8::Local<v8::Object> jsObj = FF_NEW_INSTANCE(constructor);															\
	applyFunc(																																			\
		func,																																					\
		unwrapper(info.This()),																												\
		unwrapper(info[0]->ToObject()),																								\
		unwrapper(jsObj)																															\
	);																																							\
	return info.GetReturnValue().Set(jsObj);

#define FF_OPERATOR_RET_SCALAR(func, applyFunc, unwrapper, clazz)									\
	FF_REQUIRE_INSTANCE(constructor, info[0],	FF_NEW_STRING(FF_ERR_WHERE(func, clazz) \
		+ std::string("expected arg to be an instance of ") + std::string(#clazz)));	\
	double ret;																																			\
	applyFunc(																																			\
		func,																																					\
		unwrapper(info.This()),																												\
		unwrapper(info[0]->ToObject()),																								\
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
	Nan::SetPrototypeMethod(ctor, "determinant", Determinant);

#define FF_INIT_ARITHMETIC_OPERATIONS(clazz, unwrapper)					\
	static NAN_METHOD(Add) {																			\
		FF_OPERATOR(+, FF_APPLY_OPERATOR, unwrapper, clazz);				\
	}																															\
	static NAN_METHOD(Sub) {																			\
		FF_OPERATOR(-, FF_APPLY_OPERATOR, unwrapper, clazz);				\
	}																															\
	static NAN_METHOD(Mul) {																			\
		FF_SCALAR_OPERATOR(*, FF_APPLY_OPERATOR, unwrapper, clazz);	\
	}																															\
	static NAN_METHOD(Div) {																			\
		FF_SCALAR_OPERATOR(/, FF_APPLY_OPERATOR, unwrapper, clazz);	\
	}																															\

#define FF_INIT_MATRIX_OPERATIONS(clazz, unwrapper)											\
	FF_INIT_ARITHMETIC_OPERATIONS(clazz, unwrapper)												\
	static NAN_METHOD(HMul) {																							\
		FF_OPERATOR(cv::multiply, FF_APPLY_FUNC, unwrapper, clazz);					\
	}																																			\
	static NAN_METHOD(HDiv) {																							\
		FF_OPERATOR(cv::divide, FF_APPLY_FUNC, unwrapper, clazz);						\
	}																																			\
	static NAN_METHOD(Absdiff) {																					\
		FF_OPERATOR(cv::absdiff, FF_APPLY_FUNC, unwrapper, clazz);					\
	}																																			\
	static NAN_METHOD(Exp) {																							\
		FF_SELF_OPERATOR(cv::exp, unwrapper);																\
	}																																			\
	static NAN_METHOD(Log) {																							\
		FF_SELF_OPERATOR(cv::log, unwrapper);																\
	}																																		\
	static NAN_METHOD(Sqrt) {																							\
		FF_SELF_OPERATOR(cv::sqrt, unwrapper);															\
	}																																			\

#define FF_INIT_MAT_OPERATIONS()																						\
	FF_INIT_MATRIX_OPERATIONS(Mat, FF_UNWRAP_MAT_AND_GET);										\
	static NAN_METHOD(And) {																									\
		FF_OPERATOR(&, FF_APPLY_OPERATOR, FF_UNWRAP_MAT_AND_GET, Mat);					\
	}																																					\
	static NAN_METHOD(Or) {																										\
		FF_OPERATOR(|, FF_APPLY_OPERATOR, FF_UNWRAP_MAT_AND_GET, Mat);					\
	}																																					\
	static NAN_METHOD(BitwiseAnd) {																						\
		FF_OPERATOR(cv::bitwise_and, FF_APPLY_FUNC, FF_UNWRAP_MAT_AND_GET, Mat);\
	}																																					\
	static NAN_METHOD(BitwiseNot) {																						\
		FF_SELF_OPERATOR(cv::bitwise_not, FF_UNWRAP_MAT_AND_GET);								\
	}																																					\
	static NAN_METHOD(BitwiseOr) {																						\
		FF_OPERATOR(cv::bitwise_or, FF_APPLY_FUNC, FF_UNWRAP_MAT_AND_GET, Mat);	\
	}																																					\
	static NAN_METHOD(BitwiseXor) {																						\
		FF_OPERATOR(cv::bitwise_xor, FF_APPLY_FUNC, FF_UNWRAP_MAT_AND_GET, Mat);\
	}																																					\
	static NAN_METHOD(Abs) {																									\
		FF_SELF_OPERATOR_RET(cv::abs, FF_UNWRAP_MAT_AND_GET);										\
	}																																					\
	static NAN_METHOD(Determinant) {																					\
		return info.GetReturnValue().Set(																				\
			cv::determinant(FF_UNWRAP_MAT_AND_GET(info.This())));									\
	}																																					\
	static NAN_METHOD(Transpose) {																						\
		FF_SELF_OPERATOR(cv::transpose, FF_UNWRAP_MAT_AND_GET);									\
	}																																					

#define FF_INIT_VEC2_OPERATIONS()	FF_INIT_MATRIX_OPERATIONS(Vec2, FF_UNWRAP_VEC2_AND_GET);
#define FF_INIT_VEC3_OPERATIONS()	FF_INIT_MATRIX_OPERATIONS(Vec3, FF_UNWRAP_VEC3_AND_GET);
#define FF_INIT_VEC4_OPERATIONS()	FF_INIT_MATRIX_OPERATIONS(Vec4, FF_UNWRAP_VEC4_AND_GET);

namespace FF {
	template<int cn>
	static v8::Local<v8::Array> vecToJsArr(cv::Vec<double, cn> vec) {
		v8::Local<v8::Array> jsVec = Nan::New<v8::Array>(cn);
		for (int i = 0; i < cn; i++) jsVec->Set(i, Nan::New(vec[i]));
		return jsVec;
	}
}

#endif