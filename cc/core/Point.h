#include "macros.h"
#include <opencv2/core.hpp>
#include "Point2.h"
#include "Point3.h"

#ifndef __FF_POINT_H__
#define __FF_POINT_H__

// TODO replace this
#define FF_GET_JSPROP(obj, prop) Nan::Get(obj, FF_NEW_STRING(#prop)).ToLocalChecked()

#define FF_GET_JSPROP_REQUIRED(obj, var, prop, castType)																	\
	if (!FF_HAS(obj, #prop)) {																												\
		return Nan::ThrowError(FF_NEW_STRING("Object has no property: " + std::string(#prop)));	\
	}																																												\
	var = FF_GET_JSPROP(obj, prop)->castType();

#define FF_DESTRUCTURE_JSPROP_REQUIRED(obj, prop, castType)	\
	FF_GET_JSPROP_REQUIRED(obj, prop, prop, castType)

class Point : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
	static NAN_METHOD(NewPoint2);
	static NAN_METHOD(NewPoint3);

	template<typename type>
	static void unpackJSPoint2Array(std::vector<cv::Point_<type>> &pts, v8::Local<v8::Array> jsPts) {
		for (uint i = 0; i < jsPts->Length(); i++) {
			v8::Local<v8::Object> obj = Nan::To<v8::Object>(jsPts->Get(i)).ToLocalChecked();
			double x, y;
			FF_DESTRUCTURE_JSPROP_REQUIRED(obj, x, NumberValue)
			FF_DESTRUCTURE_JSPROP_REQUIRED(obj, y, NumberValue)
			pts.push_back(cv::Point_<type>(x, y));
		}
	};

	template<typename type>
	static v8::Local<v8::Array> packJSPoint2Array(std::vector<cv::Point_<type>> pts) {
		v8::Local<v8::Array> jsPts = Nan::New<v8::Array>(pts.size());
		for (int i = 0; i < jsPts->Length(); i++) {
			v8::Local<v8::Object> jsPt2 = FF_NEW_INSTANCE(Point2::constructor);
			FF_UNWRAP_PT2_AND_GET(jsPt2) = pts.at(i);
			jsPts->Set(i, jsPt2);
		}
		return jsPts;
	}

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
};

#endif