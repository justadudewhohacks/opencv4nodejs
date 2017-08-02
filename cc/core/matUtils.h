#include <nan.h>
#include <opencv2/core.hpp>

#ifndef FF_MATUTILS_H_
#define FF_MATUTILS_H_

#define FF_MAT_FILL(mat, vec, put)				\
	for (int r = 0; r < mat.rows; r++) {		\
		for (int c = 0; c < mat.cols; c++) {	\
			put(mat, vec, r, c);								\
		}																			\
	}

#define FF_MAT_FROM_JS_ARRAY(mat, rowArray, put)																	\
	for (int r = 0; r < mat.rows; r++) {																						\
		v8::Local<v8::Array> colArray = v8::Local<v8::Array>::Cast(rowArray->Get(r));	\
		for (int c = 0; c < mat.cols; c++) {																					\
			put(mat, colArray->Get(c), r, c);																						\
		}																																							\
	}	

#define FF_JS_ARRAY_FROM_MAT(mat, rowArray, get)										\
	for (int r = 0; r < mat.rows; r++) {															\
		v8::Local<v8::Array> colArray = Nan::New<v8::Array>(mat.cols);	\
		for (int c = 0; c < mat.cols; c++) {														\
			get(colArray, mat, r, c);																			\
		}																																\
		rowArray->Set(r, colArray);																			\
	}	

