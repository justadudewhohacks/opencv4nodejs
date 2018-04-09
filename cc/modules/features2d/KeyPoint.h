#include "macros.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include "Point2.h"

#ifndef FF_KEYPOINT_H_
#define FF_KEYPOINT_H_

#define FF_PACK_KEYPOINT_ARRAY(var, kps)									\
	FF_ARR var = FF_NEW_ARRAY(kps.size());									\
	for (int i = 0; i < kps.size(); i++) {									\
		FF_OBJ jsKp = FF_NEW_INSTANCE(KeyPoint::constructor);	\
		FF_UNWRAP(jsKp, KeyPoint)->keyPoint = kps.at(i);			\
		var->Set(i, jsKp);																		\
	}

#define FF_UNPACK_KEYPOINT_ARRAY_TO(vec, jsKps)																									\
	for (uint i = 0; i < jsKps->Length(); i++) {																									\
		cv::KeyPoint kp;																																						\
		FF_REQUIRE_INSTANCE(KeyPoint::constructor, jsKps->Get(i), "expected instance of KeyPoint"); \
		vec.push_back(FF_UNWRAP(FF_CAST_OBJ(jsKps->Get(i)), KeyPoint)->keyPoint);										\
	}

#define FF_UNPACK_KEYPOINT_ARRAY(var, jsKps)																										\
	std::vector<cv::KeyPoint> var;																																\
	FF_UNPACK_KEYPOINT_ARRAY_TO(var, jsKps)

class KeyPoint : public Nan::ObjectWrap {
public:
  int localId = -1;
  cv::KeyPoint keyPoint;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER_JSOBJ(KeyPoint, GetPoint, keyPoint.pt, FF_UNWRAP_PT2_AND_GET, Point2::constructor);
  static FF_GETTER(KeyPoint, GetLocalId, localId);
	static FF_GETTER(KeyPoint, GetAngle, keyPoint.angle);
	static FF_GETTER(KeyPoint, GetClassId, keyPoint.class_id);
	static FF_GETTER(KeyPoint, GetResponse, keyPoint.response);
	static FF_GETTER(KeyPoint, GetSize, keyPoint.size);
	static FF_GETTER(KeyPoint, GetOctave, keyPoint.octave);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::KeyPoint* getNativeObjectPtr() { return &keyPoint; }
	cv::KeyPoint getNativeObject() { return keyPoint; }

	typedef InstanceConverter<KeyPoint, cv::KeyPoint> Converter;

	static const char* getClassName() {
		return "KeyPoint";
	}
};

#endif