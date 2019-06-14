#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "FacemarkAAM.h"
#include "FacemarkAAMParams.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

Nan::Persistent<v8::FunctionTemplate> FacemarkAAM::constructor;

NAN_MODULE_INIT(FacemarkAAM::Init) {
  v8::Local<v8::FunctionTemplate> ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkAAM::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Facemark::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("FacemarkAAM").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

  Nan::Set(target,Nan::New("FacemarkAAM").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(FacemarkAAM::New) {
	FF::TryCatch tryCatch("FacemarkAAM::New");
	FF_ASSERT_CONSTRUCT_CALL();

  cv::face::FacemarkAAM::Params params;
  if (FacemarkAAMParams::Converter::optArg(0, &params, info)) {
	  return tryCatch.reThrow();
  }

  FacemarkAAM *self = new FacemarkAAM();
  self->Wrap(info.Holder());
  self->facemark = cv::face::FacemarkAAM::create(params);

  info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
