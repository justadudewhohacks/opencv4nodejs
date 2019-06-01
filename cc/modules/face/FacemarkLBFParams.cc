#ifdef HAVE_FACE

#include "FacemarkLBFParams.h"

#if CV_VERSION_MINOR >= 4

Nan::Persistent<v8::FunctionTemplate> FacemarkLBFParams::constructor;

NAN_MODULE_INIT(FacemarkLBFParams::Init) {
  v8::Local<v8::FunctionTemplate> ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkLBFParams::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("FacemarkLBFParams"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString("baggingOverlap"), baggingOverlapGet, baggingOverlapSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("cascadeFace"), cascadeFaceGet, cascadeFaceSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("detectROI"), detectROIGet, detectROISet);
  Nan::SetAccessor(instanceTemplate, FF::newString("featsM"), featsMGet, featsMSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("initShapeN"), initShapeNGet, initShapeNSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("modelFilename"), modelFilenameGet, modelFilenameSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("nLandmarks"), nLandmarksGet, nLandmarksSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("pupils"), pupilsGet, pupilsSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("radiusM"), radiusMGet, radiusMSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("saveModel"), saveModelGet, saveModelSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("seed"), seedGet, seedSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("shapeOffset"), shapeOffsetGet, shapeOffsetSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("stagesN"), stagesNGet, stagesNSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("treeDepth"), treeDepthGet, treeDepthSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("treeN"), treeNGet, treeNSet);
  Nan::SetAccessor(instanceTemplate, FF::newString("verbose"), verboseGet, verboseSet);

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
