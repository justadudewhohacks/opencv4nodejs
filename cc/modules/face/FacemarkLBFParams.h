#include "macros.h"
#include "NativeNodeUtils.h"
#include "Rect.h"
#include <opencv2/face.hpp>

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

#ifndef __FF_FACEMARKLBFPARAMS_H__
#define __FF_FACEMARKLBFPARAMS_H__

class FacemarkLBFParams : public FF::ObjectWrap<FacemarkLBFParams, cv::face::FacemarkLBF::Params> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "FacemarkLBFParams";
	}

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  FF_ACCESSORS(bagging_overlap, FF::DoubleConverter);
  FF_ACCESSORS(cascade_face, FF::StringConverter);
  FF_ACCESSORS(detectROI, Rect::Converter);
  FF_ACCESSORS(feats_m, FF::IntArrayConverter);
  FF_ACCESSORS(initShape_n, FF::IntConverter);
  FF_ACCESSORS(model_filename, FF::StringConverter);
  FF_ACCESSORS(n_landmarks, FF::IntConverter);
  FF_ACCESSORS(radius_m, FF::DoubleArrayConverter);
  FF_ACCESSORS(save_model, FF::BoolConverter);
  FF_ACCESSORS(seed, FF::UintConverter);
  FF_ACCESSORS(shape_offset, FF::DoubleConverter);
  FF_ACCESSORS(stages_n, FF::IntConverter);
  FF_ACCESSORS(tree_depth, FF::IntConverter);
  FF_ACCESSORS(tree_n, FF::IntConverter);
  FF_ACCESSORS(verbose, FF::BoolConverter);

  static NAN_GETTER(pupils_getter) {
	  Nan::ObjectWrap::Unwrap<FacemarkLBFParams>(info.This())->self.pupils;
	  v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(2);
	  for (uint i = 0; i < jsArr->Length(); i++) {
		  Nan::Set(jsArr, i, FF::IntArrayConverter::wrap(
			  Nan::ObjectWrap::Unwrap<FacemarkLBFParams>(info.This())->self.pupils[i])
		  );
	  }
	  info.GetReturnValue().Set(jsArr);
  }

  static NAN_SETTER(pupils_setter) {
	  FF::TryCatch tryCatch("FacemarkLBFParams::pupils_setter");
	  v8::Local<v8::Array> jsArr = v8::Local<v8::Array>::Cast(value);
	  for (uint i = 0; i < jsArr->Length(); i++) {
		  std::vector<int> vec;
		  if (FF::IntArrayConverter::unwrapTo(&vec, Nan::Get(jsArr, i).ToLocalChecked())) {
			  tryCatch.ReThrow();
		  }
		  Nan::ObjectWrap::Unwrap<FacemarkLBFParams>(info.This())->self.pupils[i] = vec;
	  }
  }
};

#endif

#endif
