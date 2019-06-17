#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "FacemarkLBF.h"
#include "FacemarkLBFParams.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

Nan::Persistent<v8::FunctionTemplate> FacemarkLBF::constructor;

NAN_MODULE_INIT(FacemarkLBF::Init) {
  v8::Local<v8::FunctionTemplate> ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkLBF::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Facemark::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("FacemarkLBF").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

  Nan::Set(target,Nan::New("FacemarkLBF").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(FacemarkLBF::New) {
	FF::TryCatch tryCatch("FacemarkLBF::New");
	FF_ASSERT_CONSTRUCT_CALL();

  cv::face::FacemarkLBF::Params params;
  if (FacemarkLBFParams::Converter::optArg(0, &params, info)) {
	  return tryCatch.reThrow();
  }

  FacemarkLBF *self = new FacemarkLBF();
  self->Wrap(info.Holder());
  self->facemark = cv::face::FacemarkLBF::create(params);


  info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
