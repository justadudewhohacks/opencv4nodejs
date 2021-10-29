#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMG_HASH

#include "PHash.h"

Nan::Persistent<v8::FunctionTemplate> PHash::constructor;

NAN_MODULE_INIT(PHash::Init)
{
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(PHash::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  ImgHashBase::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("PHash"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::Set(target, FF::newString("PHash"), FF::getFunction(ctor));
};

NAN_METHOD(PHash::New)
{
  FF::TryCatch tryCatch("PHash::New");
  FF_ASSERT_CONSTRUCT_CALL();

  PHash *self = new PHash();
  self->Wrap(info.Holder());
  self->imgHashBase = cv::img_hash::PHash::create();

  info.GetReturnValue().Set(info.Holder());
};

#endif
