#include <nan.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "macros.h"

#ifndef __FF_CONTOUR_H__
#define __FF_CONTOUR_H__

class Contour: public Nan::ObjectWrap {
public:
  std::vector<cv::Point2d> contour;
  cv::Vec4d hierarchy;

	static void Init();

	static NAN_METHOD(New) {
		Contour* self = new Contour();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static NAN_METHOD(ApproxPolyDP);
	static NAN_METHOD(ArcLength);
	static NAN_METHOD(BoundingRect);
	static NAN_METHOD(ContourArea);
	static NAN_METHOD(ConvexHull);
	static NAN_METHOD(ConvexityDefects);
	static NAN_METHOD(IsContourConvex);
	static NAN_METHOD(MinEnclosingCircle);
	static NAN_METHOD(PointPolygonTest);
	static NAN_METHOD(MatchShapes);
	
	// TODO FitEllipse, FitLine, MinAreaRect, Moments, HuMoments

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif