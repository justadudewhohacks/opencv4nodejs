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

  target->Set(Nan::New("FacemarkLBF").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(FacemarkLBF::New) {
  FF_ASSERT_CONSTRUCT_CALL(FacemarkLBF);
  FF::TryCatch tryCatch;

  cv::face::FacemarkLBF::Params params;
  if (FacemarkLBFParams::Converter::optArg(0, &params, info)) {
	  v8::Local<v8::Value> err = tryCatch.formatCatchedError("FacemarkLBF::New");
	  tryCatch.throwNew(err);
	  return;
  }

  FacemarkLBF *self = new FacemarkLBF();
  self->Wrap(info.Holder());
  self->facemark = cv::face::FacemarkLBF::create(params);


  FF_RETURN(info.Holder());
};

#endif

#endif
