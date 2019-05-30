#include <opencv2/core.hpp>
#include "NativeNodeUtils.h"
#include "CatchCvExceptionWorker.h"
#include "Size.h"
#include "macros.h"

#ifndef __FF_RECT_H__
#define __FF_RECT_H__

class Rect : public FF::ObjectWrap<Rect> {
public:
	typedef cv::Rect2d Type;

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "Rect";
	}

	static NAN_MODULE_INIT(Init);

	static FF_GETTER(Rect, GetX, self.x);
	static FF_GETTER(Rect, GetY, self.y);
	static FF_GETTER(Rect, GetWidth, self.width);
	static FF_GETTER(Rect, GetHeight, self.height);

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