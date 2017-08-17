#include "FeatureDetector.h"

void FeatureDetector::Init(v8::Local<v8::FunctionTemplate> ctor) {
	Nan::SetPrototypeMethod(ctor, "detect", FeatureDetector::Detect);
	Nan::SetPrototypeMethod(ctor, "compute", FeatureDetector::Compute);
};

NAN_METHOD(FeatureDetector::Detect) {
  if (!info[0]->IsObject()) {
    return Nan::ThrowError("required argument image");      
  }
	FeatureDetector* self = Nan::ObjectWrap::Unwrap<FeatureDetector>(info.This());
	// TODO check instanceof Mat
	cv::Mat mat = Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat;
	std::vector<cv::KeyPoint> kps;
	FF_TRY(self->getDetector()->detect(mat, kps);)

	v8::Local<v8::Array> jsKps = Nan::New<v8::Array>(kps.size());
	uint i = 0;
	for (auto kp : kps) {
		v8::Local<v8::Object> handle = Nan::NewInstance(Nan::New(KeyPoint::constructor)->GetFunction()).ToLocalChecked();
		Nan::ObjectWrap::Unwrap<KeyPoint>(handle)->setNativeProps(i, kp);
		jsKps->Set(i++, handle);
	}
	info.GetReturnValue().Set(jsKps);
}

NAN_METHOD(FeatureDetector::Compute) {
  if (!info[0]->IsObject() || !info[1]->IsObject()) {
    return Nan::ThrowError("required arguments image, keyPoints");      
  }
	FeatureDetector* self = Nan::ObjectWrap::Unwrap<FeatureDetector>(info.This());
	cv::Mat mat = FF_UNWRAP_MAT_AND_GET(info[0]->ToObject());
	std::vector<cv::KeyPoint> kps;
	FF_UNWRAP_KEYPOINT_ARRAY(FF_CAST_ARRAY(info[1]), kps);
	cv::Mat desc;
	FF_TRY(self->getDetector()->compute(mat, kps, desc);)

	v8::Local<v8::Object> jsMat = Nan::NewInstance(Nan::New(Mat::constructor)->GetFunction()).ToLocalChecked();
	Nan::ObjectWrap::Unwrap<Mat>(jsMat)->setNativeProps(desc);
  info.GetReturnValue().Set(jsMat);
}