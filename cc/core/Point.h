#include <nan.h>
#include <opencv2/core.hpp>
#include "Point2.h"
#include "Point3.h"
#include "macros.h"

#ifndef __FF_POINT_H__
#define __FF_POINT_H__

class Point : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);

  static NAN_METHOD(New);
	static NAN_METHOD(NewPoint2);
	static NAN_METHOD(NewPoint3);

	static std::vector<cv::Point2d> unpackJSPoint2Array(v8::Local<v8::Array> jsPts) {
		std::vector<cv::Point2d> pts;
		for (uint i = 0; i < jsPts->Length(); i++) {
			v8::Local<v8::Object> obj = Nan::To<v8::Object>(jsPts->Get(i)).ToLocalChecked();
			pts.push_back(cv::Point2d(
				FF::getCheckedJsProp(obj, "x")->NumberValue(),
				FF::getCheckedJsProp(obj, "y")->NumberValue()
			));
		}
		return pts;
	};

	static std::vector<cv::Point3d> unpackJSPoint3Array(v8::Local<v8::Array> jsPts) {
		std::vector<cv::Point3d> pts;
		for (uint i = 0; i < jsPts->Length(); i++) {
			v8::Local<v8::Object> obj = Nan::To<v8::Object>(jsPts->Get(i)).ToLocalChecked();
			pts.push_back(cv::Point3d(
				FF::getCheckedJsProp(obj, "x")->NumberValue(),
				FF::getCheckedJsProp(obj, "y")->NumberValue(),
				FF::getCheckedJsProp(obj, "z")->NumberValue()
			));
		}
		return pts;
	};

	static Nan::Persistent<v8::FunctionTemplate> Point::constructor;
};

#endif