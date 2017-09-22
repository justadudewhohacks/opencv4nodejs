#include "Contour.h"
#include "Mat.h"
#include "Point.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "Moments.h"

Nan::Persistent<v8::FunctionTemplate> Contour::constructor;

void Contour::Init() {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Contour::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Contour").ToLocalChecked());

	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("isConvex"), GetIsConvex);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("area"), GetArea);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("numPoints"), GetNumPoints);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("hierarchy"), GetHierarchy);

	Nan::SetPrototypeMethod(ctor, "getPoints", GetPoints);
	Nan::SetPrototypeMethod(ctor, "approxPolyDP", ApproxPolyDP);
	Nan::SetPrototypeMethod(ctor, "arcLength", ArcLength);
	Nan::SetPrototypeMethod(ctor, "boundingRect", BoundingRect); 
	Nan::SetPrototypeMethod(ctor, "convexHull", ConvexHull);
	Nan::SetPrototypeMethod(ctor, "convexHullIndices", ConvexHullIndices);
	Nan::SetPrototypeMethod(ctor, "convexityDefects", ConvexityDefects);
	Nan::SetPrototypeMethod(ctor, "minAreaRect", MinAreaRect);
	Nan::SetPrototypeMethod(ctor, "minEnclosingCircle", MinEnclosingCircle);
	Nan::SetPrototypeMethod(ctor, "minEnclosingTriangle", MinEnclosingTriangle);
	Nan::SetPrototypeMethod(ctor, "pointPolygonTest", PointPolygonTest);
	Nan::SetPrototypeMethod(ctor, "matchShapes", MatchShapes);
	Nan::SetPrototypeMethod(ctor, "fitEllipse", FitEllipse);
	Nan::SetPrototypeMethod(ctor, "moments", _Moments);
};

NAN_METHOD(Contour::GetPoints) {
	info.GetReturnValue().Set(Point::packJSPoint2Array(FF_UNWRAP_CONTOUR_AND_GET(info.This())));
}

NAN_METHOD(Contour::ApproxPolyDP) {
	FF_METHOD_CONTEXT("Contour::ApproxPolyDP");
	
	FF_ARG_NUMBER(0, double epsilon);
	FF_ARG_BOOL(1, bool closed);

	std::vector<cv::Point> curve;
	cv::approxPolyDP(FF_UNWRAP_CONTOUR_AND_GET(info.This()), curve, epsilon, closed);
	FF_RETURN(Point::packJSPoint2Array(curve));
}

NAN_METHOD(Contour::ArcLength) {
	FF_METHOD_CONTEXT("Contour::ArcLength");

	FF_ARG_BOOL_IFDEF(0, bool closed, false);
	
	double arcLength = cv::arcLength(FF_UNWRAP_CONTOUR_AND_GET(info.This()), closed);
	FF_RETURN(Nan::New(arcLength));
}

NAN_METHOD(Contour::BoundingRect) {
	FF_OBJ jsRect = FF_NEW_INSTANCE(Rect::constructor);
	FF_UNWRAP(jsRect, Rect)->rect = cv::boundingRect(FF_UNWRAP_CONTOUR_AND_GET(info.This()));
	FF_RETURN(jsRect);
}

NAN_METHOD(Contour::ConvexHull) {
	FF_METHOD_CONTEXT("Contour::ConvexHull");

	FF_ARG_BOOL_IFDEF(0, bool clockwise, false);

	std::vector<cv::Point> hullPoints;
	cv::convexHull(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		hullPoints,
		clockwise,
		true
	);
	FF_OBJ jsHull = FF_NEW_INSTANCE(Contour::constructor);
	FF_UNWRAP_CONTOUR_AND_GET(jsHull) = hullPoints;
	FF_UNWRAP(jsHull, Contour)->hierarchy = cv::Vec4i(-1, -1, -1, -1);
	FF_RETURN(jsHull);
}

