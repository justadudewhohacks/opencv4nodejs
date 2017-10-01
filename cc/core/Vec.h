#include "macros.h"
#include <opencv2/core.hpp>
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#ifndef __FF_VEC_H__
#define __FF_VEC_H__

class Vec : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
	static NAN_METHOD(NewVec2);
	static NAN_METHOD(NewVec3);
	static NAN_METHOD(NewVec4);

	static std::vector<cv::Vec2d> unpackJSVec2Array(FF_ARR jsVec) {
		std::vector<cv::Vec2d> vecs;
		for (uint i = 0; i < jsVec->Length(); i++) {
			vecs.push_back(FF_UNWRAP_VEC2_AND_GET(Nan::To<v8::Object>(jsVec->Get(i)).ToLocalChecked()));
		}
		return vecs;
	};

	static std::vector<cv::Vec3d> unpackJSVec3Array(FF_ARR jsVec) {
		std::vector<cv::Vec3d> vecs;
		for (uint i = 0; i < jsVec->Length(); i++) {
			vecs.push_back(FF_UNWRAP_VEC3_AND_GET(Nan::To<v8::Object>(jsVec->Get(i)).ToLocalChecked()));
		}
		return vecs;
	};	
	
	static std::vector<cv::Vec4d> unpackJSVec4Array(FF_ARR jsVec) {
		std::vector<cv::Vec4d> vecs;
		for (uint i = 0; i < jsVec->Length(); i++) {
			vecs.push_back(FF_UNWRAP_VEC4_AND_GET(Nan::To<v8::Object>(jsVec->Get(i)).ToLocalChecked()));
		}
		return vecs;
	};

	static v8::Local<v8::Array> packJSVec4Array(std::vector<cv::Vec4d> vecs) {
		v8::Local<v8::Array> jsVecs = Nan::New<v8::Array>(vecs.size());
		for (int i = 0; i < jsVecs->Length(); i++) {
			v8::Local<v8::Object> jsVec4 = FF_NEW_INSTANCE(Vec4::constructor);
			FF_UNWRAP_VEC4_AND_GET(jsVec4) = vecs.at(i);
			jsVecs->Set(i, jsVec4);
		}
		return jsVecs;
	}


	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif