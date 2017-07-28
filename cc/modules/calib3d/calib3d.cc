#include "calib3d.h"

#define FF_SET_JS_PROP(obj, prop, val) \
	Nan::Set(obj, FF_V8STRING(#prop), val)

NAN_MODULE_INIT(Calib3d::Init) {
  v8::Local<v8::Object> module = Nan::New<v8::Object>();
	v8::Local<v8::Object> alg = Nan::New<v8::Object>();
	FF_SET_JS_PROP(alg, REGULAR, Nan::New<v8::Integer>(0));
	FF_SET_JS_PROP(alg, LMEDS, Nan::New<v8::Integer>(cv::LMEDS));
	FF_SET_JS_PROP(alg, RANSAC, Nan::New<v8::Integer>(cv::RANSAC));
	FF_SET_JS_PROP(alg, RHO, Nan::New<v8::Integer>(cv::RHO));
	module->Set(FF_V8STRING("robustnessAlgorithm"), alg);
	Nan::SetMethod(module, "findHomography", FindHomography);
  target->Set(Nan::New("calib3d").ToLocalChecked(), module);
};

NAN_METHOD(Calib3d::FindHomography) {
	if (!info[0]->IsObject()) {
		// TODO usage messages
		return Nan::ThrowError(FF_V8STRING("findHomography - empty args object"));
	}
	v8::Local<v8::Object> args = info[0]->ToObject();

	std::vector<cv::Point2d> srcPoints = Point::unpackJSPoint2Array(v8::Local<v8::Array>::Cast(FF::getCheckedJsProp(args, "srcPoints")));
	std::vector<cv::Point2d> dstPoints = Point::unpackJSPoint2Array(v8::Local<v8::Array>::Cast(FF::getCheckedJsProp(args, "dstPoints")));
	int method = 0; 
	double ransacReprojThreshold = 3;
	cv::OutputArray mask = cv::noArray();
	int maxIters = 2000;
	double confidence = 0.995;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, method, IsInt32, Int32Value)
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, ransacReprojThreshold, IsNumber, NumberValue)
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, maxIters, IsInt32, Int32Value)
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, confidence, IsNumber, NumberValue)

	if (args->HasOwnProperty(FF_V8STRING("mask"))) {
		Nan::ObjectWrap::Unwrap<Mat>(FF_GET_JSPROP(args, mask))->mat.copyTo(mask);
	}

	cv::Mat homography;
	FF_TRY(homography = cv::findHomography(srcPoints, dstPoints, method, ransacReprojThreshold, mask, maxIters, confidence);)
	v8::Local<v8::Object> jsMat = Nan::NewInstance(Nan::New(Mat::constructor)->GetFunction()).ToLocalChecked();
	Nan::ObjectWrap::Unwrap<Mat>(jsMat)->setNativeProps(homography);
	info.GetReturnValue().Set(jsMat);
}