#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "face.h"
#include "EigenFaceRecognizer.h"
#include "FisherFaceRecognizer.h"
#include "LBPHFaceRecognizer.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
#include "FacemarkAAM.h"
#include "FacemarkAAMData.h"
#include "FacemarkAAMParams.h"
#include "FacemarkLBF.h"
#include "FacemarkLBFParams.h"
#endif

NAN_MODULE_INIT(Face::Init) {
  EigenFaceRecognizer::Init(target);
  FisherFaceRecognizer::Init(target);
  LBPHFaceRecognizer::Init(target);
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
  FacemarkAAM::Init(target);
  FacemarkAAMData::Init(target);
  FacemarkAAMParams::Init(target);
  FacemarkLBF::Init(target);
  FacemarkLBFParams::Init(target);
#endif
};

#endif
