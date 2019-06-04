#include <opencv2/core.hpp>
#include "NativeNodeUtils.h"
#include "CatchCvExceptionWorker.h"
#include "Size.h"
#include "macros.h"

#ifndef __FF_RECT_H__
#define __FF_RECT_H__

class Rect : public FF::ObjectWrap<Rect, cv::Rect2d> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "Rect";
	}

	static NAN_MODULE_INIT(Init);

	FF_ACCESSORS(x, FF::DoubleConverter);
	FF_ACCESSORS(y, FF::DoubleConverter);
	FF_ACCESSORS(width, FF::DoubleConverter);
	FF_ACCESSORS(height, FF::DoubleConverter);

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