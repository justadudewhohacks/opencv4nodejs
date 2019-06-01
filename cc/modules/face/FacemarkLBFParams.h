#include "macros.h"
#include "NativeNodeUtils.h"
#include "Rect.h"
#include <opencv2/face.hpp>

#if CV_VERSION_MINOR >= 4

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

  static FF_GETTER(FacemarkLBFParams, baggingOverlapGet, self.bagging_overlap);
  static FF_SETTER_NUMBER(FacemarkLBFParams, baggingOverlap, self.bagging_overlap);
  static FF_GETTER_SIMPLE(FacemarkLBFParams, cascadeFaceGet, self.cascade_face, FF::StringConverter);
  static FF_SETTER_SIMPLE(FacemarkLBFParams, cascadeFace, self.cascade_face, FF::StringConverter);
  static FF_GETTER_SIMPLE(FacemarkLBFParams, detectROIGet, self.detectROI, Rect::Converter);
  static FF_SETTER_SIMPLE(FacemarkLBFParams, detectROI, self.detectROI, Rect::Converter);
  static FF_GETTER_COMPLEX(FacemarkLBFParams, featsMGet, self.feats_m, FF::IntArrayConverter);
  static FF_SETTER_COMPLEX(FacemarkLBFParams, featsM, self.feats_m, std::vector<int>, FF::IntArrayConverter);
  static FF_GETTER(FacemarkLBFParams, initShapeNGet, self.initShape_n);
  static FF_SETTER_INT(FacemarkLBFParams, initShapeN, self.initShape_n);
  static FF_GETTER_SIMPLE(FacemarkLBFParams, modelFilenameGet, self.model_filename, FF::StringConverter);
  static FF_SETTER_SIMPLE(FacemarkLBFParams, modelFilename, self.model_filename, FF::StringConverter);
  static FF_GETTER(FacemarkLBFParams, nLandmarksGet, self.n_landmarks);
  static FF_SETTER_INT(FacemarkLBFParams, nLandmarks, self.n_landmarks);

	static NAN_GETTER(pupilsGet) {
		v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(2);
		for (uint i = 0; i < jsArr->Length(); i++) {
			Nan::Set(jsArr, i, FF::IntArrayConverter::wrap(
				Nan::ObjectWrap::Unwrap<FacemarkLBFParams>(info.This())->self.pupils[i])
			);
		}
		info.GetReturnValue().Set(jsArr);
	}

	static NAN_SETTER(pupilsSet) {
		FF::TryCatch tryCatch("FacemarkLBFParams::pupilsSet");
		v8::Local<v8::Array> jsArr = v8::Local<v8::Array>::Cast(value);
		for (uint i = 0; i < jsArr->Length(); i++) {
			std::vector<int> vec;
			if (FF::IntArrayConverter::unwrapTo(&vec, Nan::Get(jsArr, i).ToLocalChecked())) {
				tryCatch.ReThrow();
			}
			Nan::ObjectWrap::Unwrap<FacemarkLBFParams>(info.This())->self.pupils[i] = vec;
		}
	}

  static FF_GETTER_COMPLEX(FacemarkLBFParams, radiusMGet, self.radius_m, FF::DoubleArrayConverter);
  static FF_SETTER_COMPLEX(FacemarkLBFParams, radiusM, self.radius_m, std::vector<double>, FF::DoubleArrayConverter);
  static FF_GETTER(FacemarkLBFParams, saveModelGet, self.save_model);
  static FF_SETTER_BOOL(FacemarkLBFParams, saveModel, self.save_model);
  static FF_GETTER(FacemarkLBFParams, seedGet, self.seed);
  static FF_SETTER_UINT(FacemarkLBFParams, seed, self.seed);
  static FF_GETTER(FacemarkLBFParams, shapeOffsetGet, self.shape_offset);
  static FF_SETTER_NUMBER(FacemarkLBFParams, shapeOffset, self.shape_offset);
  static FF_GETTER(FacemarkLBFParams, stagesNGet, self.stages_n);
  static FF_SETTER_INT(FacemarkLBFParams, stagesN, self.stages_n);
  static FF_GETTER(FacemarkLBFParams, treeDepthGet, self.tree_depth);
  static FF_SETTER_INT(FacemarkLBFParams, treeDepth, self.tree_depth);
  static FF_GETTER(FacemarkLBFParams, treeNGet, self.tree_n);
  static FF_SETTER_INT(FacemarkLBFParams, treeN, self.tree_n);
  static FF_GETTER(FacemarkLBFParams, verboseGet, self.verbose);
  static FF_SETTER_BOOL(FacemarkLBFParams, verbose, self.verbose);
};

#endif

#endif
