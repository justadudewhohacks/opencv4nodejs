#include "imgproc.h"
#include "imgprocConstants.h"
#include "Point2.h"
#include "Size.h"
#include "Mat.h"

NAN_MODULE_INIT(Imgproc::Init) {
  v8::Local<v8::Object> module = Nan::New<v8::Object>();
	ImgprocConstants::init(module);
	Nan::SetMethod(module, "getStructuringElement", GetStructuringElement);
  target->Set(FF_V8STRING("imgproc"), module);
};

NAN_METHOD(Imgproc::GetStructuringElement) {
	FF_REQUIRE_ARGS_OBJ("Imgproc::GetStructuringElement");
	int shape;
	v8::Local<v8::Object> jsSize;
	cv::Point2i anchor = cv::Point2i(-1, -1);
	FF_DESTRUCTURE_JSPROP_REQUIRED(args, shape, Int32Value);
	FF_GET_JSPROP_REQUIRED(args, jsSize, size, ToObject);
	if (FF_HAS_JS_PROP(args, anchor)) {
		anchor = Nan::ObjectWrap::Unwrap<Point2>(FF_GET_JSPROP(args, anchor)->ToObject())->pt;
	}
	v8::Local<v8::Object> jsKernel = FF_NEW(Mat::constructor);
	FF_UNWRAP_MAT(jsKernel)->setNativeProps(
		cv::getStructuringElement(shape, FF_UNWRAP_SIZE_AND_GET(jsSize), anchor)
	);
	info.GetReturnValue().Set(jsKernel);
}