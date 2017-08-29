#include "Contour.h"
#include "Mat.h"
#include "Point.h"
#include "Rect.h"

Nan::Persistent<v8::FunctionTemplate> Contour::constructor;

void Contour::Init() {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Contour::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Contour").ToLocalChecked());

	Nan::SetAccessor(ctor->InstanceTemplate(), FF_V8STRING("isConvex"), GetIsConvex);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_V8STRING("area"), GetArea);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_V8STRING("numPoints"), GetNumPoints);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_V8STRING("hierarchy"), GetHierarchy);

	Nan::SetPrototypeMethod(ctor, "getPoints", GetPoints);
	Nan::SetPrototypeMethod(ctor, "approxPolyDP", ApproxPolyDP);
	Nan::SetPrototypeMethod(ctor, "arcLength", ArcLength);
	Nan::SetPrototypeMethod(ctor, "boundingRect", BoundingRect);
	Nan::SetPrototypeMethod(ctor, "convexHull", ConvexHull);
	Nan::SetPrototypeMethod(ctor, "convexityDefects", ConvexityDefects);
	Nan::SetPrototypeMethod(ctor, "minEnclosingCircle", MinEnclosingCircle);
	Nan::SetPrototypeMethod(ctor, "pointPolygonTest", PointPolygonTest);
	Nan::SetPrototypeMethod(ctor, "matchShapes", MatchShapes);
};

NAN_METHOD(Contour::GetPoints) {
	info.GetReturnValue().Set(Point::packJSPoint2Array(FF_UNWRAP(info.This(), Contour)->contour));
}

NAN_METHOD(Contour::ApproxPolyDP) {
	FF_REQUIRE_ARGS_OBJ("Contour::ApproxPolyDP");
	double epsilon;
	bool closed;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, epsilon, IsNumber, NumberValue);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, closed, IsBoolean, BooleanValue);

	std::vector<cv::Point> curve;
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

NAN_METHOD(Contour::ConvexHull) {
	bool clockwise = false;
	bool returnPoints = true;

	if (info.Length() > 0) {
		FF_REQUIRE_ARGS_OBJ("Contour::ConvexHull");
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, clockwise, IsBoolean, BooleanValue);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, returnPoints, IsBoolean, BooleanValue);
	}

	v8::Local<v8::Array> jsHull;
	if (returnPoints) {
		std::vector<cv::Point> hullPoints;
		cv::convexHull(
			FF_UNWRAP_CONTOUR_AND_GET(info.This()),
			hullPoints,
			clockwise,
			returnPoints
		);
		jsHull = Point::packJSPoint2Array(hullPoints);
	}
	else {
		std::vector<int> hullIndices;
		cv::convexHull(
			FF_UNWRAP_CONTOUR_AND_GET(info.This()),
			hullIndices,
			clockwise,
			returnPoints
		);
		jsHull = Nan::New<v8::Array>(hullIndices.size());
		for (int i = 0; i < jsHull->Length(); i++) {
			jsHull->Set(i, Nan::New(hullIndices.at(i)));
		}
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
		FF_UNWRAP(info.This(), Contour)->contour,
		hull,
		defects
	);

	info.GetReturnValue().Set(Vec::packJSVec4Array(defects));
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
		return Nan::ThrowError("Contour::PointPolygonTest - expected arg0 to be an isntance of Point2");
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
	std::vector<cv::Point> contour2;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, method, IsUint32, Uint32Value);
	//FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, parameter, IsNumber, NumberValue);
	FF_DESTRUCTURE_JSOBJ_REQUIRED(args, contour2, Contour::constructor, FF_UNWRAP_CONTOUR_AND_GET, Contour);

	double cmp = cv::matchShapes(
		FF_UNWRAP(info.This(), Contour)->contour,
		contour2,
		method,
		parameter
	);

	info.GetReturnValue().Set(Nan::New(cmp));
}


