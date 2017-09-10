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
	Nan::SetPrototypeMethod(ctor, "convexityDefects", ConvexityDefects);
	Nan::SetPrototypeMethod(ctor, "minAreaRect", MinAreaRect);
	Nan::SetPrototypeMethod(ctor, "minEnclosingCircle", MinEnclosingCircle);
	Nan::SetPrototypeMethod(ctor, "pointPolygonTest", PointPolygonTest);
	Nan::SetPrototypeMethod(ctor, "matchShapes", MatchShapes);
	Nan::SetPrototypeMethod(ctor, "fitEllipse", FitEllipse);
	Nan::SetPrototypeMethod(ctor, "moments", _Moments);
};

NAN_METHOD(Contour::GetPoints) {
	info.GetReturnValue().Set(Point::packJSPoint2Array(FF_UNWRAP_CONTOUR_AND_GET(info.This())));
}

NAN_METHOD(Contour::ApproxPolyDP) {
	FF_REQUIRE_ARGS_OBJ("Contour::ApproxPolyDP");
	double epsilon;
	bool closed;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, epsilon, IsNumber, NumberValue);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, closed, IsBoolean, BooleanValue);

	std::vector<cv::Point> curve;
	cv::approxPolyDP(FF_UNWRAP_CONTOUR_AND_GET(info.This()), curve, epsilon, closed);

	info.GetReturnValue().Set(Point::packJSPoint2Array(curve));
}

NAN_METHOD(Contour::ArcLength) {
	bool closed = false;
	if (info[0]->IsBoolean()) {
		closed = info[0]->BooleanValue();
	}
	
	double arcLength = cv::arcLength(FF_UNWRAP_CONTOUR_AND_GET(info.This()), closed);
	info.GetReturnValue().Set(Nan::New(arcLength));
}

NAN_METHOD(Contour::BoundingRect) {
	v8::Local<v8::Object> jsRect = FF_NEW_INSTANCE(Rect::constructor);
	FF_UNWRAP(jsRect, Rect)->rect = cv::boundingRect(FF_UNWRAP_CONTOUR_AND_GET(info.This()));
	info.GetReturnValue().Set(jsRect);
}

NAN_METHOD(Contour::ConvexHull) {
	bool clockwise = false;
	bool returnPoints = true;

	if (info.Length() > 0) {
		FF_REQUIRE_ARGS_OBJ("Contour::ConvexHull");
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, clockwise, IsBoolean, BooleanValue);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, returnPoints, IsBoolean, BooleanValue);
	}

	v8::Local<v8::Object> jsHull;
	if (returnPoints) {
		std::vector<cv::Point> hullPoints;
		cv::convexHull(
			FF_UNWRAP_CONTOUR_AND_GET(info.This()),
			hullPoints,
			clockwise,
			returnPoints
		);
		jsHull = FF_NEW_INSTANCE(Contour::constructor);
		FF_UNWRAP_CONTOUR_AND_GET(jsHull) = hullPoints;
		FF_UNWRAP(jsHull, Contour)->hierarchy = cv::Vec4i(-1, -1, -1, -1);
	}
	else {
		std::vector<int> hullIndices;
		cv::convexHull(
			FF_UNWRAP_CONTOUR_AND_GET(info.This()),
			hullIndices,
			clockwise,
			returnPoints
		);
		jsHull = FF::stdVecToJSArray<int>(hullIndices);
	}

	info.GetReturnValue().Set(jsHull);
}

NAN_METHOD(Contour::ConvexityDefects) {
	if (!info[0]->IsArray()) {
		return Nan::ThrowError("Contour::ConvexityDefects - expected arg0 to be an array of points");
	}

	std::vector<int> hull;
	v8::Local<v8::Array> jsHull = FF_CAST_ARRAY(info[0]);
	for (int i = 0; i < jsHull->Length(); i++) {
		hull.push_back(jsHull->Get(i)->Uint32Value());
	}

	std::vector<cv::Vec4d> defects;
	cv::convexityDefects(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		hull,
		defects
	);

	info.GetReturnValue().Set(Vec::packJSVec4Array(defects));
}

NAN_METHOD(Contour::MinEnclosingCircle) {
	cv::Point2f center;
	float radius;
	cv::minEnclosingCircle(FF_UNWRAP_CONTOUR_AND_GET(info.This()), center, radius);

	v8::Local<v8::Object> jsCircle = Nan::New<v8::Object>();
	v8::Local<v8::Object> jsCenter = FF_NEW_INSTANCE(Point2::constructor);
	FF_UNWRAP_PT2_AND_GET(jsCenter) = center;
	Nan::Set(jsCircle, FF_NEW_STRING("center"), jsCenter);
	Nan::Set(jsCircle, FF_NEW_STRING("radius"), Nan::New((double)radius));
	info.GetReturnValue().Set(jsCircle);
}

NAN_METHOD(Contour::PointPolygonTest) {
	if (!FF_IS_INSTANCE(Point2::constructor, info[0])) {
		return Nan::ThrowError("Contour::PointPolygonTest - expected arg0 to be an isntance of Point2");
	}
	
	double dist = cv::pointPolygonTest(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		FF_UNWRAP_PT2_AND_GET(info[0]->ToObject()),
		true
	);

	info.GetReturnValue().Set(Nan::New(dist));
}

NAN_METHOD(Contour::MatchShapes) {
	FF_REQUIRE_ARGS_OBJ("Contour::MatchShapes");

	int method;
	double parameter;
	std::vector<cv::Point> contour2;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, method, IsUint32, Uint32Value);
	// not supported
	//FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, parameter, IsNumber, NumberValue);
	FF_DESTRUCTURE_JSOBJ_REQUIRED(args, contour2, Contour::constructor, FF_UNWRAP_CONTOUR_AND_GET, Contour);

	double cmp = cv::matchShapes(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		contour2,
		method,
		parameter
	);

	info.GetReturnValue().Set(Nan::New(cmp));
}

NAN_METHOD(Contour::MinAreaRect) {
	v8::Local<v8::Object> jsRotatedRect = FF_NEW_INSTANCE(RotatedRect::constructor);
	FF_UNWRAP_ROTATEDRECT_AND_GET(jsRotatedRect) = cv::minAreaRect(FF_UNWRAP_CONTOUR_AND_GET(info.This()));
	info.GetReturnValue().Set(jsRotatedRect);
}

NAN_METHOD(Contour::FitEllipse) {
	v8::Local<v8::Object> jsRotatedRect = FF_NEW_INSTANCE(RotatedRect::constructor);
	FF_UNWRAP_ROTATEDRECT_AND_GET(jsRotatedRect) = cv::fitEllipse(FF_UNWRAP_CONTOUR_AND_GET(info.This()));
	info.GetReturnValue().Set(jsRotatedRect);
}

NAN_METHOD(Contour::_Moments) {
	v8::Local<v8::Object> jsMoments = FF_NEW_INSTANCE(Moments::constructor);
	FF_UNWRAP(jsMoments, Moments)->moments = cv::moments(FF_UNWRAP_CONTOUR_AND_GET(info.This()));
	info.GetReturnValue().Set(jsMoments);
}