#ifdef HAVE_FACE

#include "FacemarkLBF.h"
#include "FacemarkLBFParams.h"

#if CV_VERSION_MINOR >= 4

Nan::Persistent<v8::FunctionTemplate> FacemarkLBF::constructor;

NAN_MODULE_INIT(FacemarkLBF::Init) {
  v8::Local<v8::FunctionTemplate> ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkLBF::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Facemark::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("FacemarkLBF").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

  target->Set(Nan::New("FacemarkLBF").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(FacemarkLBF::New) {
	FF_METHOD_CONTEXT("FacemarkLBF::New");

  FF_ARG_INSTANCE_IFDEF(
    0,
    cv::face::FacemarkLBF::Params params,
    FacemarkLBFParams::constructor,
    FF_UNWRAP_FACEMARKLBFPARAMS_AND_GET,
    cv::face::FacemarkLBF::Params()
  );

  FacemarkLBF *self = new FacemarkLBF();
  self->Wrap(info.Holder());
  self->facemark = cv::face::FacemarkLBF::create(params);

  FF_RETURN(info.Holder());
};

#endif

#endif
