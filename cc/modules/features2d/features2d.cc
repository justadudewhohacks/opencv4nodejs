#include "features2d.h"
#include "KeyPoint.h"
#include "KeyPointMatch.h"
#include "GFTTDetector.h"
#include "ORBDetector.h"

NAN_MODULE_INIT(Features2d::Init) {
  v8::Local<v8::Object> module = Nan::New<v8::Object>();
	KeyPoint::Init(module);
	KeyPointMatch::Init(module);
  GFTTDetector::Init(module);
	ORBDetector::Init(module);
  target->Set(Nan::New("features2d").ToLocalChecked(), module);
};