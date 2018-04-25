#ifdef HAVE_FACE

#include "FacemarkLBFParams.h"

#if CV_VERSION_MINOR >= 4

Nan::Persistent<v8::FunctionTemplate> FacemarkLBFParams::constructor;

NAN_MODULE_INIT(FacemarkLBFParams::Init) {
  v8::Local<v8::FunctionTemplate> ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkLBFParams::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF_NEW_STRING("FacemarkLBFParams"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("baggingOverlap"), baggingOverlapGet, baggingOverlapSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("cascadeFace"), cascadeFaceGet, cascadeFaceSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("detectROI"), detectROIGet, detectROISet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("featsM"), featsMGet, featsMSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("initShapeN"), initShapeNGet, initShapeNSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("modelFilename"), modelFilenameGet, modelFilenameSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("nLandmarks"), nLandmarksGet, nLandmarksSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("pupils"), pupilsGet, pupilsSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("radiusM"), radiusMGet, radiusMSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("saveModel"), saveModelGet, saveModelSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("seed"), seedGet, seedSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("shapeOffset"), shapeOffsetGet, shapeOffsetSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("stagesN"), stagesNGet, stagesNSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("treeDepth"), treeDepthGet, treeDepthSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("treeN"), treeNGet, treeNSet);
  Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("verbose"), verboseGet, verboseSet);

  target->Set(FF_NEW_STRING("FacemarkLBFParams"), ctor->GetFunction());
};

NAN_METHOD(FacemarkLBFParams::New) {
  FF_METHOD_CONTEXT("FacemarkLBFParams::New");
  FacemarkLBFParams *self = new FacemarkLBFParams();
  self->params = cv::face::FacemarkLBF::Params();
  self->Wrap(info.Holder());
  FF_RETURN(info.Holder());
};

#endif

#endif
