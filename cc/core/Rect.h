#include <opencv2/core.hpp>
#include "NativeNodeUtils.h"
#include "CatchCvExceptionWorker.h"
#include "Size.h"
#include "macros.h"

#ifndef __FF_RECT_H__
#define __FF_RECT_H__

class Rect : public Nan::ObjectWrap {
public:
	cv::Rect2d rect;

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Rect2d* getNativeObjectPtr() { return &rect; }
	cv::Rect2d getNativeObject() { return rect; }

	typedef InstanceConverter<Rect, cv::Rect2d> Converter;

	static const char* getClassName() {
		return "Rect";
	}

	static NAN_MODULE_INIT(Init);

	static FF_GETTER(Rect, GetX, rect.x);
	static FF_GETTER(Rect, GetY, rect.y);
	static FF_GETTER(Rect, GetWidth, rect.width);
	static FF_GETTER(Rect, GetHeight, rect.height);

	static NAN_METHOD(New);
	static NAN_METHOD(And);
	static NAN_METHOD(Or);
	static NAN_METHOD(ToSquare);
	static NAN_METHOD(ToSquareAsync);
	static NAN_METHOD(Pad);
	static NAN_METHOD(PadAsync);
	static NAN_METHOD(Rescale);
	static NAN_METHOD(RescaleAsync);

};

#endif