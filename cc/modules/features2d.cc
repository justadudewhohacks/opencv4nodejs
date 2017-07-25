#include "features2d.h"
#include "../core/Mat.h"
#include "../KeyPointMatch.h"
#include <iostream>
#include <opencv2/highgui.hpp>

static v8::Local<v8::Object> initializeEnum(const std::string enumNames[], int length);

NAN_MODULE_INIT(Features2d::Init) {
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  // xfeatures2d
  Nan::SetMethod(obj, "detectKeypointsSIFT", DetectKeypointsSIFT);
  Nan::SetMethod(obj, "detectKeypointsSURF", DetectKeypointsSURF);
  Nan::SetMethod(obj, "computeDescriptorsSIFT", ComputeDescriptorsSIFT);
  Nan::SetMethod(obj, "computeDescriptorsSURF", ComputeDescriptorsSURF);
  Nan::SetMethod(obj, "matchDescriptors", MatchDescriptors);

  // features2d
  Nan::SetMethod(obj, "detectKeypointsORB", DetectKeypointsORB);
  Nan::SetMethod(obj, "computeDescriptorsORB", ComputeDescriptorsORB);

  target->Set(Nan::New("features2d").ToLocalChecked(), obj);
};

NAN_METHOD(Features2d::DetectKeypointsSIFT) {
  if (!info[0]->IsObject()) {
    return Nan::ThrowError("usage: detectKeypointsSIFT(Mat img)");      
  }
  info.GetReturnValue().Set(
    detectKeyPoints(
      Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat, 
      cv::xfeatures2d::SIFT::create()
    )
  );
}

NAN_METHOD(Features2d::DetectKeypointsSURF) {
  if (!info[0]->IsObject()) {
    return Nan::ThrowError("usage: detectKeypointsSURF(Mat img)");      
  }
  info.GetReturnValue().Set(
    detectKeyPoints(
      Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat, 
      cv::xfeatures2d::SURF::create()
    )
  );
}

NAN_METHOD(Features2d::DetectKeypointsORB) {
  if (!info[0]->IsObject()) {
    return Nan::ThrowError("usage: detectKeypointsORB(Mat img)");      
  }
  info.GetReturnValue().Set(
    detectKeyPoints(
      Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat, 
      cv::ORB::create()
    )
  );
}

NAN_METHOD(Features2d::ComputeDescriptorsSIFT) {
  if (!info[0]->IsObject() || !info[1]->IsObject()) {
    return Nan::ThrowError("usage: computeDescriptors(Mat img, KeyPoints[] keyPoints)");      
  }
  info.GetReturnValue().Set(
    computeDescriptors(
      Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat, 
      v8::Local<v8::Array>::Cast(info[1]),
      cv::xfeatures2d::SIFT::create()
    )
  );
}

NAN_METHOD(Features2d::ComputeDescriptorsSURF) {
  if (!info[0]->IsObject() || !info[1]->IsObject()) {
    return Nan::ThrowError("usage: computeDescriptors(Mat img, KeyPoints[] keyPoints)");      
  }
  info.GetReturnValue().Set(
    computeDescriptors(
      Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat, 
      v8::Local<v8::Array>::Cast(info[1]),
      cv::xfeatures2d::SURF::create()
    )
  );
}

NAN_METHOD(Features2d::ComputeDescriptorsORB) {
  if (!info[0]->IsObject() || !info[1]->IsObject()) {
    return Nan::ThrowError("usage: computeDescriptors(Mat img, KeyPoints[] keyPoints)");      
  }
  info.GetReturnValue().Set(
    computeDescriptors(
      Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat, 
      v8::Local<v8::Array>::Cast(info[1]),
      cv::ORB::create()
    )
  );
}

NAN_METHOD(Features2d::MatchDescriptors) {

  if (!info[0]->IsObject() || !info[1]->IsObject() || !info[2]->IsObject() || !info[3]->IsObject()) {
    return Nan::ThrowError("usage: matchDescriptors(Mat descFrom, Mat descTo, KeyPoint[] kpsFrom, KeyPoint[] kpsTo, int matcherType)");      
  }
  cv::Mat descFrom = Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat;
  cv::Mat descTo = Nan::ObjectWrap::Unwrap<Mat>(info[2]->ToObject())->mat;
  v8::Local<v8::Array> jsKpsFrom = v8::Local<v8::Array>::Cast(info[1]);
  v8::Local<v8::Array> jsKpsTo = v8::Local<v8::Array>::Cast(info[3]);

  std::vector<cv::DMatch> matches;
  cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("FlannBased");
	FF_TRY(matcher->match(descFrom, descTo, matches);)

  v8::Local<v8::Array> jsMatches = Nan::New<v8::Array>(matches.size());
  int i = 0;
	for (auto match : matches) {
    v8::Local<v8::Object> handle = Nan::NewInstance(Nan::New(KeyPointMatch::constructor)->GetFunction()).ToLocalChecked();
    Nan::ObjectWrap::Unwrap<KeyPointMatch>(handle)->setNativeProps(
      Nan::ObjectWrap::Unwrap<KeyPoint>(Nan::To<v8::Object>(jsKpsFrom->Get(match.queryIdx)).ToLocalChecked()), 
      Nan::ObjectWrap::Unwrap<KeyPoint>(Nan::To<v8::Object>(jsKpsTo->Get(match.trainIdx)).ToLocalChecked()), 
      match.distance
    );
    jsMatches->Set(i++, handle);
	}
  info.GetReturnValue().Set(jsMatches);
}

v8::Local<v8::Value> Features2d::detectKeyPoints(cv::Mat mat, cv::Ptr<cv::FeatureDetector> detector) {
  std::vector<cv::KeyPoint> kps;
	
  try {
    detector->detect(mat, kps);
  } catch(std::exception &e) {
    Nan::ThrowError(e.what());
    return Nan::Null();
  } catch(...) {
    Nan::ThrowError("SEGFAULT");
    return Nan::Null();
  }

  v8::Local<v8::Array> jsKps = Nan::New<v8::Array>(kps.size());
  uint i = 0;
	for (auto kp : kps) {
    v8::Local<v8::Object> handle = Nan::NewInstance(Nan::New(KeyPoint::constructor)->GetFunction()).ToLocalChecked();
    Nan::ObjectWrap::Unwrap<KeyPoint>(handle)->setNativeProps(i, kp);
    jsKps->Set(i++, handle);
	}
  return jsKps;
}

v8::Local<v8::Value> Features2d::computeDescriptors(cv::Mat mat, v8::Local<v8::Array> jsKps, cv::Ptr<cv::FeatureDetector> detector) {
  std::vector<cv::KeyPoint> kps = KeyPoint::unwrapJSKps(jsKps);
  cv::Mat desc;
    try {
    detector->compute(mat, kps, desc);
  } catch(std::exception &e) {
    Nan::ThrowError(e.what());
    return Nan::Null();
  } catch(...) {
    Nan::ThrowError("SEGFAULT");
    return Nan::Null();
  }
  
  v8::Local<v8::Object> handle = Nan::NewInstance(Nan::New(Mat::constructor)->GetFunction()).ToLocalChecked();
  Nan::ObjectWrap::Unwrap<Mat>(handle)->setNativeProps(desc);
  return handle;
}