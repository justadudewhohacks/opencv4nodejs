#include "imgproc.h"
#include "imgprocConstants.h"
#include "Point2.h"
#include "Size.h"
#include "Mat.h"

NAN_MODULE_INIT(Imgproc::Init) {
  v8::Local<v8::Object> module = Nan::New<v8::Object>();
	initImgProcConstants(module);
	Nan::SetMethod(module, "getStructuringElement", GetStructuringElement);
  target->Set(Nan::New("imgproc").ToLocalChecked(), module);
};

NAN_METHOD(Imgproc::GetStructuringElement) {
	FF_REQUIRE_ARGS_OBJ("Imgproc::GetStructuringElement");
	int shape;
	v8::Local<v8::Object> jsSize;
	cv::Point2i anchor = cv::Point2i(-1, -1);
	FF_DESTRUCTURE_JSPROP_REQUIRED(args, shape, Int32Value);
	FF_GET_JSPROP_REQUIRED(args, jsSize, size, ToObject);
	if (args->HasOwnProperty(FF_V8STRING("anchor"))) {
		anchor = Nan::ObjectWrap::Unwrap<Point2>(FF_GET_JSPROP(args, anchor)->ToObject())->pt;
	}
	v8::Local<v8::Object> jsKernel = Nan::NewInstance(Nan::New(Mat::constructor)->GetFunction()).ToLocalChecked();
	Nan::ObjectWrap::Unwrap<Mat>(jsKernel)->setNativeProps(
		cv::getStructuringElement(shape, Nan::ObjectWrap::Unwrap<Size>(jsSize)->size, anchor)
	);
	info.GetReturnValue().Set(jsKernel);
}