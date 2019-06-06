#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_MATUTILS_H__
#define __FF_MATUTILS_H__

#define FF_MAT_AT(mat, val, get)                                                         \
  if (mat.dims > 2)                                                                      \
    val = get(mat, info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), info[1]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), info[2]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value()); \
  else                                                                                   \
    val = get(mat, info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), info[1]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value());

#define FF_MAT_AT_ARRAY(mat, val, get)  \
  { \
	std::vector<int> vec; \
	if (FF::IntArrayConverter::arg(0, &vec, info)) { \
		return tryCatch.reThrow(); \
	} \
    const int* idx = &vec.front();      \
    val = get(mat, idx);                \
  }

#define FF_MAT_SET(mat, val, put)                                                        \
  if (mat.dims > 2)                                                                      \
    put(mat, val, info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), info[1]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), info[2]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value());  \
  else                                                                                   \
    put(mat, val, info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), info[1]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value());

#define FF_MAT_FILL(mat, vec, put)				\
	for (int r = 0; r < mat.rows; r++) {		\
		for (int c = 0; c < mat.cols; c++) {	\
			put(mat, vec, r, c);								\
		}																			\
	}

#define FF_MAT_FROM_JS_ARRAY(mat, rowArray, put)																	\
	for (int r = 0; r < mat.rows; r++) {																						\
		v8::Local<v8::Array> colArray = v8::Local<v8::Array>::Cast(Nan::Get(rowArray, r).ToLocalChecked());	\
		for (int c = 0; c < mat.cols; c++) {																					\
			put(mat, Nan::Get(colArray, c).ToLocalChecked(), r, c);																						\
		}																																							\
	}

#define FF_JS_ARRAY_FROM_MAT(mat, rowArray, get)										\
	for (int r = 0; r < mat.rows; r++) {															\
		v8::Local<v8::Array> colArray = Nan::New<v8::Array>(mat.cols);	\
		for (int c = 0; c < mat.cols; c++) {														\
			Nan::Set(colArray, c, get(mat, r, c));															\
		}																																\
		Nan::Set(rowArray, r, colArray);																			\
	}

#define FF_JS_ARRAY_FROM_MAT_3D(mat, rowArray, get)                       \
  for (int r = 0; r < mat.size[0]; r++) {                                 \
    v8::Local<v8::Array> colArray = Nan::New<v8::Array>(mat.size[1]);     \
    for (int c = 0; c < mat.size[1]; c++) {                               \
      v8::Local<v8::Array> depthArray = Nan::New<v8::Array>(mat.size[2]); \
      for (int z = 0; z < mat.size[2]; z++) {                             \
        Nan::Set(depthArray, z, get(mat, r, c, z));                            \
      }                                                                   \
      Nan::Set(colArray, c, depthArray);                                       \
    }                                                                     \
    Nan::Set(rowArray, r, colArray);                                           \
  }

