#include "xfeatures2d.h"
#include "SIFTDetector.h"
#include "SURFDetector.h"

NAN_MODULE_INIT(XFeatures2d::Init) {
	v8::Local<v8::Object> module = Nan::New<v8::Object>();
	SIFTDetector::Init(module);
	SURFDetector::Init(module);
	target->Set(Nan::New("xfeatures2d").ToLocalChecked(), module);
};