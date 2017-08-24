#include "BackgroundSubtractor.h"
#include "Mat.h"

void BackgroundSubtractor::Init(v8::Local<v8::FunctionTemplate> ctor) {
	Nan::SetPrototypeMethod(ctor, "apply", BackgroundSubtractor::Apply);
};

NAN_METHOD(BackgroundSubtractor::Apply) {
	double learningRate = -1;
	FF_REQUIRE_INSTANCE(Mat::constructor, info[0], "expected arg0 to be instance of Mat");
	cv::Mat frame = FF_UNWRAP_MAT_AND_GET(info[0]->ToObject());
	if (info[1]->IsNumber()) {
		learningRate = info[1]->NumberValue();
	}

	BackgroundSubtractor* self = FF_UNWRAP(info.This(), BackgroundSubtractor);
	self->getSubtractor()->apply(frame, self->fgMask, learningRate);

	v8::Local<v8::Object> jsMat = FF_NEW(Mat::constructor);
	FF_UNWRAP_MAT_AND_GET(jsMat) = self->fgMask;
	info.GetReturnValue().Set(jsMat);
}