#define FF_MAT_APPLY_TYPED_OPERATOR(mat, arg, type, ITERATOR, OPERATOR) {	\
	switch (type) {																													\
	case CV_8UC1:																														\
		ITERATOR(mat, arg, OPERATOR##Val<uchar>)															\
			break;																															\
	case CV_8UC2:																														\
		ITERATOR(mat, arg, OPERATOR##Vec2<uchar>)															\
			break;																															\
	case CV_8UC3:																														\
		ITERATOR(mat, arg, OPERATOR##Vec3<uchar>)															\
			break;																															\
	case CV_8UC4:																														\
		ITERATOR(mat, arg, OPERATOR##Vec4<uchar>)															\
			break;																															\
	case CV_8SC1:																														\
		ITERATOR(mat, arg, OPERATOR##Val<char>)																\
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
		ITERATOR(mat, arg, OPERATOR##Val<ushort>)\
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
		ITERATOR(mat, arg, OPERATOR##Val<short>)\
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
		ITERATOR(mat, arg, OPERATOR##Val<int>)\
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
	case CV_32FC1:\
		ITERATOR(mat, arg, OPERATOR##Val<float>)\
			break;\
	case CV_32FC2:\
		ITERATOR(mat, arg, OPERATOR##Vec2<float>)\
			break;\
	case CV_32FC3:\
		ITERATOR(mat, arg, OPERATOR##Vec3<float>)\
			break;\
	case CV_32FC4:\
		ITERATOR(mat, arg, OPERATOR##Vec4<float>)\
			break;\
	case CV_64FC1:\
		ITERATOR(mat, arg, OPERATOR##Val<double>)\
			break;\
	case CV_64FC2:\
		ITERATOR(mat, arg, OPERATOR##Vec2<double>)\
			break;\
	case CV_64FC3:\
		ITERATOR(mat, arg, OPERATOR##Vec3<double>)\
			break;\
	case CV_64FC4:\
		ITERATOR(mat, arg, OPERATOR##Vec4<double>)\
			break;\
	default:\
		return tryCatch.throwError("invalid matType: " + std::to_string(type));\
		break;\
	}\
}

#define FF_ASSERT_CHANNELS(cn, have, what) \
	if (cn != have) { \
		return tryCatch.throwError(std::string(what) + " - expected vector with " \
			+ std::to_string(cn) + " channels, have " + std::to_string(have));	\
	}

namespace FF {
	template<typename type>
	static inline void matPutVal(cv::Mat mat, v8::Local<v8::Value> value, int r, int c) {
		mat.at<type>(r, c) = (type)value->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
	}

	template<typename type>
	static inline void matPutVal(cv::Mat mat, v8::Local<v8::Value> value, int r, int c, int z) {
		mat.at<type>(r, c, z) = (type)value->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
	}

	template<typename type>
	static inline void matPutVec2(cv::Mat mat, v8::Local<v8::Value> vector, int r, int c) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(vector);
		mat.at< cv::Vec<type, 2> >(r, c) = cv::Vec<type, 2>(
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 0).ToLocalChecked()),
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 1).ToLocalChecked())
		);
	}

	template<typename type>
	static inline void matPutVec2(cv::Mat mat, v8::Local<v8::Value> vector, int r, int c, int z) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(vector);
		mat.at< cv::Vec<type, 2> >(r, c, z) = cv::Vec<type, 2>(
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 0).ToLocalChecked()),
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 1).ToLocalChecked())
		);
	}

	template<typename type>
	static inline void matPutVec3(cv::Mat mat, v8::Local<v8::Value> vector, int r, int c) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(vector);
		mat.at< cv::Vec<type, 3> >(r, c) = cv::Vec<type, 3>(
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 0).ToLocalChecked()),
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 1).ToLocalChecked()),
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 2).ToLocalChecked())
		);
	}

	template<typename type>
	static inline void matPutVec3(cv::Mat mat, v8::Local<v8::Value> vector, int r, int c, int z) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(vector);
		mat.at< cv::Vec<type, 3> >(r, c, z) = cv::Vec<type, 3>(
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 0).ToLocalChecked()),
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 1).ToLocalChecked()),
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 2).ToLocalChecked())
		);
	}

	template<typename type>
	static inline void matPutVec4(cv::Mat mat, v8::Local<v8::Value> vector, int r, int c) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(vector);
		mat.at< cv::Vec<type, 4> >(r, c) = cv::Vec<type, 4>(
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 0).ToLocalChecked()),
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 1).ToLocalChecked()),
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 2).ToLocalChecked()),
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 3).ToLocalChecked())
		);
	}

	template<typename type>
	static inline void matPutVec4(cv::Mat mat, v8::Local<v8::Value> vector, int r, int c, int z) {
		v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(vector);
		mat.at< cv::Vec<type, 4> >(r, c, z) = cv::Vec<type, 4>(
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 0).ToLocalChecked()),
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 1).ToLocalChecked()),
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 2).ToLocalChecked()),
			(type)FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 3).ToLocalChecked())
		);
	}

	template<typename type>
	static inline v8::Local<v8::Value> matGetVal(cv::Mat mat, int r, int c) {
		return Nan::New(mat.at<type>(r, c));
	}

	template<typename type>
	static inline v8::Local<v8::Value> matGetVal(cv::Mat mat, int r, int c, int z) {
		return Nan::New(mat.at<type>(r, c, z));
	}

  template<typename type>
	static inline v8::Local<v8::Value> matGetVal(cv::Mat mat, const int* idx) {
		return Nan::New(mat.at<type>(idx));
	}

	template<typename type>
	static inline v8::Local<v8::Value> matGetVec2(cv::Mat mat, int r, int c) {
		v8::Local<v8::Array> vec = Nan::New<v8::Array>(2);
		Nan::Set(vec, 0, Nan::New(mat.at< cv::Vec<type, 2> >(r, c)[0]));
		Nan::Set(vec, 1, Nan::New(mat.at< cv::Vec<type, 2> >(r, c)[1]));
		return vec;
	}

	template<typename type>
	static inline v8::Local<v8::Value> matGetVec2(cv::Mat mat, int r, int c, int z) {
		v8::Local<v8::Array> vec = Nan::New<v8::Array>(2);
		Nan::Set(vec, 0, Nan::New(mat.at< cv::Vec<type, 2> >(r, c, z)[0]));
		Nan::Set(vec, 1, Nan::New(mat.at< cv::Vec<type, 2> >(r, c, z)[1]));
		return vec;
	}

  template<typename type>
	static inline v8::Local<v8::Value> matGetVec2(cv::Mat mat, const int* idx) {
		v8::Local<v8::Array> vec = Nan::New<v8::Array>(2);
		Nan::Set(vec, 0, Nan::New(mat.at< cv::Vec<type, 2> >(idx)[0]));
		Nan::Set(vec, 1, Nan::New(mat.at< cv::Vec<type, 2> >(idx)[1]));
		return vec;
	}

	template<typename type>
	static inline v8::Local<v8::Value> matGetVec3(cv::Mat mat, int r, int c) {
		v8::Local<v8::Array> vec = Nan::New<v8::Array>(3);
		Nan::Set(vec, 0, Nan::New(mat.at< cv::Vec<type, 3> >(r, c)[0]));
		Nan::Set(vec, 1, Nan::New(mat.at< cv::Vec<type, 3> >(r, c)[1]));
		Nan::Set(vec, 2, Nan::New(mat.at< cv::Vec<type, 3> >(r, c)[2]));
		return vec;
	}

	template<typename type>
	static inline v8::Local<v8::Value> matGetVec3(cv::Mat mat, int r, int c, int z) {
		v8::Local<v8::Array> vec = Nan::New<v8::Array>(3);
		Nan::Set(vec, 0, Nan::New(mat.at< cv::Vec<type, 3> >(r, c, z)[0]));
		Nan::Set(vec, 1, Nan::New(mat.at< cv::Vec<type, 3> >(r, c, z)[1]));
		Nan::Set(vec, 2, Nan::New(mat.at< cv::Vec<type, 3> >(r, c, z)[2]));
		return vec;
	}

  template<typename type>
	static inline v8::Local<v8::Value> matGetVec3(cv::Mat mat, const int* idx) {
		v8::Local<v8::Array> vec = Nan::New<v8::Array>(3);
		Nan::Set(vec, 0, Nan::New(mat.at< cv::Vec<type, 3> >(idx)[0]));
		Nan::Set(vec, 1, Nan::New(mat.at< cv::Vec<type, 3> >(idx)[1]));
		Nan::Set(vec, 2, Nan::New(mat.at< cv::Vec<type, 3> >(idx)[2]));
		return vec;
	}

	template<typename type>
	static inline v8::Local<v8::Value> matGetVec4(cv::Mat mat, int r, int c) {
		v8::Local<v8::Array> vec = Nan::New<v8::Array>(4);
		Nan::Set(vec, 0, Nan::New(mat.at< cv::Vec<type, 4> >(r, c)[0]));
		Nan::Set(vec, 1, Nan::New(mat.at< cv::Vec<type, 4> >(r, c)[1]));
		Nan::Set(vec, 2, Nan::New(mat.at< cv::Vec<type, 4> >(r, c)[2]));
		Nan::Set(vec, 3, Nan::New(mat.at< cv::Vec<type, 4> >(r, c)[3]));
		return vec;
	}

	template<typename type>
	static inline v8::Local<v8::Value> matGetVec4(cv::Mat mat, int r, int c, int z) {
		v8::Local<v8::Array> vec = Nan::New<v8::Array>(4);
		Nan::Set(vec, 0, Nan::New(mat.at< cv::Vec<type, 4> >(r, c, z)[0]));
		Nan::Set(vec, 1, Nan::New(mat.at< cv::Vec<type, 4> >(r, c, z)[1]));
		Nan::Set(vec, 2, Nan::New(mat.at< cv::Vec<type, 4> >(r, c, z)[2]));
		Nan::Set(vec, 3, Nan::New(mat.at< cv::Vec<type, 4> >(r, c, z)[3]));
		return vec;
	}

  template<typename type>
  static inline v8::Local<v8::Value> matGetVec4(cv::Mat mat, const int* idx) {
    v8::Local<v8::Array> vec = Nan::New<v8::Array>(4);
    Nan::Set(vec, 0, Nan::New(mat.at< cv::Vec<type, 4> >(idx)[0]));
    Nan::Set(vec, 1, Nan::New(mat.at< cv::Vec<type, 4> >(idx)[1]));
    Nan::Set(vec, 2, Nan::New(mat.at< cv::Vec<type, 4> >(idx)[2]));
    Nan::Set(vec, 3, Nan::New(mat.at< cv::Vec<type, 4> >(idx)[3]));
    return vec;
  }
}

#endif
