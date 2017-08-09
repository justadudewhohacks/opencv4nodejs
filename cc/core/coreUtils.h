#ifndef FF_COREUTILS_H_
#define FF_COREUTILS_H_

#define FF_ASSERT_INDEX_RANGE(idx, max)																									\
	if (idx < 0 || max < idx) {																														\
		return Nan::ThrowError(FF_V8STRING("Index out of bounds: " + std::to_string(idx)));	\
	}																																											

#define FF_APPLY_FUNC(func, arg0, arg1, ret) func(arg0, arg1, ret);
#define FF_APPLY_CLASS_FUNC(func, arg0, arg1, ret) ret = arg0.##func##(arg1);
#define FF_APPLY_OPERATOR(op, arg0, arg1, ret) ret = arg0 op arg1;


/* TODO fix non scalar matrix multiplication, division */

#define FF_ERR_WHERE(func, clazz) std::string(#clazz) + "  " + std::string(#func) + " : "

#define FF_SCALAR_OPERATOR(func, applyFunc, unwrapper, clazz)			\
	if (!info[0]->IsNumber()) {																			\
		return Nan::ThrowError(FF_V8STRING(FF_ERR_WHERE(func, clazz)	\
			+ std::string("expected arg to be a Scalar")));							\
	}																																\
	v8::Local<v8::Object> jsObj = FF_NEW(constructor);							\
	applyFunc(																											\
		func,																													\
		unwrapper(info.This()),																				\
		info[0]->NumberValue(),																				\
		unwrapper(jsObj)																							\
	);																															\
	return info.GetReturnValue().Set(jsObj);																																																										

#define FF_OPERATOR(func, applyFunc, unwrapper, clazz)														\
	FF_REQUIRE_INSTANCE(constructor, info[0],	FF_V8STRING(FF_ERR_WHERE(func, clazz) \
		+ std::string("expected arg to be an instance of ") + std::string(#clazz)));	\
	v8::Local<v8::Object> jsObj = FF_NEW(constructor);															\
	applyFunc(																																			\
		func,																																					\
		unwrapper(info.This()),																												\
		unwrapper(info[0]->ToObject()),																								\
		unwrapper(jsObj)																															\
	);																																							\
	return info.GetReturnValue().Set(jsObj);

#define FF_OPERATOR_RET_SCALAR(func, applyFunc, unwrapper, clazz)									\
	FF_REQUIRE_INSTANCE(constructor, info[0],	FF_V8STRING(FF_ERR_WHERE(func, clazz) \
		+ std::string("expected arg to be an instance of ") + std::string(#clazz)));	\
	double ret;																																			\
	applyFunc(																																			\
		func,																																					\
		unwrapper(info.This()),																												\
		unwrapper(info[0]->ToObject()),																								\
		ret																																						\
	);																																							\
	return info.GetReturnValue().Set(ret);

#define FF_PROTO_SET_MATRIX_OPERATIONS(ctor)				\
	Nan::SetPrototypeMethod(ctor, "add", Add);				\
	Nan::SetPrototypeMethod(ctor, "sub", Sub);				\
	Nan::SetPrototypeMethod(ctor, "mul", Mul);				\
	Nan::SetPrototypeMethod(ctor, "div", Div);				\
	Nan::SetPrototypeMethod(ctor, "hMul", HMul);	\
	Nan::SetPrototypeMethod(ctor, "hDiv", HDiv);	\
	Nan::SetPrototypeMethod(ctor, "dot", Dot);

#define FF_PROTO_SET_MAT_OPERATIONS(ctor)				\
	FF_PROTO_SET_MATRIX_OPERATIONS(ctor)					\
	Nan::SetPrototypeMethod(ctor, "and", And);		\
	Nan::SetPrototypeMethod(ctor, "or", Or);	

#define FF_INIT_MATRIX_OPERATIONS(clazz, accessor, unwrapper)						\
	static NAN_METHOD(Add) {																							\
		FF_OPERATOR(+, FF_APPLY_OPERATOR, unwrapper, clazz);								\
	}																																			\
	static NAN_METHOD(Sub) {																							\
		FF_OPERATOR(-, FF_APPLY_OPERATOR, unwrapper, clazz);								\
	}																																			\
	static NAN_METHOD(Mul) {																							\
		FF_SCALAR_OPERATOR(*, FF_APPLY_OPERATOR, unwrapper, clazz);					\
	}																																			\
	static NAN_METHOD(Div) {																							\
		FF_SCALAR_OPERATOR(/, FF_APPLY_OPERATOR, unwrapper, clazz);					\
	}																																			\
	static NAN_METHOD(HMul) {																							\
		FF_OPERATOR(cv::multiply, FF_APPLY_FUNC, unwrapper, clazz);					\
	}																																			\
	static NAN_METHOD(HDiv) {																							\
		FF_OPERATOR(cv::divide, FF_APPLY_FUNC, unwrapper, clazz);						\
	}																																			\
	static NAN_METHOD(Dot) {																							\
		FF_OPERATOR_RET_SCALAR(dot, FF_APPLY_CLASS_FUNC, unwrapper, clazz);	\
	}

#define FF_INIT_MAT_OPERATIONS()																								\
	FF_INIT_MATRIX_OPERATIONS(Mat, mat, FF_UNWRAP_MAT_AND_GET);										\
	static NAN_METHOD(And) {																											\
		FF_OPERATOR(&, FF_APPLY_OPERATOR, FF_UNWRAP_MAT_AND_GET, Mat);							\
	}																																							\
	static NAN_METHOD(Or) {																												\
		FF_OPERATOR(|, FF_APPLY_OPERATOR, FF_UNWRAP_MAT_AND_GET, Mat);							\
	}

#define FF_INIT_VEC2_OPERATIONS()	FF_INIT_MATRIX_OPERATIONS(Vec2, vec, FF_UNWRAP_VEC2_AND_GET);
#define FF_INIT_VEC3_OPERATIONS()	FF_INIT_MATRIX_OPERATIONS(Vec3, vec, FF_UNWRAP_VEC3_AND_GET);
#define FF_INIT_VEC4_OPERATIONS()	FF_INIT_MATRIX_OPERATIONS(Vec4, vec, FF_UNWRAP_VEC4_AND_GET);

#endif