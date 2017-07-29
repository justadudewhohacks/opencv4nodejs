#include "ximgproc.h"
#include "SuperpixelSEEDS.h"

NAN_MODULE_INIT(XImgproc::Init) {
  v8::Local<v8::Object> module = Nan::New<v8::Object>();
	SuperpixelSEEDS::Init(module);
  target->Set(Nan::New("ximgproc").ToLocalChecked(), module);
}