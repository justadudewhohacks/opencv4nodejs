#include "macros.h"
#include <opencv2/imgproc.hpp>
#include "KeyPoint.h"

#ifndef FF_KEYPOINTMATCH_H_
#define FF_KEYPOINTMATCH_H_

class KeyPointMatch : public Nan::ObjectWrap {
public:
  Nan::Persistent<v8::Object> kpFrom;
  Nan::Persistent<v8::Object> kpTo;
  float distance;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static NAN_GETTER(GetKpFrom);
  static NAN_GETTER(GetKpTo);
  static NAN_GETTER(GetDistance);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  void setNativeProps(KeyPoint* kpFrom, KeyPoint* kpTo, float distance);
  KeyPoint* getKpFrom() {
    return Nan::ObjectWrap::Unwrap<KeyPoint>(Nan::New(this->kpFrom));
  }

  KeyPoint* getKpTo() {
    return Nan::ObjectWrap::Unwrap<KeyPoint>(Nan::New(this->kpTo));
  }
};

#endif