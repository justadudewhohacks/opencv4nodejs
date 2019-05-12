#include "macros.h"
#include <opencv2/core.hpp>
#include "Point.h"
#include "Size.h"
#include "Rect.h"

#ifndef __FF_ROTATEDRECT_H__
#define __FF_ROTATEDRECT_H__

class RotatedRect : public Nan::ObjectWrap {
public:
	cv::RotatedRect rect;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER(RotatedRect, GetAngle, rect.angle);

	static NAN_GETTER(GetCenter) {
		v8::Local<v8::Object> jsCenter = FF::newInstance(Nan::New(Point2::constructor));
		FF_UNWRAP_PT2_AND_GET(jsCenter) = FF_UNWRAP(info.This(), RotatedRect)->rect.center;
		info.GetReturnValue().Set(jsCenter);
	}

	static NAN_GETTER(GetSize) {
		v8::Local<v8::Object> jsSize = FF::newInstance(Nan::New(Size::constructor));
		FF_UNWRAP_SIZE_AND_GET(jsSize) = FF_UNWRAP(info.This(), RotatedRect)->rect.size;
		info.GetReturnValue().Set(jsSize);
	}

	static NAN_METHOD(BoundingRect) {
		v8::Local<v8::Object> jsRect = FF::newInstance(Nan::New(Rect::constructor));
		FF_UNWRAP(jsRect, Rect)->rect = FF_UNWRAP(info.This(), RotatedRect)->rect.boundingRect();
		info.GetReturnValue().Set(jsRect);
	}

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::RotatedRect* getNativeObjectPtr() { return &rect; }
	cv::RotatedRect getNativeObject() { return rect; }

	typedef InstanceConverter<RotatedRect, cv::RotatedRect> Converter;

	static const char* getClassName() {
		return "RotatedRect";
	}
};

#endif