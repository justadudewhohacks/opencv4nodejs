#ifndef FF_COREUTILS_H_
#define FF_COREUTILS_H_

#define FF_ASSERT_INDEX_RANGE(idx, max)																									\
	if (idx < 0 || max < idx) {																														\
		return Nan::ThrowError(FF_V8STRING("Index out of bounds: " + std::to_string(idx)));	\
	}																																											

/* TODO fix non scalar matrix multiplication, division */

#define FF_OPERATOR(method, op, clazz, accessor)																													\
	if (!info[0]->IsObject()) {																																							\
		return Nan::ThrowError(FF_V8STRING(std::string(#clazz) + "::" + std::string(#method)									\
			+ " - expected arg to be a " + std::string(#clazz)));																								\
	}																																																				\
	v8::Local<v8::Object> jsObj = Nan::NewInstance(Nan::New(constructor)->GetFunction()).ToLocalChecked();	\
	Nan::ObjectWrap::Unwrap<clazz>(jsObj)->accessor =																												\
		Nan::ObjectWrap::Unwrap<clazz>(info.This())->accessor																									\
		op Nan::ObjectWrap::Unwrap<clazz>(info[0]->ToObject())->accessor;																			\
	info.GetReturnValue().Set(jsObj);																																				\

#define FF_SCALAR_OPERATOR(method, op, clazz, accessor)																										\
	if (!info[0]->IsNumber()) {																																							\
		return Nan::ThrowError(FF_V8STRING(std::string(#clazz) + "::" + std::string(#method)									\
			+ " - expected arg to be a Scalar"));																																\
	}																																																				\
	v8::Local<v8::Object> jsObj = Nan::NewInstance(Nan::New(constructor)->GetFunction()).ToLocalChecked();	\
	Nan::ObjectWrap::Unwrap<clazz>(jsObj)->accessor =																												\
		Nan::ObjectWrap::Unwrap<clazz>(info.This())->accessor																									\
		op info[0]->NumberValue();																																						\
	return info.GetReturnValue().Set(jsObj);																																																																																

#define FF_PROTO_SET_NUMERIC_OPERATORS(ctor)	\
	Nan::SetPrototypeMethod(ctor, "add", Add);	\
	Nan::SetPrototypeMethod(ctor, "sub", Sub);	\
	Nan::SetPrototypeMethod(ctor, "mul", Mul);	\
	Nan::SetPrototypeMethod(ctor, "div", Div);

#define FF_PROTO_SET_LOGICAL_OPERATORS(ctor)	\
	Nan::SetPrototypeMethod(ctor, "and", And);	\
	Nan::SetPrototypeMethod(ctor, "or", Or);		

#define FF_INIT_NUMERIC_OPERATORS(clazz, accessor)		\
	static NAN_METHOD(Add) {														\
		FF_OPERATOR(Add, +, clazz, accessor);							\
	}																										\
	static NAN_METHOD(Sub) {														\
		FF_OPERATOR(Sub, -, clazz, accessor);							\
	}																										\
	static NAN_METHOD(Mul) {														\
		FF_SCALAR_OPERATOR(Mul, *, clazz, accessor);			\
	}																										\
	static NAN_METHOD(Div) {														\
		FF_SCALAR_OPERATOR(Div, /, clazz, accessor);			\
	}

#define FF_INIT_LOGICAL_OPERATORS(clazz, accessor)		\
	static NAN_METHOD(And) {														\
		FF_OPERATOR(And, &, clazz, accessor);							\
	}																										\
	static NAN_METHOD(Or) {															\
		FF_OPERATOR(Or, | , clazz, accessor);							\
	}		

#endif