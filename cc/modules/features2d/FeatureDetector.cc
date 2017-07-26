#include "FeatureDetector.h"

void FeatureDetector::Init(v8::Local<v8::FunctionTemplate> ctor) {
	Nan::SetPrototypeMethod(ctor, "detect", FeatureDetector::Detect);
	Nan::SetPrototypeMethod(ctor, "compute", FeatureDetector::Compute);
};

NAN_METHOD(FeatureDetector::Detect) {
	FeatureDetector* self = Nan::ObjectWrap::Unwrap<FeatureDetector>(info[0]->ToObject());
  if (!info[0]->IsObject()) {
    return Nan::ThrowError("usage: detectKeypointsORB(Mat img)");      
  }

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
	FeatureDetector* self = Nan::ObjectWrap::Unwrap<FeatureDetector>(info[0]->ToObject());
  if (!info[0]->IsObject() || !info[1]->IsObject()) {
    return Nan::ThrowError("usage: computeDescriptors(Mat img, KeyPoints[] keyPoints)");      
  }

	cv::Mat mat = Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat;
	std::vector<cv::KeyPoint> kps = KeyPoint::unwrapJSKeyPointArray(v8::Local<v8::Array>::Cast(info[1]));

	cv::Mat desc;
	FF_TRY(self->getDetector()->compute(mat, kps, desc);)

	v8::Local<v8::Object> jsMat = Nan::NewInstance(Nan::New(Mat::constructor)->GetFunction()).ToLocalChecked();
	Nan::ObjectWrap::Unwrap<Mat>(jsMat)->setNativeProps(desc);
  info.GetReturnValue().Set(jsMat);
}