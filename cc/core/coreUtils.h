#ifndef FF_COREUTILS_H_
#define FF_COREUTILS_H_

#define FF_ASSERT_INDEX_RANGE(idx, max)																									\
	if (idx < 0 || max < idx) {																														\
		return Nan::ThrowError(FF_V8STRING("Index out of bounds: " + std::to_string(idx)));	\
	}																																											

#define FF_MAT_OPERATOR_WITH_SCALAR(name, op)																															\
	if (info[0]->IsNumber()) {																																							\
		v8::Local<v8::Object> jsMat = Nan::NewInstance(Nan::New(constructor)->GetFunction()).ToLocalChecked();\
		Nan::ObjectWrap::Unwrap<Mat>(jsMat)->mat =																														\
			Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat																											\
			op info[0]->NumberValue();																																					\
		return info.GetReturnValue().Set(jsMat);																															\
	}																																																				\
	FF_MAT_OPERATOR(name, op, true)

#define FF_MAT_OPERATOR(name, op, acceptsScalar)																													\
	if (!info[0]->IsObject()) {																																							\
		return Nan::ThrowError(FF_V8STRING(std::string(#name)																									\
			+ " - expected arg to be a Mat" + (acceptsScalar ? " or Scalar" : ""))															\
		);																																																		\
	}																																																				\
	v8::Local<v8::Object> jsMat = Nan::NewInstance(Nan::New(constructor)->GetFunction()).ToLocalChecked();	\
	Nan::ObjectWrap::Unwrap<Mat>(jsMat)->mat =																															\
		Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat																												\
		op Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat;																						\
	info.GetReturnValue().Set(jsMat);																																				\


#endif