#include "imgproc.h"

NAN_MODULE_INIT(Imgproc::Init) {
  v8::Local<v8::Object> module = Nan::New<v8::Object>();

	v8::Local<v8::Object> borderTypes = Nan::New<v8::Object>();
	FF_SET_JS_PROP(borderTypes, BORDER_CONSTANT, Nan::New<v8::Integer>(cv::BORDER_CONSTANT));
	FF_SET_JS_PROP(borderTypes, BORDER_REPLICATE, Nan::New<v8::Integer>(cv::BORDER_REPLICATE));
	FF_SET_JS_PROP(borderTypes, BORDER_REFLECT, Nan::New<v8::Integer>(cv::BORDER_REFLECT));
	FF_SET_JS_PROP(borderTypes, BORDER_WRAP, Nan::New<v8::Integer>(cv::BORDER_WRAP));
	FF_SET_JS_PROP(borderTypes, BORDER_REFLECT_101, Nan::New<v8::Integer>(cv::BORDER_REFLECT_101));
	FF_SET_JS_PROP(borderTypes, BORDER_TRANSPARENT, Nan::New<v8::Integer>(cv::BORDER_TRANSPARENT));
	FF_SET_JS_PROP(borderTypes, BORDER_ISOLATED, Nan::New<v8::Integer>(cv::BORDER_ISOLATED));
	FF_SET_JS_PROP(borderTypes, BORDER_DEFAULT, Nan::New<v8::Integer>(cv::BORDER_DEFAULT));
	module->Set(FF_V8STRING("borderTypes"), borderTypes);

	v8::Local<v8::Object> interpolationFlags = Nan::New<v8::Object>();
	FF_SET_JS_PROP(borderTypes, INTER_NEAREST, Nan::New<v8::Integer>(cv::INTER_NEAREST));
	FF_SET_JS_PROP(borderTypes, INTER_LINEAR, Nan::New<v8::Integer>(cv::INTER_LINEAR));
	FF_SET_JS_PROP(borderTypes, INTER_CUBIC, Nan::New<v8::Integer>(cv::INTER_CUBIC));
	FF_SET_JS_PROP(borderTypes, INTER_AREA, Nan::New<v8::Integer>(cv::INTER_AREA));
	FF_SET_JS_PROP(borderTypes, INTER_LANCZOS4, Nan::New<v8::Integer>(cv::INTER_LANCZOS4));
	FF_SET_JS_PROP(borderTypes, INTER_MAX, Nan::New<v8::Integer>(cv::INTER_MAX));
	FF_SET_JS_PROP(borderTypes, WARP_FILL_OUTLIERS, Nan::New<v8::Integer>(cv::WARP_FILL_OUTLIERS));
	FF_SET_JS_PROP(borderTypes, WARP_INVERSE_MAP, Nan::New<v8::Integer>(cv::WARP_INVERSE_MAP));
	module->Set(FF_V8STRING("interpolationFlags"), borderTypes);

  target->Set(Nan::New("imgproc").ToLocalChecked(), module);
};