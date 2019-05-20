#include "BackgroundSubtractor.h"
#include "Mat.h"

void BackgroundSubtractor::Init(v8::Local<v8::FunctionTemplate> ctor) {
	Nan::SetPrototypeMethod(ctor, "apply", BackgroundSubtractor::Apply);
};

NAN_METHOD(BackgroundSubtractor::Apply) {
	FF::TryCatch tryCatch;
	cv::Mat frame;
	double learningRate = -1;
	if (
		Mat::Converter::arg(0, &frame, info) ||
		DoubleConverter::optArg(1, &learningRate, info)
		) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("BackgroundSubtractor::Apply");
		tryCatch.throwNew(err);
		return;
	}

	BackgroundSubtractor* self = FF_UNWRAP(info.This(), BackgroundSubtractor);
	self->getSubtractor()->apply(frame, self->fgMask, learningRate);
	FF_OBJ jsMat = FF::newInstance(Nan::New(Mat::constructor));
	FF_UNWRAP_MAT_AND_GET(jsMat) = self->fgMask;
	FF_RETURN(jsMat);
}