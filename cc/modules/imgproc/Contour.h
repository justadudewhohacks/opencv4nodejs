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
  cv::Vec4d hierarchy;

	static void Init();

	static NAN_METHOD(New) {
		Contour* self = new Contour();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static NAN_GETTER(GetNumPoints) {
		info.GetReturnValue().Set(Nan::New((uint)FF_UNWRAP(info.This(), Contour)->contour.size()));
	}

	static NAN_GETTER(GetHierarchy) {
		v8::Local<v8::Object> jsHierarchy = FF_NEW(Vec4::constructor);
		FF_UNWRAP_VEC4_AND_GET(jsHierarchy) = FF_UNWRAP(info.This(), Contour)->hierarchy;
		info.GetReturnValue().Set(jsHierarchy);
	}

	static NAN_GETTER(GetArea) {
		info.GetReturnValue().Set(Nan::New(cv::contourArea(FF_UNWRAP(info.This(), Contour)->contour, false)));
	}

	static NAN_GETTER(GetIsConvex) {
		info.GetReturnValue().Set(Nan::New(cv::isContourConvex(FF_UNWRAP(info.This(), Contour)->contour)));
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
	
	// TODO FitEllipse, FitLine, MinAreaRect, Moments, HuMoments

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif