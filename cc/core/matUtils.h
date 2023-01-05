#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_MATUTILS_H__
#define __FF_MATUTILS_H__



namespace FF {
	/**
	 * 2,3-Dimmentions Macro seters for a single Value
	 */
	template<typename type>
	static inline void matPutVal(cv::Mat mat, v8::Local<v8::Value> value, int r, int c) {
		mat.at<type>(r, c) = (type)value->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
	}

	template<typename type>
	static inline void matPutVal(cv::Mat mat, v8::Local<v8::Value> value, int r, int c, int z) {
		mat.at<type>(r, c, z) = (type)value->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
	}

	/**
	 * 2,3-Dimmentions Macro seters for a Vec<2> Value
	 */
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
	/**
	 * 2,3-Dimmentions Macro seters for a Vec<3> Value
	 */
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
	/**
	 * 2,3-Dimmentions Macro seters for a Vec<4> Value
	 */
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

	/**
	 * 2,3,n-Dimmentions Macro getters for single Value
	 */
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

	/**
	 * 2,3,n-Dimmentions Macro getters for Vec<2> Value
	 */
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

	/**
	 * 2,3,n-Dimmentions Macro getters for Vec<3> Value
	 */
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

	/**
	 * 2,3,n-Dimmentions Macro getters for Vec<4> Value
	 */
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