#define FF_MAT_APPLY_TYPED_OPERATOR(mat, arg, type, ITERATOR, OPERATOR) {	\
	switch (type) {																													\
	case CV_8UC1:																														\
		ITERATOR(mat, arg, OPERATOR<uchar>)															\
			break;																															\
	case CV_8UC2:																														\
		ITERATOR(mat, arg, OPERATOR##Vec2<uchar>)												\
			break;																															\
	case CV_8UC3:																														\
		ITERATOR(mat, arg, OPERATOR##Vec3<uchar>)												\
			break;																															\
	case CV_8UC4:																														\
		ITERATOR(mat, arg, OPERATOR##Vec4<uchar>)												\
			break;																															\
	case CV_8SC1:																														\
		ITERATOR(mat, arg, OPERATOR##<char>)\
			break;\
	case CV_8SC2:\
		ITERATOR(mat, arg, OPERATOR##Vec2<char>)\
			break;\
	case CV_8SC3:\
		ITERATOR(mat, arg, OPERATOR##Vec3<char>)\
			break;\
	case CV_8SC4:\
		ITERATOR(mat, arg, OPERATOR##Vec4<char>)\
			break;\
	case CV_16UC1:\
		ITERATOR(mat, arg, OPERATOR##<ushort>)\
			break;\
	case CV_16UC2:\
		ITERATOR(mat, arg, OPERATOR##Vec2<ushort>)\
			break;\
	case CV_16UC3:\
		ITERATOR(mat, arg, OPERATOR##Vec3<ushort>)\
			break;\
	case CV_16UC4:\
		ITERATOR(mat, arg, OPERATOR##Vec4<ushort>)\
			break;\
	case CV_16SC1:\
		ITERATOR(mat, arg, OPERATOR##<short>)\
			break;\
	case CV_16SC2:\
		ITERATOR(mat, arg, OPERATOR##Vec2<short>)\
			break;\
	case CV_16SC3:\
		ITERATOR(mat, arg, OPERATOR##Vec3<short>)\
			break;\
	case CV_16SC4:\
		ITERATOR(mat, arg, OPERATOR##Vec4<short>)\
			break;\
	case CV_32SC1:\
		ITERATOR(mat, arg, OPERATOR##<int>)\
			break;\
	case CV_32SC2:\
		ITERATOR(mat, arg, OPERATOR##Vec2<int>)\
			break;\
	case CV_32SC3:\
		ITERATOR(mat, arg, OPERATOR##Vec3<int>)\
			break;\
	case CV_32SC4:\
		ITERATOR(mat, arg, OPERATOR##Vec4<int>)\
			break;\
	case CV_32FC1: case CV_64FC1:\
		ITERATOR(mat, arg, OPERATOR##<double>)\
			break;\
	case CV_32FC2: case CV_64FC2:\
		ITERATOR(mat, arg, OPERATOR##Vec2<double>)\
			break;\
	case CV_32FC3: case CV_64FC3:\
		ITERATOR(mat, arg, OPERATOR##Vec3<double>)\
			break;\
	case CV_32FC4: case CV_64FC4:\
		ITERATOR(mat, arg, OPERATOR##Vec4<double>)\
			break;\
	default:\
		Nan::ThrowError(Nan::New("invalid matType: " + std::to_string(type)).ToLocalChecked());\
		break;\
	}\
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

namespace FF {
	template<typename type>
	static inline void matPut(cv::Mat mat, v8::Local<v8::Value> value, int r, int c) {
		mat.at<type>(r, c) = (type)value->NumberValue();
	}

	template<typename type>
	static inline void matPutVec2(cv::Mat mat, v8::Local<v8::Value> vector, int r, int c) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(vector);
		mat.at<cv::Vec<type, 2>>(r, c) = cv::Vec<type, 2>(
			(type)vec->Get(0)->NumberValue(),
			(type)vec->Get(1)->NumberValue()
		);
	}

	template<typename type>
	static inline void matPutVec3(cv::Mat mat, v8::Local<v8::Value> vector, int r, int c) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(vector);
		mat.at<cv::Vec<type, 3>>(r, c) = cv::Vec<type, 3>(
			(type)vec->Get(0)->NumberValue(),
			(type)vec->Get(1)->NumberValue(),
			(type)vec->Get(2)->NumberValue()
		);
	}

	template<typename type>
	static inline void matPutVec4(cv::Mat mat, v8::Local<v8::Value> vector, int r, int c) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(vector);
		mat.at<cv::Vec<type, 4>>(r, c) = cv::Vec<type, 4>(
			(type)vec->Get(0)->NumberValue(),
			(type)vec->Get(1)->NumberValue(),
			(type)vec->Get(2)->NumberValue(),
			(type)vec->Get(3)->NumberValue()
		);
	}

	template<typename type>
	static inline void matGet(v8::Local<v8::Array> colArray, cv::Mat mat, int r, int c) {
		colArray->Set(c, Nan::New(mat.at<type>(r, c)));
	}

	template<typename type>
	static inline void matGetVec2(v8::Local<v8::Array> colArray, cv::Mat mat, int r, int c) {
		v8::Local<v8::Array> vec = Nan::New<v8::Array>(2);
		vec->Set(0, Nan::New(mat.at<cv::Vec<type, 2>>(r, c)[0]));
		vec->Set(1, Nan::New(mat.at<cv::Vec<type, 2>>(r, c)[1]));
		colArray->Set(c, vec);
	}

	template<typename type>
	static inline void matGetVec3(v8::Local<v8::Array> colArray, cv::Mat mat, int r, int c) {
		v8::Local<v8::Array> vec = Nan::New<v8::Array>(3);
		vec->Set(0, Nan::New(mat.at<cv::Vec<type, 3>>(r, c)[0]));
		vec->Set(1, Nan::New(mat.at<cv::Vec<type, 3>>(r, c)[1]));
		vec->Set(2, Nan::New(mat.at<cv::Vec<type, 3>>(r, c)[2]));
		colArray->Set(c, vec);
	}

	template<typename type>
	static inline void matGetVec4(v8::Local<v8::Array> colArray, cv::Mat mat, int r, int c) {
		v8::Local<v8::Array> vec = Nan::New<v8::Array>(4);
		vec->Set(0, Nan::New(mat.at<cv::Vec<type, 4>>(r, c)[0]));
		vec->Set(1, Nan::New(mat.at<cv::Vec<type, 4>>(r, c)[1]));
		vec->Set(2, Nan::New(mat.at<cv::Vec<type, 4>>(r, c)[2]));
		vec->Set(3, Nan::New(mat.at<cv::Vec<type, 4>>(r, c)[3]));
		colArray->Set(c, vec);
	}

	static int reassignMatTypeIfFloat(int type) {
		switch (type) {
		case CV_32FC1: return CV_64FC1;
		case CV_32FC2: return CV_64FC2;
		case CV_32FC3: return CV_64FC3;
		case CV_32FC4: return CV_64FC4;
		default: return type;
		}
	}
}

#endif