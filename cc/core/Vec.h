#include "macros.h"
#include <opencv2/core.hpp>
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Vec6.h"

#ifndef __FF_VEC_H__
#define __FF_VEC_H__

class Vec : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
	static NAN_METHOD(NewVec2);
	static NAN_METHOD(NewVec3);
	static NAN_METHOD(NewVec4);
	static NAN_METHOD(NewVec6);

	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif
