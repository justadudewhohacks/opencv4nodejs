#include "macros.h"
#include "ArrayConverters.h"
#include "Point2.h"
#include <opencv2/core.hpp>
#include <opencv2/face.hpp>

#if CV_VERSION_MINOR >= 4

#ifndef __FF_FACEMARKAAMDATA_H__
#define __FF_FACEMARKAAMDATA_H__

typedef ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f> s0_converter;

class FacemarkAAMData : public Nan::ObjectWrap {
public:
  cv::face::FacemarkAAM::Data data;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static FF_GETTER_COMPLEX(FacemarkAAMData, s0Get, data.s0, s0_converter);
  static FF_SETTER_COMPLEX(FacemarkAAMData, s0, data.s0, std::vector<cv::Point2f>, s0_converter);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::face::FacemarkAAM::Data* getNativeObjectPtr() { return &data; }
	cv::face::FacemarkAAM::Data getNativeObject() { return data; }
};

#define FF_UNWRAP_FACEMARKAAMDATA(obj) FF_UNWRAP(obj, FacemarkAAMData)
#define FF_UNWRAP_FACEMARKAAMDATA_AND_GET(obj)                               \
  FF_UNWRAP_FACEMARKAAMDATA(obj)->data

#endif

#endif
