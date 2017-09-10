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