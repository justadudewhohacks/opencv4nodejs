#include "macros.h"
#include "TypeConverters.h"
#include <opencv2/face.hpp>

#if CV_VERSION_MINOR >= 4

#ifndef __FF_FACEMARKAAMPARAMS_H__
#define __FF_FACEMARKAAMPARAMS_H__

class FacemarkAAMParams : public Nan::ObjectWrap {
public:
  cv::face::FacemarkAAM::Params params;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static FF_GETTER(FacemarkAAMParams, mGet, params.m);
  static FF_SETTER_INT(FacemarkAAMParams, m, params.m);
  static FF_GETTER(FacemarkAAMParams, maxMGet, params.max_m);
  static FF_SETTER_INT(FacemarkAAMParams, maxM, params.max_m);
  static FF_GETTER(FacemarkAAMParams, maxNGet, params.max_n);
  static FF_SETTER_INT(FacemarkAAMParams, maxN, params.max_n);
  static FF_GETTER_SIMPLE(FacemarkAAMParams, modelFilenameGet, params.model_filename, StringConverter);
  static FF_SETTER_SIMPLE(FacemarkAAMParams, modelFilename, params.model_filename, StringConverter);
  static FF_GETTER(FacemarkAAMParams, nGet, params.n);
  static FF_SETTER_INT(FacemarkAAMParams, n, params.n);
  static FF_GETTER(FacemarkAAMParams, nIterGet, params.n_iter);
  static FF_SETTER_INT(FacemarkAAMParams, nIter, params.n_iter);
  static FF_GETTER(FacemarkAAMParams, saveModelGet, params.save_model);
  static FF_SETTER_BOOL(FacemarkAAMParams, saveModel, params.save_model);
  static FF_GETTER_COMPLEX(FacemarkAAMParams, scalesGet, params.scales, FloatArrayConverter);
  static FF_SETTER_COMPLEX(FacemarkAAMParams, scales, params.scales, std::vector<float>, FloatArrayConverter);
  static FF_GETTER(FacemarkAAMParams, textureMaxMGet, params.texture_max_m);
  static FF_SETTER_INT(FacemarkAAMParams, textureMaxM, params.texture_max_m);
  static FF_GETTER(FacemarkAAMParams, verboseGet, params.verbose);
  static FF_SETTER_BOOL(FacemarkAAMParams, verbose, params.verbose);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#define FF_UNWRAP_FACEMARKAAMPARAMS(obj) FF_UNWRAP(obj, FacemarkAAMParams)
#define FF_UNWRAP_FACEMARKAAMPARAMS_AND_GET(obj)                               \
  FF_UNWRAP_FACEMARKAAMPARAMS(obj)->params

#endif

#endif