NAN_METHOD(Contour::ConvexHullIndices) {
	FF_METHOD_CONTEXT("Contour::ConvexHullIndices");

	FF_ARG_BOOL_IFDEF(0, bool clockwise, false);

	std::vector<int> hullIndices;
	cv::convexHull(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		hullIndices,
		clockwise,
		false
	);
	FF_PACK_ARRAY(jsHullIndices, hullIndices);
	FF_RETURN(jsHullIndices);
}
NAN_METHOD(Contour::ConvexityDefects) {
	FF_METHOD_CONTEXT("Contour::ConvexityDefects");

	FF_ARG_ARRAY(0, FF_ARR jsHull);
	FF_UNPACK_INT_ARRAY(hull, jsHull);

	std::vector<cv::Vec4d> defects;
	cv::convexityDefects(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		hull,
		defects
	);

	FF_RETURN(Vec::packJSVec4Array(defects));
}

NAN_METHOD(Contour::MinEnclosingCircle) {
	cv::Point2f center;
	float radius;
	cv::minEnclosingCircle(FF_UNWRAP_CONTOUR_AND_GET(info.This()), center, radius);

	FF_OBJ jsCircle = FF_NEW_OBJ();
	FF_OBJ jsCenter = FF_NEW_INSTANCE(Point2::constructor);
	FF_UNWRAP_PT2_AND_GET(jsCenter) = center;
	Nan::Set(jsCircle, FF_NEW_STRING("center"), jsCenter);
	Nan::Set(jsCircle, FF_NEW_STRING("radius"), Nan::New((double)radius));
	FF_RETURN(jsCircle);
}

NAN_METHOD(Contour::MinEnclosingTriangle) {
	std::vector<cv::Point2f> triangle;
	cv::minEnclosingTriangle(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()), 
		triangle
	);
	FF_RETURN(Point::packJSPoint2Array(triangle));
}

NAN_METHOD(Contour::PointPolygonTest) {
	FF_METHOD_CONTEXT("Contour::PointPolygonTest");

	FF_ARG_INSTANCE(0, cv::Point2d point, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	
	double dist = cv::pointPolygonTest(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		point,
		true
	);
	FF_RETURN(Nan::New(dist));
}

NAN_METHOD(Contour::MatchShapes) {
	FF_METHOD_CONTEXT("Contour::MatchShapes");

	FF_ARG_INSTANCE(0, std::vector<cv::Point> contour2, Contour::constructor, FF_UNWRAP_CONTOUR_AND_GET);
	FF_ARG_UINT(1, uint method);

	// parameter not supported
	double parameter;
	double cmp = cv::matchShapes(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		contour2,
		(int)method,
		parameter
	);
	FF_RETURN(Nan::New(cmp));
}

NAN_METHOD(Contour::MinAreaRect) {
	FF_OBJ jsRotatedRect = FF_NEW_INSTANCE(RotatedRect::constructor);
	FF_UNWRAP_ROTATEDRECT_AND_GET(jsRotatedRect) = cv::minAreaRect(FF_UNWRAP_CONTOUR_AND_GET(info.This()));
	FF_RETURN(jsRotatedRect);
}

NAN_METHOD(Contour::FitEllipse) {
	FF_OBJ jsRotatedRect = FF_NEW_INSTANCE(RotatedRect::constructor);
	FF_UNWRAP_ROTATEDRECT_AND_GET(jsRotatedRect) = cv::fitEllipse(FF_UNWRAP_CONTOUR_AND_GET(info.This()));
	FF_RETURN(jsRotatedRect);
}

NAN_METHOD(Contour::_Moments) {
	FF_OBJ jsMoments = FF_NEW_INSTANCE(Moments::constructor);
	FF_UNWRAP(jsMoments, Moments)->moments = cv::moments(FF_UNWRAP_CONTOUR_AND_GET(info.This()));
	FF_RETURN(jsMoments);
}