#ifdef HAVE_FACE

#include "FacemarkAAMData.h"

#if CV_VERSION_MINOR >= 4

Nan::Persistent<v8::FunctionTemplate> FacemarkAAMData::constructor;

NAN_MODULE_INIT(FacemarkAAMData::Init) {
  v8::Local<v8::FunctionTemplate> ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkAAMData::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF_NEW_STRING("FacemarkAAMData"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("s0"), s0Get, s0Set);

  target->Set(FF_NEW_STRING("FacemarkAAMData"), ctor->GetFunction());
};

NAN_METHOD(FacemarkAAMData::New) {
  FF_METHOD_CONTEXT("FacemarkAAMData::New");
  FacemarkAAMData *self = new FacemarkAAMData();
  self->data = cv::face::FacemarkAAM::Data();
  self->Wrap(info.Holder());
  FF_RETURN(info.Holder());
};

#endif

#endif
