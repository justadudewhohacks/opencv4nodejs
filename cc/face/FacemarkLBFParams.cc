#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "FacemarkLBFParams.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

Nan::Persistent<v8::FunctionTemplate> FacemarkLBFParams::constructor;

NAN_MODULE_INIT(FacemarkLBFParams::Init) {
  v8::Local<v8::FunctionTemplate> ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkLBFParams::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("FacemarkLBFParams"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString("bagging_overlap"), bagging_overlap_getter, bagging_overlap_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("cascade_face"), cascade_face_getter, cascade_face_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("detectROI"), detectROI_getter, detectROI_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("feats_m"), feats_m_getter, feats_m_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("initShape_n"), initShape_n_getter, initShape_n_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("model_filename"), model_filename_getter, model_filename_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("n_landmarks"), n_landmarks_getter, n_landmarks_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("pupils"), pupils_getter, pupils_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("radius_m"), radius_m_getter, radius_m_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("save_model"), save_model_getter, save_model_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("seed"), seed_getter, seed_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("shape_offset"), shape_offset_getter, shape_offset_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("stages_n"), stages_n_getter, stages_n_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("tree_depth"), tree_depth_getter, tree_depth_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("tree_n"), tree_n_getter, tree_n_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("verbose"), verbose_getter, verbose_setter);

  Nan::Set(target,FF::newString("FacemarkLBFParams"), FF::getFunction(ctor));
};

NAN_METHOD(FacemarkLBFParams::New) {
	FF::TryCatch tryCatch("FacemarkLBFParams::New");
	FF_ASSERT_CONSTRUCT_CALL();
  FacemarkLBFParams *self = new FacemarkLBFParams();
  self->self = cv::face::FacemarkLBF::Params();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
