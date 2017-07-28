#include "matUtils.h"
#include <Eigen/Core>
#include <iostream>

#ifndef FF_MACROS_H_
#define FF_MACROS_H_

#define FF_V8STRING(s) \
	Nan::New(s).ToLocalChecked()

#define FF_JS_VAL_TO_STRING(s) \
	std::string(*Nan::Utf8String(s->ToString()))

#define FF_GETTER(clazz, name, value)	\
	NAN_GETTER(name) { info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<clazz>(info.This())->value); }

/* unchecked js prop getters */

#define FF_GET_JSPROP(obj, prop) \
	Nan::Get(obj, FF_V8STRING(#prop)).ToLocalChecked()

#define FF_GET_JSPROP_NUMBER(obj, prop) \
	FF_GET_JSPROP(obj, prop)->NumberValue()

#define FF_GET_JSPROP_OBJECT(obj, prop) \
	FF_GET_JSPROP(obj, prop)->ToObject()

#define FF_GET_JSPROP_FLOAT(obj, prop) \
	(float)FF_GET_JSPROP_NUMBER(obj, prop)

#define FF_GET_JSPROP_DOUBLE(obj, prop) \
	(double)FF_GET_JSPROP_NUMBER(obj, prop)

#define FF_GET_JSPROP_INT(obj, prop) \
	(int)FF_GET_JSPROP(obj, prop)->IntegerValue()

#define FF_GET_JSPROP_UINT(obj, prop) \
	(uint)FF_GET_JSPROP(obj, prop)->Uint32Value()

#define FF_GET_JSPROP_STRING(obj, prop) \
	FF_JS_VAL_TO_STRING(FF_GET_JSPROP(obj, prop)->ToString())

#define FF_TRY(work)										\
	try {																	\
		work																\
	} catch (std::exception &e) {					\
		return Nan::ThrowError(e.what());		\
	} catch (...) {												\
		return Nan::ThrowError("SEGFAULT");	\
	}

#define FF_MAT_TO_JS_ARR(data, rows, cols)										\
	v8::Local<v8::Array> rowArray = Nan::New<v8::Array>(rows);	\

#define FF_GET_TYPECHECKED_JSPROP_IFDEF(obj, var, prop, assertType, castType)	\
	if (obj->HasOwnProperty(FF_V8STRING(#prop))) {															\
		if (!FF_GET_JSPROP(obj, prop)->assertType()) {														\
			return Nan::ThrowError(FF_V8STRING(																			\
				"Invalid type for " + std::string(#prop) + " :"												\
				+ FF_GET_JSPROP_STRING(obj, prop)																			\
				+ ", expected: " + #assertType																				\
			));																																			\
		}																																					\
		var = FF_GET_JSPROP(obj, prop)->castType();																\
	}

#define FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(obj, prop, assertType, castType)	\
	FF_GET_TYPECHECKED_JSPROP_IFDEF(obj, prop, prop, assertType, castType)

namespace FF {
	/* checked js prop getters */

	static inline v8::Local<v8::Value> getCheckedJsProp(v8::Local<v8::Object> obj, char* prop) {
		if (!obj->HasOwnProperty(FF_V8STRING(prop))) {
			Nan::ThrowError(FF_V8STRING("Object has no property: " + std::string(prop)));
		}
		return Nan::Get(obj, FF_V8STRING(prop)).ToLocalChecked();
	}

	static inline v8::Local<v8::Array> matrixdToJsArray(Eigen::MatrixXd vec) {
		v8::Local<v8::Array> jsVec = Nan::New<v8::Array>(vec.rows());
		for (int r = 0; r < vec.rows(); r++) {
			v8::Local<v8::Array> colArray = Nan::New<v8::Array>(vec.cols());
			for (int c = 0; c < vec.cols(); c++) {
				colArray->Set(c, Nan::New(vec(r, c)));
			}
			jsVec->Set(r, colArray);
		}
		return jsVec;
	}

	static inline Eigen::MatrixXd jsArrayToMatrixd(v8::Local<v8::Array> jsVec) {
		int rows = jsVec->Length(),
				cols = v8::Local<v8::Array>::Cast(jsVec->Get(0))->Length();
		Eigen::MatrixXd mat(rows, cols);
		for (int r = 0; r < rows; r++) {
			v8::Local<v8::Array> rowArray = v8::Local<v8::Array>::Cast(jsVec->Get(r));
			for (int c = 0; c < cols; c++) {
				mat(r, c) = rowArray->Get(c)->NumberValue();
			}
		}
		return mat;
	}
}

#endif