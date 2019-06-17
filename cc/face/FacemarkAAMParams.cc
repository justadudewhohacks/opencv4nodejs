#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "FacemarkAAMParams.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

Nan::Persistent<v8::FunctionTemplate> FacemarkAAMParams::constructor;

NAN_MODULE_INIT(FacemarkAAMParams::Init) {
  v8::Local<v8::FunctionTemplate> ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkAAMParams::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("FacemarkAAMParams"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString("m"), m_getter, m_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("max_m"), max_m_getter, max_m_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("max_n"), max_n_getter, max_n_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("model_filename"), model_filename_getter, model_filename_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("n"), n_getter, n_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("n_iter"), n_iter_getter, n_iter_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("save_model"), save_model_getter, save_model_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("scales"), scales_getter, scales_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("texture_max_m"), texture_max_m_getter, texture_max_m_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("verbose"), verbose_getter, verbose_setter);

  Nan::Set(target,FF::newString("FacemarkAAMParams"), FF::getFunction(ctor));
};

NAN_METHOD(FacemarkAAMParams::New) {
	FF::TryCatch tryCatch("FacemarkAAMParams::New");
	FF_ASSERT_CONSTRUCT_CALL();
  FacemarkAAMParams *self = new FacemarkAAMParams();
  self->self = cv::face::FacemarkAAM::Params();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
