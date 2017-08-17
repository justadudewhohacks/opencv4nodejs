#include <nan.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include "macros.h"

#ifndef FF_KEYPOINT_H_
#define FF_KEYPOINT_H_

#define FF_UNWRAP_KEYPOINT_ARRAY(jsKps, kps)																										\
	for (uint i = 0; i < jsKps->Length(); i++) {																									\
		cv::KeyPoint kp;																																						\
		FF_REQUIRE_INSTANCE(KeyPoint::constructor, jsKps->Get(i), "expected instance of KeyPoint"); \
		kps.push_back(FF_UNWRAP(FF_CAST_OBJ(jsKps->Get(i)), KeyPoint)->keyPoint);										\
	}

class KeyPoint : public Nan::ObjectWrap {
public:
  uint localId;
  cv::KeyPoint keyPoint;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static FF_GETTER(KeyPoint, GetLocalId, localId);
	static FF_GETTER(KeyPoint, GetX, keyPoint.pt.x);
	static FF_GETTER(KeyPoint, GetY, keyPoint.pt.y);
	static FF_GETTER(KeyPoint, GetAngle, keyPoint.angle);
	static FF_GETTER(KeyPoint, GetClassId, keyPoint.class_id);
	static FF_GETTER(KeyPoint, GetResponse, keyPoint.response);
	static FF_GETTER(KeyPoint, GetSize, keyPoint.size);
	static FF_GETTER(KeyPoint, GetOctave, keyPoint.octave);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  void setNativeProps(uint, cv::KeyPoint);
};

#endif