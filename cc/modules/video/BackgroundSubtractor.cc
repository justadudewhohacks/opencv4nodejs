#include "BackgroundSubtractor.h"
#include "Mat.h"

void BackgroundSubtractor::Init(v8::Local<v8::FunctionTemplate> ctor) {
	Nan::SetPrototypeMethod(ctor, "apply", BackgroundSubtractor::Apply);
};

NAN_METHOD(BackgroundSubtractor::Apply) {
	FF_METHOD_CONTEXT("BackgroundSubtractorKNN::Apply");

	FF_ARG_INSTANCE(0, cv::Mat frame, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_NUMBER_IFDEF(1, double learningRate, -1);

	BackgroundSubtractor* self = FF_UNWRAP(info.This(), BackgroundSubtractor);
	self->getSubtractor()->apply(frame, self->fgMask, learningRate);
	FF_OBJ jsMat = FF_NEW_INSTANCE(Mat::constructor);
	FF_UNWRAP_MAT_AND_GET(jsMat) = self->fgMask;
	FF_RETURN(jsMat);
}