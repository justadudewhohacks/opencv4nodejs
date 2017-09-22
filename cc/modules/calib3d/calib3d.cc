#include "calib3d.h"

NAN_MODULE_INIT(Calib3d::Init) {
	FF_SET_JS_PROP(target, REGULAR, Nan::New<v8::Integer>(0));
	FF_SET_JS_PROP(target, LMEDS, Nan::New<v8::Integer>(cv::LMEDS));
	FF_SET_JS_PROP(target, RANSAC, Nan::New<v8::Integer>(cv::RANSAC));
	FF_SET_JS_PROP(target, RHO, Nan::New<v8::Integer>(cv::RHO));

	Nan::SetMethod(target, "findHomography", FindHomography);
};

NAN_METHOD(Calib3d::FindHomography) {
	FF_METHOD_CONTEXT("FindHomography");

	FF_ARG_ARRAY(0, FF_ARR jsSrcPoints);
	FF_ARG_ARRAY(1, FF_ARR jsDstPoints);

	// TODO FF_ARG_UNPACK_ARRAY_INSTANCE
	Nan::TryCatch tryCatch;
	std::vector<cv::Point2d> srcPoints, dstPoints;
	Point::unpackJSPoint2Array(srcPoints, jsSrcPoints);
	Point::unpackJSPoint2Array(dstPoints, jsDstPoints);
	if (tryCatch.HasCaught()) {
		return info.GetReturnValue().Set(tryCatch.ReThrow());
	}

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(2) && info[2]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[2]->ToObject() : FF_NEW_OBJ();

	FF_GET_UINT_IFDEF(optArgs, uint method, "method", 0);
	FF_GET_NUMBER_IFDEF(optArgs, double ransacReprojThreshold, "ransacReprojThreshold", 3);
	FF_GET_UINT_IFDEF(optArgs, uint maxIters, "maxIters", 2000);
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Mat mask, "mask", Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat, cv::noArray().getMat())
	FF_GET_NUMBER_IFDEF(optArgs, double confidence, "confidence", 0.995);
	if (!hasOptArgsObj) {
		FF_ARG_UINT_IFDEF(2, method, method);
		FF_ARG_NUMBER_IFDEF(3, ransacReprojThreshold, ransacReprojThreshold);
		FF_ARG_UINT_IFDEF(4, maxIters, maxIters);
		FF_ARG_INSTANCE_IFDEF(5, mask, Mat::constructor, FF_UNWRAP_MAT_AND_GET, mask);
		FF_ARG_NUMBER_IFDEF(4, confidence, confidence);
	}

	FF_OBJ jsMat = FF_NEW_INSTANCE(Mat::constructor);
	FF_UNWRAP_MAT_AND_GET(jsMat) = cv::findHomography(srcPoints, dstPoints, method, ransacReprojThreshold, mask, maxIters, confidence);
	FF_RETURN(jsMat);
}