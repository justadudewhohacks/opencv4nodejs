#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMGPROC

#include "Contour.h"
#include "ContourBindings.h"
#include "Mat.h"
#include "Point.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "Moments.h"

Nan::Persistent<v8::FunctionTemplate> Contour::constructor;

NAN_MODULE_INIT(Contour::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Contour::New);
	constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("Contour").ToLocalChecked());

	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("isConvex"), GetIsConvex);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("area"), GetArea);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("numPoints"), GetNumPoints);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("hierarchy"), GetHierarchy);

	Nan::SetPrototypeMethod(ctor, "getPoints", GetPoints);
	Nan::SetPrototypeMethod(ctor, "approxPolyDP", ApproxPolyDP);
	Nan::SetPrototypeMethod(ctor, "approxPolyDPAsync", ApproxPolyDPAsync);
	Nan::SetPrototypeMethod(ctor, "approxPolyDPContour", ApproxPolyDPContour);
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

	Nan::Set(target,Nan::New("Contour").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(Contour::New) {
	FF::TryCatch tryCatch("Contour::New");
	FF_ASSERT_CONSTRUCT_CALL();
	if (info.Length() > 1) {
		return tryCatch.throwError("expected one or zero argument");
	}
	if (info.Length() == 1 && !info[0]->IsArray()) {
		return tryCatch.throwError("expected arg0 to be an array");
	}

	Contour* self = new Contour();
	if (info.Length() == 1) {
		v8::Local<v8::Array> jsPts = v8::Local<v8::Array>::Cast(info[0]);
		self->self.reserve(jsPts->Length());
		for (uint i = 0; i < jsPts->Length(); i++) {
			cv::Point2d cv_pt;
			auto jsPt = Nan::Get(jsPts, i).ToLocalChecked();
			if (jsPt->IsArray()) {
				v8::Local<v8::Array> jsObj = v8::Local<v8::Array>::Cast(jsPt);
				if (jsObj->Length() != 2)
					return tryCatch.throwError("expected arg0 to consist of only Point2 or array of length 2");
				double x = FF::DoubleConverter::unwrapUnchecked(Nan::Get(jsObj, 0).ToLocalChecked());
				double y = FF::DoubleConverter::unwrapUnchecked(Nan::Get(jsObj, 1).ToLocalChecked());
				cv_pt = cv::Point2d(x, y);
			}
			else if (Point2::hasInstance(jsPt)) {
				cv_pt = Point2::Converter::unwrapUnchecked(jsPt);
			}
			else {
				return tryCatch.throwError("expected arg0 to consist of only Point2 or array of length 2");
			}
			self->self.emplace_back(cv::Point2i(cv_pt.x, cv_pt.y));
		}
	}
	self->hierarchy = cv::Vec4i(-1, -1, -1, -1);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Contour::GetPoints) {
	info.GetReturnValue().Set(Point2::ArrayWithCastConverter<cv::Point2i>::wrap(Contour::unwrapSelf(info)));
}

NAN_METHOD(Contour::ApproxPolyDP) {
	FF::executeSyncBinding(
		std::make_shared<ContourBindings::ApproxPolyDPWorker>(Contour::unwrapSelf(info)),
		"Contour::ApproxPolyDP",
		info
	);
}

NAN_METHOD(Contour::ApproxPolyDPAsync) {
	FF::executeAsyncBinding(
		std::make_shared<ContourBindings::ApproxPolyDPWorker>(Contour::unwrapSelf(info)),
		"Contour::ApproxPolyDPAsync",
		info
	);
}

NAN_METHOD(Contour::ApproxPolyDPContour) {
	FF::TryCatch tryCatch("Contour::ApproxPolyDPContour");
	double epsilon;
	bool closed;
	if (
		FF::DoubleConverter::arg(0, &epsilon, info) ||
		FF::BoolConverter::arg(1, &closed, info)
	) {
		return tryCatch.reThrow();
	}

	std::vector<cv::Point> curve;
	cv::approxPolyDP(Contour::unwrapSelf(info), curve, epsilon, closed);

	v8::Local<v8::Object> jsApprox = FF::newInstance(Nan::New(Contour::constructor));
	Contour* pContour = Contour::unwrapClassPtrUnchecked(jsApprox);
	pContour->setNativeObject(curve);
	pContour->hierarchy = cv::Vec4i(-1, -1, -1, -1);
	info.GetReturnValue().Set(jsApprox);
}

NAN_METHOD(Contour::ArcLength) {
	FF::TryCatch tryCatch("Contour::ArcLength");
	bool closed = false;
	if (FF::BoolConverter::optArg(0, &closed, info)) {
		return tryCatch.reThrow();
	}

	double arcLength = cv::arcLength(Contour::unwrapSelf(info), closed);
	info.GetReturnValue().Set(Nan::New(arcLength));
}

NAN_METHOD(Contour::BoundingRect) {
	info.GetReturnValue().Set(Rect::Converter::wrap(cv::boundingRect(Contour::unwrapSelf(info))));
}

NAN_METHOD(Contour::ConvexHull) {
	FF::TryCatch tryCatch("Contour::ConvexHull");
	bool clockwise = false;
	if (FF::BoolConverter::optArg(0, &clockwise, info)) {
		return tryCatch.reThrow();
	}

	std::vector<cv::Point> hullPoints;
	cv::convexHull(
		Contour::unwrapSelf(info),
		hullPoints,
		clockwise,
		true
	);
	v8::Local<v8::Object> jsHull = FF::newInstance(Nan::New(Contour::constructor));
	Contour* pContour = Contour::unwrapClassPtrUnchecked(jsHull);
	pContour->setNativeObject(hullPoints);
	pContour->hierarchy = cv::Vec4i(-1, -1, -1, -1);
	info.GetReturnValue().Set(jsHull);
}

NAN_METHOD(Contour::ConvexHullIndices) {
	FF::TryCatch tryCatch("Contour::ConvexHullIndices");
	bool clockwise = false;
	if (FF::BoolConverter::optArg(0, &clockwise, info)) {
		return tryCatch.reThrow();
	}

	std::vector<int> hullIndices;
	cv::convexHull(
		Contour::unwrapSelf(info),
		hullIndices,
		clockwise,
		false
	);
	info.GetReturnValue().Set(FF::IntArrayConverter::wrap(hullIndices));
}
NAN_METHOD(Contour::ConvexityDefects) {
	FF::TryCatch tryCatch("Contour::ConvexityDefects");
	std::vector<int> hull;
	if (FF::IntArrayConverter::arg(0, &hull, info)) {
		return tryCatch.reThrow();
	}

	std::vector<cv::Vec4d> defects;
	cv::convexityDefects(
		Contour::unwrapSelf(info),
		hull,
		defects
	);

	info.GetReturnValue().Set(Vec4::ArrayConverter::wrap(defects));
}

NAN_METHOD(Contour::MinEnclosingCircle) {
	cv::Point2f center;
	float radius;
	cv::minEnclosingCircle(Contour::unwrapSelf(info), center, radius);

	v8::Local<v8::Object> jsCircle = Nan::New<v8::Object>();
	Nan::Set(jsCircle, FF::newString("center"), Point2::Converter::wrap(center));
	Nan::Set(jsCircle, FF::newString("radius"), Nan::New((double)radius));
	info.GetReturnValue().Set(jsCircle);
}

NAN_METHOD(Contour::MinEnclosingTriangle) {
	std::vector<cv::Point2f> triangle;
	cv::minEnclosingTriangle(
		Contour::unwrapSelf(info),
		triangle
	);
	info.GetReturnValue().Set(Point2::ArrayWithCastConverter<cv::Point2f>::wrap(triangle));
}

NAN_METHOD(Contour::PointPolygonTest) {
	FF::TryCatch tryCatch("Contour::PointPolygonTest");
	cv::Point2d point;
	if (Point2::Converter::arg(0, &point, info)) {
		return tryCatch.reThrow();
	}

	double dist = cv::pointPolygonTest(
		Contour::unwrapSelf(info),
		point,
		true
	);
	info.GetReturnValue().Set(Nan::New(dist));
}

NAN_METHOD(Contour::MatchShapes) {
	FF::TryCatch tryCatch("Contour::MatchShapes");
	std::vector<cv::Point> contour2;
	uint method;
	if (
		Contour::Converter::arg(0, &contour2, info) ||
		FF::UintConverter::arg(1, &method, info)
	) {
		return tryCatch.reThrow();
	}

	// parameter not supported
	double parameter = 0.0;
	double cmp = cv::matchShapes(
		Contour::unwrapSelf(info),
		contour2,
		(int)method,
		parameter
	);
	info.GetReturnValue().Set(Nan::New(cmp));
}

NAN_METHOD(Contour::MinAreaRect) {
	info.GetReturnValue().Set(RotatedRect::Converter::wrap(cv::minAreaRect(Contour::unwrapSelf(info))));
}

NAN_METHOD(Contour::FitEllipse) {
	info.GetReturnValue().Set(RotatedRect::Converter::wrap(cv::fitEllipse(Contour::unwrapSelf(info))));
}

NAN_METHOD(Contour::_Moments) {
	info.GetReturnValue().Set(Moments::Converter::wrap(cv::moments(Contour::unwrapSelf(info))));
}

#endif
