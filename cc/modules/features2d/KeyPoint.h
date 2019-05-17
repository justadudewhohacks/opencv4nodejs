#include "macros.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include "Point2.h"

#ifndef FF_KEYPOINT_H_
#define FF_KEYPOINT_H_

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