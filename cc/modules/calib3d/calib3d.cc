#include "calib3d.h"

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
		return Nan::ThrowError(FF_V8STRING("findHomography - args object required"));
	}
	v8::Local<v8::Object> args = info[0]->ToObject();

	v8::Local<v8::Object> jsSrcPoints, jsDstPoints;
	std::vector<cv::Point2d> srcPoints, dstPoints;
	FF_GET_JSPROP_REQUIRED(args, jsSrcPoints, srcPoints, ToObject)
	FF_GET_JSPROP_REQUIRED(args, jsDstPoints, dstPoints, ToObject)
	Nan::TryCatch tryCatch; 
	Point::unpackJSPoint2Array(srcPoints, v8::Local<v8::Array>::Cast(jsSrcPoints));
	Point::unpackJSPoint2Array(dstPoints, v8::Local<v8::Array>::Cast(jsDstPoints));
	if (tryCatch.HasCaught()) {
		return info.GetReturnValue().Set(tryCatch.ReThrow());
	}
	int method = 0; 
	double ransacReprojThreshold = 3;
	cv::OutputArray mask = cv::noArray();
	int maxIters = 2000;
	double confidence = 0.995;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, method, IsInt32, Int32Value)
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, ransacReprojThreshold, IsNumber, NumberValue)
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, maxIters, IsInt32, Int32Value)
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, confidence, IsNumber, NumberValue)

	if (FF_HAS_JS_PROP(args, mask)) {
		Nan::ObjectWrap::Unwrap<Mat>(FF_GET_JSPROP(args, mask)->ToObject())->mat.copyTo(mask);
	}

	cv::Mat homography;
	FF_TRY_CATCH(homography = cv::findHomography(srcPoints, dstPoints, method, ransacReprojThreshold, mask, maxIters, confidence);)
	if (tryCatch.HasCaught()) {
		return info.GetReturnValue().Set(tryCatch.ReThrow());
	}
	v8::Local<v8::Object> jsMat = Nan::NewInstance(Nan::New(Mat::constructor)->GetFunction()).ToLocalChecked();
	Nan::ObjectWrap::Unwrap<Mat>(jsMat)->setNativeProps(homography);
	info.GetReturnValue().Set(jsMat);
}