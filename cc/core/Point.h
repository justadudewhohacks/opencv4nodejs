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

	static void unpackJSPoint2Array(std::vector<cv::Point2d> &pts, v8::Local<v8::Array> jsPts) {
		for (uint i = 0; i < jsPts->Length(); i++) {
			v8::Local<v8::Object> obj = Nan::To<v8::Object>(jsPts->Get(i)).ToLocalChecked();
			double x, y;
			FF_DESTRUCTURE_JSPROP_REQUIRED(obj, x, NumberValue)
			FF_DESTRUCTURE_JSPROP_REQUIRED(obj, y, NumberValue)
			pts.push_back(cv::Point2d(x, y));
		}
	};

	static void unpackJSPoint3Array(std::vector<cv::Point3d> &pts, v8::Local<v8::Array> jsPts) {
		for (uint i = 0; i < jsPts->Length(); i++) {
			v8::Local<v8::Object> obj = Nan::To<v8::Object>(jsPts->Get(i)).ToLocalChecked();
			double x, y, z;
			FF_DESTRUCTURE_JSPROP_REQUIRED(obj, x, NumberValue)
			FF_DESTRUCTURE_JSPROP_REQUIRED(obj, y, NumberValue)
			FF_DESTRUCTURE_JSPROP_REQUIRED(obj, z, NumberValue)
			pts.push_back(cv::Point3d(x, y, z));
		}
	};

	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif