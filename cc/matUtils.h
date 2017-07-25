#include <nan.h>
#include <opencv2/core.hpp>

#define FF_MAT_FROM_JS_ARRAY(mat, rowArray, put)																	\
	for (int r = 0; r < mat.rows; r++) {																						\
		v8::Local<v8::Array> colArray = v8::Local<v8::Array>::Cast(rowArray->Get(r));	\
		for (int c = 0; c < mat.cols; c++) {																					\
			put(mat, colArray, r, c);																										\
		}																																							\
	}	

#define FF_JS_ARRAY_FROM_MAT(rowArray, mat, get)										\
	for (int r = 0; r < mat.rows; r++) {															\
		v8::Local<v8::Array> colArray = Nan::New<v8::Array>(mat.cols);	\
		for (int c = 0; c < mat.cols; c++) {														\
			get(colArray, mat, r, c);																			\
		}																																\
		rowArray->Set(r, colArray);																			\
	}	

namespace FF {
	template<typename type>
	static inline void matPut(cv::Mat mat, v8::Local<v8::Array> colArray, int r, int c) {
		mat.at<type>(r, c) = (type)colArray->Get(c)->NumberValue();
	}

	template<typename type>
	static inline void matPutVec2(cv::Mat mat, v8::Local<v8::Array> colArray, int r, int c) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(colArray->Get(c));
		mat.at<cv::Vec<type, 2>>(r, c) = cv::Vec<type, 2>(
			(type)vec->Get(0)->NumberValue(),
			(type)vec->Get(1)->NumberValue()
			);
	}

	template<typename type>
	static inline void matPutVec3(cv::Mat mat, v8::Local<v8::Array> colArray, int r, int c) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(colArray->Get(c));
		mat.at<cv::Vec<type, 3>>(r, c) = cv::Vec<type, 3>(
			(type)vec->Get(0)->NumberValue(),
			(type)vec->Get(1)->NumberValue(),
			(type)vec->Get(2)->NumberValue()
			);
	}

	template<typename type>
	static inline void matPutVec4(cv::Mat mat, v8::Local<v8::Array> colArray, int r, int c) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(colArray->Get(c));
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
	
	static v8::Local<v8::Array> matDataToJsArray(cv::Mat mat) {
		v8::Local<v8::Array> rowArray = Nan::New<v8::Array>(mat.rows);
		switch (mat.type()) {
			case CV_8UC1:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGet<uchar>)
					break;
			case CV_8UC2:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec2<uchar>)
					break;
			case CV_8UC3:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec3<uchar>)
					break;
			case CV_8UC4:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec4<uchar>)
					break;
			case CV_8SC1:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGet<char>)
					break;
			case CV_8SC2:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec2<char>)
					break;
			case CV_8SC3:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec3<char>)
					break;
			case CV_8SC4:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec4<char>)
					break;
			case CV_16UC1:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGet<ushort>)
					break;
			case CV_16UC2:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec2<ushort>)
					break;
			case CV_16UC3:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec3<ushort>)
					break;
			case CV_16UC4:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec4<ushort>)
					break;
			case CV_16SC1:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGet<short>)
					break;
			case CV_16SC2:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec2<short>)
					break;
			case CV_16SC3:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec3<short>)
					break;
			case CV_16SC4:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec4<short>)
					break;
			case CV_32SC1:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGet<int>)
					break;
			case CV_32SC2:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec2<int>)
					break;
			case CV_32SC3:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec3<int>)
					break;
			case CV_32SC4:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec4<int>)
					break;
			case CV_32FC1: case CV_64FC1:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGet<double>)
					break;
			case CV_32FC2: case CV_64FC2:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec2<double>)
					break;
			case CV_32FC3: case CV_64FC3:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec3<double>)
					break;
			case CV_32FC4: case CV_64FC4:
				FF_JS_ARRAY_FROM_MAT(rowArray, mat, matGetVec4<double>)
					break;
			default:
					break;
		}
		return rowArray;
	}

	static void fillMatDataFromJsArray(cv::Mat& mat, v8::Local<v8::Array> rowArray) {
		switch (mat.type()) {
			case CV_8UC1:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPut<uchar>)
					break;
			case CV_8UC2:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec2<uchar>)
					break;
			case CV_8UC3:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec3<uchar>)
					break;
			case CV_8UC4:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec4<uchar>)
					break;
			case CV_8SC1:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPut<char>)
					break;
			case CV_8SC2:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec2<char>)
					break;
			case CV_8SC3:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec3<char>)
					break;
			case CV_8SC4:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec4<char>)
					break;
			case CV_16UC1:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPut<ushort>)
					break;
			case CV_16UC2:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec2<ushort>)
					break;
			case CV_16UC3:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec3<ushort>)
					break;
			case CV_16UC4:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec4<ushort>)
					break;
			case CV_16SC1:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPut<short>)
					break;
			case CV_16SC2:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec2<short>)
					break;
			case CV_16SC3:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec3<short>)
					break;
			case CV_16SC4:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec4<short>)
					break;
			case CV_32SC1:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPut<int>)
					break;
			case CV_32SC2:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec2<int>)
					break;
			case CV_32SC3:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec3<int>)
					break;
			case CV_32SC4:
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec4<int>)
					break;
			case CV_32FC1: case CV_64FC1:
				mat = cv::Mat(mat.rows, mat.cols, CV_64FC1);
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPut<double>)
					break;
			case CV_32FC2: case CV_64FC2:
				mat = cv::Mat(mat.rows, mat.cols, CV_64FC2);
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec2<double>)
					break;
			case CV_32FC3: case CV_64FC3:
				mat = cv::Mat(mat.rows, mat.cols, CV_64FC3);
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec3<double>)
					break;
			case CV_32FC4: case CV_64FC4:
				mat = cv::Mat(mat.rows, mat.cols, CV_64FC4);
				FF_MAT_FROM_JS_ARRAY(mat, rowArray, matPutVec4<double>)
					break;
			default:
					break;
		}	
	}
}
