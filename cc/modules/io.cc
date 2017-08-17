#include "io.h"
#include "Mat.h"
#include <iostream>


NAN_MODULE_INIT(Io::Init) {
  Nan::SetMethod(target, "imread", Imread);
  Nan::SetMethod(target, "imshow", Imshow);
  Nan::SetMethod(target, "imsave", Imsave);
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