#include "features2d.h"
#include "GFTTDetector.h"

NAN_MODULE_INIT(Features2d::Init) {
  v8::Local<v8::Object> module = Nan::New<v8::Object>();
  GFTTDetector::Init(module);
  target->Set(Nan::New("features2d").ToLocalChecked(), module);
};