#include "matUtils.h"
#include <Eigen/Core>
#include <iostream>

#define FF_GETTER(clazz, name, value)	\
	NAN_GETTER(name) { info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<clazz>(info.This())->value); }

#define FF_GET_JS_PROP(obj, prop) \
	Nan::Get(obj, Nan::New(#prop).ToLocalChecked()).ToLocalChecked()

#define FF_GET_JS_PROP_NUMBER(obj, prop) \
	FF_GET_JS_PROP(obj, prop)->NumberValue()

#define FF_GET_JS_PROP_OBJECT(obj, prop) \
	FF_GET_JS_PROP(obj, prop)->ToObject()

#define FF_GET_JS_PROP_FLOAT(obj, prop) \
	(float)FF_GET_JS_PROP_NUMBER(obj, prop)

#define FF_GET_JS_PROP_DOUBLE(obj, prop) \
	(double)FF_GET_JS_PROP_NUMBER(obj, prop)

#define FF_GET_JS_PROP_INT(obj, prop) \
	(int)FF_GET_JS_PROP_NUMBER(obj, prop)

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

#define FF_VERIFY_OPTIONAL_ARG(n, arg, assertType, castType)		\
	if (info.Length() > n) {																			\
		if (!info[n]->assertType()) {																\
			return Nan::ThrowError(Nan::New(													\
				"Expected " + std::string(#arg) + " " + #assertType +		\
				", argument " + std::to_string(n) + " invalid: " +			\
				std::string(*Nan::Utf8String(info[n]->ToString()))			\
			).ToLocalChecked());																			\
		}																														\
		arg = info[0]->castType();																	\
	}


namespace FF {
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



	
