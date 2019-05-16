#ifdef HAVE_FACE

#include "FacemarkAAM.h"
#include "FacemarkAAMParams.h"

#if CV_VERSION_MINOR >= 4

Nan::Persistent<v8::FunctionTemplate> FacemarkAAM::constructor;

NAN_MODULE_INIT(FacemarkAAM::Init) {
  v8::Local<v8::FunctionTemplate> ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkAAM::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Facemark::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("FacemarkAAM").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

  target->Set(Nan::New("FacemarkAAM").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(FacemarkAAM::New) {
  FF_ASSERT_CONSTRUCT_CALL(FacemarkAAM);
  FF::TryCatch tryCatch;

  cv::face::FacemarkAAM::Params params;
  if (FacemarkAAMParams::Converter::optArg(0, &params, info)) {
	  v8::Local<v8::Value> err = tryCatch.formatCatchedError("FacemarkAAM::New");
	  tryCatch.throwNew(err);
	  return;
  }

  FacemarkAAM *self = new FacemarkAAM();
  self->Wrap(info.Holder());
  self->facemark = cv::face::FacemarkAAM::create(params);

  FF_RETURN(info.Holder());
};

#endif

#endif
