#include "macros.h"
#include "NativeNodeUtils.h"
#include <opencv2/face.hpp>

#if CV_VERSION_MINOR >= 4

#ifndef __FF_FACEMARKAAMPARAMS_H__
#define __FF_FACEMARKAAMPARAMS_H__

class FacemarkAAMParams : public FF::ObjectWrap<FacemarkAAMParams, cv::face::FacemarkAAM::Params> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "FacemarkAAMParams";
	}

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static FF_GETTER(FacemarkAAMParams, mGet, self.m);
  static FF_SETTER_INT(FacemarkAAMParams, m, self.m);
  static FF_GETTER(FacemarkAAMParams, maxMGet, self.max_m);
  static FF_SETTER_INT(FacemarkAAMParams, maxM, self.max_m);
  static FF_GETTER(FacemarkAAMParams, maxNGet, self.max_n);
  static FF_SETTER_INT(FacemarkAAMParams, maxN, self.max_n);
  static FF_GETTER_SIMPLE(FacemarkAAMParams, modelFilenameGet, self.model_filename, FF::StringConverter);
  static FF_SETTER_SIMPLE(FacemarkAAMParams, modelFilename, self.model_filename, FF::StringConverter);
  static FF_GETTER(FacemarkAAMParams, nGet, self.n);
  static FF_SETTER_INT(FacemarkAAMParams, n, self.n);
  static FF_GETTER(FacemarkAAMParams, nIterGet, self.n_iter);
  static FF_SETTER_INT(FacemarkAAMParams, nIter, self.n_iter);
  static FF_GETTER(FacemarkAAMParams, saveModelGet, self.save_model);
  static FF_SETTER_BOOL(FacemarkAAMParams, saveModel, self.save_model);
  static FF_GETTER_COMPLEX(FacemarkAAMParams, scalesGet, self.scales, FF::FloatArrayConverter);
  static FF_SETTER_COMPLEX(FacemarkAAMParams, scales, self.scales, std::vector<float>, FF::FloatArrayConverter);
  static FF_GETTER(FacemarkAAMParams, textureMaxMGet, self.texture_max_m);
  static FF_SETTER_INT(FacemarkAAMParams, textureMaxM, self.texture_max_m);
  static FF_GETTER(FacemarkAAMParams, verboseGet, self.verbose);
  static FF_SETTER_BOOL(FacemarkAAMParams, verbose, self.verbose);
};

#endif

#endif
