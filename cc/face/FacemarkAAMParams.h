#include "macros.h"
#include "NativeNodeUtils.h"
#include <opencv2/face.hpp>

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

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

  FF_ACCESSORS(m, FF::IntConverter);
  FF_ACCESSORS(max_m, FF::IntConverter);
  FF_ACCESSORS(max_n, FF::IntConverter);
  FF_ACCESSORS(model_filename, FF::StringConverter);
  FF_ACCESSORS(n, FF::IntConverter);
  FF_ACCESSORS(n_iter, FF::IntConverter);
  FF_ACCESSORS(save_model, FF::BoolConverter);
  FF_ACCESSORS(scales, FF::FloatArrayConverter);
  FF_ACCESSORS(texture_max_m, FF::IntConverter);
  FF_ACCESSORS(verbose, FF::BoolConverter);
};

#endif

#endif
