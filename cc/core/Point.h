#include "macros.h"
#include <opencv2/core.hpp>
#include "Point2.h"
#include "Point3.h"

#ifndef __FF_POINT_H__
#define __FF_POINT_H__

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
			if (DoubleConverter::prop(&x, "x", obj) || DoubleConverter::prop(&y, "y", obj)) {
				return;
			}
			pts.push_back(cv::Point_<type>(x, y));
		}
	};

	template<typename type>
	static v8::Local<v8::Array> packJSPoint2Array(std::vector<cv::Point_<type>> pts) {
		v8::Local<v8::Array> jsPts = Nan::New<v8::Array>(pts.size());
		for (uint i = 0; i < jsPts->Length(); i++) {
			v8::Local<v8::Object> jsPt2 = FF_NEW_INSTANCE(Point2::constructor);
			FF_UNWRAP_PT2_AND_GET(jsPt2) = pts.at(i);
			jsPts->Set(i, jsPt2);
		}
		return jsPts;
	}
	
	template<typename type>
	static v8::Local<v8::Array> packJSPoint3Array(std::vector<cv::Point3_<type>> pts) {
		v8::Local<v8::Array> jsPts = Nan::New<v8::Array>(pts.size());
		for (uint i = 0; i < jsPts->Length(); i++) {
			v8::Local<v8::Object> jsPt3 = FF_NEW_INSTANCE(Point3::constructor);
			FF_UNWRAP_PT3_AND_GET(jsPt3) = pts.at(i);
			jsPts->Set(i, jsPt3);
		}
		return jsPts;
	}
	
	template<typename type>
	static void unpackJSPoint3Array(std::vector<cv::Point3_<type>> &pts, v8::Local<v8::Array> jsPts) {
		for (uint i = 0; i < jsPts->Length(); i++) {
			v8::Local<v8::Object> obj = Nan::To<v8::Object>(jsPts->Get(i)).ToLocalChecked();
			double x, y, z;

			if (DoubleConverter::prop(&x, "x", obj) || DoubleConverter::prop(&y, "y", obj) || DoubleConverter::prop(&z, "z", obj)) {
				return;
			}
			pts.push_back(cv::Point3_<type>(x, y, z));
		}
	};
};

#endif
