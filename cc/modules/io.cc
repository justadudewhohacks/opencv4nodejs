#include "io.h"
#include "Mat.h"
#include "features2d/KeyPointMatch.h"
#include<iostream>


NAN_MODULE_INIT(Io::Init) {
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  Nan::SetMethod(obj, "imread", Imread);
  Nan::SetMethod(obj, "imshow", Imshow);
  Nan::SetMethod(obj, "imsave", Imsave);
  Nan::SetMethod(obj, "drawKeyPoints", DrawKeyPoints);
  Nan::SetMethod(obj, "drawMatches", DrawMatches);
  target->Set(Nan::New("io").ToLocalChecked(), obj);
};

NAN_METHOD(Io::Imread) {
  if (!info[0]->IsString() || !info[1]->IsFunction()) {
    return Nan::ThrowError("usage: imread(string path, func cb)");      
  }

  std::string path = std::string(*Nan::Utf8String(info[0]->ToString()));
  v8::Local<v8::Function> cb = v8::Local<v8::Function>::Cast(info[1]);
  v8::Local<v8::Value> cbArgs[2];
  cbArgs[0] = Nan::Null();
  cbArgs[1] = Nan::Null();

  try {
    cv::Mat mat = cv::imread(path);
    if (mat.rows == 0 && mat.cols == 0) {
      cbArgs[0] = Nan::Error("imread empty mat");
    } else {
      v8::Local<v8::Object> handle = Nan::NewInstance(Nan::New(Mat::constructor)->GetFunction()).ToLocalChecked();
      Nan::ObjectWrap::Unwrap<Mat>(handle)->setNativeProps(mat);
      cbArgs[1] = handle;
    }
  } catch(std::exception &e) {
    cbArgs[0] = Nan::Error(e.what());
  } catch(...) {
    cbArgs[0] = Nan::Error("... Exception");
  }

  cb->Call(Nan::GetCurrentContext()->Global(), 2, cbArgs);
}

NAN_METHOD(Io::Imsave) {
  if (!info[0]->IsString() || !info[1]->IsObject()) {
    return Nan::ThrowError("usage: imsave(string path, Mat img, func cb)");      
  }

  std::string path = std::string(*Nan::Utf8String(info[0]->ToString()));
  cv::Mat mat = Nan::ObjectWrap::Unwrap<Mat>(info[1]->ToObject())->mat;
  v8::Local<v8::Function> cb = v8::Local<v8::Function>::Cast(info[2]);
  v8::Local<v8::Value> cbArgs[2];
  cbArgs[0] = Nan::Null();
  cbArgs[1] = Nan::Null();
  try {
    cv::imwrite(path, mat);
    cbArgs[1] = info[1];
  } catch(std::exception &e) {
    cbArgs[0] = Nan::Error(e.what());
  } catch(...) {
    cbArgs[0] = Nan::Error("... Exception");
  }

  cb->Call(Nan::GetCurrentContext()->Global(), 2, cbArgs);
}

NAN_METHOD(Io::Imshow) {
  if (!info[0]->IsString() || !info[1]->IsObject()) {
    return Nan::ThrowError("usage: imshow(string winName, Mat img)");      
  }
  std::string winName = std::string(*Nan::Utf8String(info[0]->ToString()));
  Mat* mat = Nan::ObjectWrap::Unwrap<Mat>(info[1]->ToObject());

  try {
    cv::imshow(winName, mat->mat);
    cv::waitKey();
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
    Nan::ThrowError(e.what());
  } catch(...) {
    std::cout << "... Exception" << std::endl;
    Nan::ThrowError("... Exception");
  }
}

NAN_METHOD(Io::DrawKeyPoints) {
  if (!info[0]->IsObject() || !info[1]->IsObject()) {
    return Nan::ThrowError("usage: drawKeyPoints(Mat img, KeyPoints[] kps)");      
  }
  cv::Mat mat = Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat;
  v8::Local<v8::Array> jsKps = v8::Local<v8::Array>::Cast(info[1]);

  std::vector<cv::KeyPoint> kps;
  for (uint i = 0; i < jsKps->Length(); i++) {
    KeyPoint* kp = Nan::ObjectWrap::Unwrap<KeyPoint>(Nan::To<v8::Object>(jsKps->Get(i)).ToLocalChecked());
    kps.push_back(kp->keyPoint);
  }

  cv::Mat drawImg;
  cv::drawKeypoints(mat, kps, drawImg);
  v8::Local<v8::Object> handle = Nan::NewInstance(Nan::New(Mat::constructor)->GetFunction()).ToLocalChecked();
  Nan::ObjectWrap::Unwrap<Mat>(handle)->mat = drawImg;
  info.GetReturnValue().Set(handle);
}

NAN_METHOD(Io::DrawMatches) {
  if (!info[0]->IsObject() || !info[1]->IsObject() || !info[2]->IsObject()) {
    return Nan::ThrowError("usage: drawKeyPoints(Mat imgFrom, Mat imgTo, KeyPointMatches[] matches)");      
  }
  cv::Mat imgFrom = Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat;
  cv::Mat imgTo = Nan::ObjectWrap::Unwrap<Mat>(info[1]->ToObject())->mat;
  v8::Local<v8::Array> jsMatches = v8::Local<v8::Array>::Cast(info[2]);

  std::vector<cv::KeyPoint> kpsFrom, kpsTo;
  std::vector<cv::DMatch> dMatches;
  for (uint i = 0; i < jsMatches->Length(); i++) {
    KeyPointMatch* match = Nan::ObjectWrap::Unwrap<KeyPointMatch>(Nan::To<v8::Object>(jsMatches->Get(i)).ToLocalChecked());
    kpsFrom.push_back(match->getKpFrom()->keyPoint);
    kpsTo.push_back(match->getKpTo()->keyPoint);
    dMatches.push_back(cv::DMatch(i, i, match->distance));
  }

  cv::Mat drawImg;
  cv::drawMatches(imgFrom, kpsFrom, imgTo, kpsTo, dMatches, drawImg);
  v8::Local<v8::Object> handle = Nan::NewInstance(Nan::New(Mat::constructor)->GetFunction()).ToLocalChecked();
  Nan::ObjectWrap::Unwrap<Mat>(handle)->mat = drawImg;
  info.GetReturnValue().Set(handle);
}