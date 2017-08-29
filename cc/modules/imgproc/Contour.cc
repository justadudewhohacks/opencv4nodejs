#include "Contour.h"
#include "Mat.h"
#include "Point.h"
#include "Vec.h"
#include "Rect.h"

Nan::Persistent<v8::FunctionTemplate> Contour::constructor;

void Contour::Init() {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Contour::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Contours").ToLocalChecked());

	Nan::SetPrototypeMethod(ctor, "approxPolyDP", ApproxPolyDP);
	Nan::SetPrototypeMethod(ctor, "arcLength", ArcLength);
	Nan::SetPrototypeMethod(ctor, "boundingRect", BoundingRect);
	Nan::SetPrototypeMethod(ctor, "contourArea", ContourArea);
	Nan::SetPrototypeMethod(ctor, "isContourConvex", IsContourConvex);
	Nan::SetPrototypeMethod(ctor, "convexHull", ConvexHull);
	Nan::SetPrototypeMethod(ctor, "convexityDefects", ConvexityDefects);
	Nan::SetPrototypeMethod(ctor, "minEnclosingCircle", MinEnclosingCircle);
	Nan::SetPrototypeMethod(ctor, "pointPolygonTest", PointPolygonTest);
	Nan::SetPrototypeMethod(ctor, "matchShapes", MatchShapes);
};

NAN_METHOD(Contour::ApproxPolyDP) {
	FF_REQUIRE_ARGS_OBJ("Contour::ApproxPolyDP");
	double epsilon;
	bool closed;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, epsilon, IsNumber, NumberValue);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, closed, IsBoolean, BooleanValue);

	std::vector<cv::Point2d> curve;
	cv::approxPolyDP(FF_UNWRAP(info.This(), Contour)->contour, curve, epsilon, closed);

	info.GetReturnValue().Set(Point::packJSPoint2Array(curve));
}

NAN_METHOD(Contour::ArcLength) {
	bool closed = false;
	if (info[0]->IsBoolean()) {
		closed = info[0]->BooleanValue();
	}
	
	double arcLength = cv::arcLength(FF_UNWRAP(info.This(), Contour)->contour, closed);
	info.GetReturnValue().Set(Nan::New(arcLength));
}

NAN_METHOD(Contour::BoundingRect) {
	v8::Local<v8::Object> jsRect = FF_NEW(Rect::constructor);
	FF_UNWRAP(jsRect, Rect)->rect = cv::boundingRect(FF_UNWRAP(info.This(), Contour)->contour);
	info.GetReturnValue().Set(jsRect);
}

NAN_METHOD(Contour::ContourArea) {
	bool oriented = false;
	if (info[0]->IsBoolean()) {
		oriented = info[0]->BooleanValue();
	}

	double contourArea = cv::contourArea(FF_UNWRAP(info.This(), Contour)->contour, oriented);
	info.GetReturnValue().Set(Nan::New(contourArea));
}

NAN_METHOD(Contour::ConvexHull) {
	bool clockwise = false;
	bool returnPoints = true;

	if (info.Length() > 0) {
		FF_REQUIRE_ARGS_OBJ("Contour::ConvexHull");
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, clockwise, IsBoolean, BooleanValue);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, returnPoints, IsBoolean, BooleanValue);
	}

	std::vector<cv::Point2d> hull;
	cv::convexHull(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		hull,
		clockwise,
		returnPoints
	);

	info.GetReturnValue().Set(Point::packJSPoint2Array(hull));
}

NAN_METHOD(Contour::ConvexityDefects) {
	if (!info[0]->IsArray()) {
		Nan::ThrowError("Contour::ConvexityDefects - expected arg0 to be an array of points");
	}
	std::vector<cv::Point2d> hull;
	std::vector<cv::Vec4d> defects;
	Point::unpackJSPoint2Array(hull, FF_CAST_ARRAY(info[0]));
	v8::Local<v8::Object> jsMat = FF_NEW(constructor);
	cv::convexityDefects(
		FF_UNWRAP(info.This(), Contour)->contour,
		hull,
		defects
	);

	info.GetReturnValue().Set(Vec::packJSVec4Array(defects));
}

NAN_METHOD(Contour::IsContourConvex) {
	bool isConvex = cv::isContourConvex(FF_UNWRAP(info.This(), Contour)->contour);
	info.GetReturnValue().Set(Nan::New(isConvex));
}

NAN_METHOD(Contour::MinEnclosingCircle) {
	cv::Point2f center;
	float radius;
	cv::minEnclosingCircle(FF_UNWRAP(info.This(), Contour)->contour, center, radius);

	v8::Local<v8::Object> jsCircle = Nan::New<v8::Object>();
	v8::Local<v8::Object> jsCenter = FF_NEW(Point2::constructor);
	FF_UNWRAP_PT2_AND_GET(jsCenter) = center;
	Nan::Set(jsCircle, FF_V8STRING("center"), jsCenter);
	Nan::Set(jsCircle, FF_V8STRING("radius"), Nan::New((double)radius));
	info.GetReturnValue().Set(jsCircle);
}

NAN_METHOD(Contour::PointPolygonTest) {
	if (!FF_IS_INSTANCE(Point2::constructor, info[0])) {
		Nan::ThrowError("Contour::PointPolygonTest - expected arg0 to be an isntance of Point2");
	}
	
	double dist = cv::pointPolygonTest(
		FF_UNWRAP(info.This(), Contour)->contour,
		FF_UNWRAP_PT2_AND_GET(info[0]->ToObject()),
		true
	);

	info.GetReturnValue().Set(Nan::New(dist));
}

NAN_METHOD(Contour::MatchShapes) {
	FF_REQUIRE_ARGS_OBJ("Contour::MatchShapes");

	int method;
	double parameter;
	std::vector<cv::Point2d> contour2;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, method, IsUint32, Uint32Value);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, parameter, IsNumber, NumberValue);
	FF_DESTRUCTURE_JSOBJ_REQUIRED(args, contour2, Contour::constructor, FF_UNWRAP_CONTOUR_AND_GET, Contour);

	double cmp = cv::matchShapes(
		FF_UNWRAP(info.This(), Contour)->contour,
		contour2,
		method,
		parameter
	);

	info.GetReturnValue().Set(Nan::New(cmp));
}


