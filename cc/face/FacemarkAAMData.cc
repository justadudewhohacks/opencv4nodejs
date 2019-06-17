#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "FacemarkAAMData.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

Nan::Persistent<v8::FunctionTemplate> FacemarkAAMData::constructor;

NAN_MODULE_INIT(FacemarkAAMData::Init) {
  v8::Local<v8::FunctionTemplate> ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkAAMData::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("FacemarkAAMData"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString("s0"), s0_getter, s0_setter);

  Nan::Set(target,FF::newString("FacemarkAAMData"), FF::getFunction(ctor));
};

NAN_METHOD(FacemarkAAMData::New) {
	FF::TryCatch tryCatch("FacemarkAAMData::New");
	FF_ASSERT_CONSTRUCT_CALL();
  FacemarkAAMData *self = new FacemarkAAMData();
  self->self = cv::face::FacemarkAAM::Data();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
