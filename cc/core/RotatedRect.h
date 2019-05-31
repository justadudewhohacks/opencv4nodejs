#include "macros.h"
#include <opencv2/core.hpp>
#include "Point.h"
#include "Size.h"
#include "Rect.h"

#ifndef __FF_ROTATEDRECT_H__
#define __FF_ROTATEDRECT_H__

class RotatedRect : public FF::ObjectWrap<RotatedRect, cv::RotatedRect> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "RotatedRect";
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static FF_GETTER(RotatedRect, GetAngle, self.angle);

	static NAN_GETTER(GetCenter) {
		info.GetReturnValue().Set(Point2::Converter::wrap(unwrapSelf(info).center));
	}
	static NAN_GETTER(GetSize) {
		info.GetReturnValue().Set(Size::Converter::wrap(unwrapSelf(info).size));
	}
	static NAN_METHOD(BoundingRect) {
		info.GetReturnValue().Set(Size::Converter::wrap(unwrapSelf(info).size));
	}
};

#endif