#include "macros.h"
#include <opencv2/core.hpp>
#include "Point.h"
#include "Size.h"
#include "Rect.h"

#ifndef __FF_ROTATEDRECT_H__
#define __FF_ROTATEDRECT_H__

class RotatedRect : public FF::ObjectWrap<RotatedRect> {
public:
	typedef cv::RotatedRect Type;

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "RotatedRect";
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static FF_GETTER(RotatedRect, GetAngle, self.angle);

	static NAN_GETTER(GetCenter) {
		v8::Local<v8::Object> jsCenter = FF::newInstance(Nan::New(Point2::constructor));
		Point2::unwrap(jsCenter)->setNativeObject(FF_UNWRAP(info.This(), RotatedRect)->self.center);
		info.GetReturnValue().Set(jsCenter);
	}

	static NAN_GETTER(GetSize) {
		v8::Local<v8::Object> jsSize = FF::newInstance(Nan::New(Size::constructor));
		Size::unwrap(jsSize)->setNativeObject(FF_UNWRAP(info.This(), RotatedRect)->self.size);
		info.GetReturnValue().Set(jsSize);
	}

	static NAN_METHOD(BoundingRect) {
		v8::Local<v8::Object> jsRect = FF::newInstance(Nan::New(Rect::constructor));
		FF_UNWRAP(jsRect, Rect)->self = FF_UNWRAP(info.This(), RotatedRect)->self.boundingRect();
		info.GetReturnValue().Set(jsRect);
	}
};

#endif