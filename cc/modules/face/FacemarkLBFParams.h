#include "macros.h"
#include "TypeConverters.h"
#include "ArrayConverters.h"
#include "Rect.h"
#include <opencv2/face.hpp>

#if CV_VERSION_MINOR >= 4

#ifndef __FF_FACEMARKLBFPARAMS_H__
#define __FF_FACEMARKLBFPARAMS_H__

class FacemarkLBFParams : public Nan::ObjectWrap {
public:
  cv::face::FacemarkLBF::Params params;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static FF_GETTER(FacemarkLBFParams, baggingOverlapGet, params.bagging_overlap);
  static FF_SETTER_NUMBER(FacemarkLBFParams, baggingOverlap, params.bagging_overlap);
  static FF_GETTER_SIMPLE(FacemarkLBFParams, cascadeFaceGet, params.cascade_face, StringConverter);
  static FF_SETTER_SIMPLE(FacemarkLBFParams, cascadeFace, params.cascade_face, StringConverter);
  static FF_GETTER_SIMPLE(FacemarkLBFParams, detectROIGet, params.detectROI, Rect::Converter);
  static FF_SETTER_SIMPLE(FacemarkLBFParams, detectROI, params.detectROI, Rect::Converter);
  static FF_GETTER_COMPLEX(FacemarkLBFParams, featsMGet, params.feats_m, IntArrayConverter);
  static FF_SETTER_COMPLEX(FacemarkLBFParams, featsM, params.feats_m, std::vector<int>, IntArrayConverter);
  static FF_GETTER(FacemarkLBFParams, initShapeNGet, params.initShape_n);
  static FF_SETTER_INT(FacemarkLBFParams, initShapeN, params.initShape_n);
  static FF_GETTER_SIMPLE(FacemarkLBFParams, modelFilenameGet, params.model_filename, StringConverter);
  static FF_SETTER_SIMPLE(FacemarkLBFParams, modelFilename, params.model_filename, StringConverter);
  static FF_GETTER(FacemarkLBFParams, nLandmarksGet, params.n_landmarks);
  static FF_SETTER_INT(FacemarkLBFParams, nLandmarks, params.n_landmarks);

	static NAN_GETTER(pupilsGet) {
		v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(2);
		for (int i = 0; i < jsArr->Length(); i++) {
			jsArr->Set(i, ArrayConverterType<IntTypeConverter, int>::wrap(
				Nan::ObjectWrap::Unwrap<FacemarkLBFParams>(info.This())->params.pupils[i])
			);
		}
		info.GetReturnValue().Set(jsArr);
	}

	static NAN_SETTER(pupilsSet) {
		FF_METHOD_CONTEXT("pupils");
		v8::Local<v8::Array> jsArr = v8::Local<v8::Array>::Cast(value);
		for (int i = 0; i < jsArr->Length(); i++) {
			std::vector<int> vec;
			Nan::TryCatch tryCatch;
			if (ArrayConverterType<IntTypeConverter, int>::unwrap(&vec, jsArr->Get(i))) {
				tryCatch.ReThrow();
			}
			Nan::ObjectWrap::Unwrap<FacemarkLBFParams>(info.This())->params.pupils[i] = vec;
		}
	}

  static FF_GETTER_COMPLEX(FacemarkLBFParams, radiusMGet, params.radius_m, DoubleArrayConverter);
  static FF_SETTER_COMPLEX(FacemarkLBFParams, radiusM, params.radius_m, std::vector<double>, DoubleArrayConverter);
  static FF_GETTER(FacemarkLBFParams, saveModelGet, params.save_model);
  static FF_SETTER_BOOL(FacemarkLBFParams, saveModel, params.save_model);
  static FF_GETTER(FacemarkLBFParams, seedGet, params.seed);
  static FF_SETTER_UINT(FacemarkLBFParams, seed, params.seed);
  static FF_GETTER(FacemarkLBFParams, shapeOffsetGet, params.shape_offset);
  static FF_SETTER_NUMBER(FacemarkLBFParams, shapeOffset, params.shape_offset);
  static FF_GETTER(FacemarkLBFParams, stagesNGet, params.stages_n);
  static FF_SETTER_INT(FacemarkLBFParams, stagesN, params.stages_n);
  static FF_GETTER(FacemarkLBFParams, treeDepthGet, params.tree_depth);
  static FF_SETTER_INT(FacemarkLBFParams, treeDepth, params.tree_depth);
  static FF_GETTER(FacemarkLBFParams, treeNGet, params.tree_n);
  static FF_SETTER_INT(FacemarkLBFParams, treeN, params.tree_n);
  static FF_GETTER(FacemarkLBFParams, verboseGet, params.verbose);
  static FF_SETTER_BOOL(FacemarkLBFParams, verbose, params.verbose);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#define FF_UNWRAP_FACEMARKLBFPARAMS(obj) FF_UNWRAP(obj, FacemarkLBFParams)
#define FF_UNWRAP_FACEMARKLBFPARAMS_AND_GET(obj)                               \
  FF_UNWRAP_FACEMARKLBFPARAMS(obj)->params

#endif

#endif
