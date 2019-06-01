#ifdef HAVE_FACE

#include "FacemarkAAMData.h"

#if CV_VERSION_MINOR >= 4

Nan::Persistent<v8::FunctionTemplate> FacemarkAAMData::constructor;

NAN_MODULE_INIT(FacemarkAAMData::Init) {
  v8::Local<v8::FunctionTemplate> ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkAAMData::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("FacemarkAAMData"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString("s0"), s0Get, s0Set);

  Nan::Set(target,FF::newString("FacemarkAAMData"), FF::getFunction(ctor));
};

NAN_METHOD(FacemarkAAMData::New) {
	FF::TryCatch tryCatch("FacemarkAAMData::New");
	FF_ASSERT_CONSTRUCT_CALL();
  FacemarkAAMData *self = new FacemarkAAMData();
  self->data = cv::face::FacemarkAAM::Data();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
