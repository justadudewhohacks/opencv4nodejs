#include "photo.h"
#include "../core/Mat.h"
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/videostab.hpp>

NAN_MODULE_INIT(Photo::Init) {
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  Nan::SetMethod(obj, "fastNlMeansDenoisingColored", FastNlMeansDenoisingColored);
  target->Set(Nan::New("photo").ToLocalChecked(), obj);
};

NAN_METHOD(Photo::FastNlMeansDenoisingColored) {
  if (!info[0]->IsObject()) {
    return Nan::ThrowError("usage: fastNlMeansDenoisingColored(Mat src, float h=3, float hColor=3, int templateWindowSize=7, int searchWindowSize=21 )");      
  }
  cv::Mat mat = Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat;

  cv::Mat dst;
  try {
    cv::fastNlMeansDenoisingColored(mat, dst);
  } catch(std::exception &e) {
    return Nan::ThrowError(e.what());
  } catch(...) {
    return Nan::ThrowError("... Exception");
  }

  v8::Local<v8::Object> handle = Nan::NewInstance(Nan::New(Mat::constructor)->GetFunction()).ToLocalChecked();
  Nan::ObjectWrap::Unwrap<Mat>(handle)->mat = dst;
  info.GetReturnValue().Set(handle);
}