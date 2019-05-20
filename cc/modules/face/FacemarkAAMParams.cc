#ifdef HAVE_FACE

#include "FacemarkAAMParams.h"

#if CV_VERSION_MINOR >= 4

Nan::Persistent<v8::FunctionTemplate> FacemarkAAMParams::constructor;

NAN_MODULE_INIT(FacemarkAAMParams::Init) {
  v8::Local<v8::FunctionTemplate> ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkAAMParams::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF_NEW_STRING("FacemarkAAMParams"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("m"), mGet, mSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("maxM"), maxMGet, maxMSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("maxN"), maxNGet, maxNSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("modelFilename"), modelFilenameGet, modelFilenameSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("n"), nGet, nSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("nIter"), nIterGet, nIterSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("saveModel"), saveModelGet, saveModelSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("scales"), scalesGet, scalesSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("textureMaxM"), textureMaxMGet, textureMaxMSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("verbose"), verboseGet, verboseSet);

  target->Set(FF_NEW_STRING("FacemarkAAMParams"), FF::getFunction(ctor));
};

NAN_METHOD(FacemarkAAMParams::New) {
  FF_ASSERT_CONSTRUCT_CALL(FacemarkAAMParams);
  FF_METHOD_CONTEXT("FacemarkAAMParams::New");
  FacemarkAAMParams *self = new FacemarkAAMParams();
  self->params = cv::face::FacemarkAAM::Params();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
