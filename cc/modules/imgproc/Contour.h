#include <nan.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "macros.h"
#include "Vec.h"

#ifndef __FF_CONTOUR_H__
#define __FF_CONTOUR_H__

class Contour: public Nan::ObjectWrap {
public:
  std::vector<cv::Point2i> contour;
  cv::Vec4i hierarchy;

	static void Init();

	static NAN_METHOD(New) {
		Contour* self = new Contour();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static NAN_GETTER(GetNumPoints) {
		info.GetReturnValue().Set(Nan::New((uint)FF_UNWRAP_CONTOUR_AND_GET(info.This()).size()));
	}

	static NAN_GETTER(GetHierarchy) {
		v8::Local<v8::Object> jsHierarchy = FF_NEW(Vec4::constructor);
		FF_UNWRAP_VEC4_AND_GET(jsHierarchy) = FF_UNWRAP(info.This(), Contour)->hierarchy;
		info.GetReturnValue().Set(jsHierarchy);
	}

	static NAN_GETTER(GetArea) {
		info.GetReturnValue().Set(Nan::New(cv::contourArea(FF_UNWRAP_CONTOUR_AND_GET(info.This()), false)));
	}

	static NAN_GETTER(GetIsConvex) {
		info.GetReturnValue().Set(Nan::New(cv::isContourConvex(FF_UNWRAP_CONTOUR_AND_GET(info.This()))));
	}

	static NAN_METHOD(GetPoints);
	static NAN_METHOD(ApproxPolyDP);
	static NAN_METHOD(ArcLength);
	static NAN_METHOD(BoundingRect);
	static NAN_METHOD(ConvexHull);
	static NAN_METHOD(ConvexityDefects);
	static NAN_METHOD(MinEnclosingCircle);
	static NAN_METHOD(PointPolygonTest);
	static NAN_METHOD(MatchShapes);
	static NAN_METHOD(FitEllipse);
	static NAN_METHOD(MinAreaRect);
	static NAN_METHOD(_Moments);

	// TODO FitLine, minEnclosingTriangle

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif