#include <nan.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include "macros.h"

#ifndef FF_KEYPOINT_H_
#define FF_KEYPOINT_H_

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

  static std::vector<cv::KeyPoint> unwrapJSKeyPointArray(v8::Local<v8::Array> jsKps) {
    std::vector<cv::KeyPoint> kps;
    for (uint i = 0; i < jsKps->Length(); i++) {
      KeyPoint* kp = Nan::ObjectWrap::Unwrap<KeyPoint>(Nan::To<v8::Object>(jsKps->Get(i)).ToLocalChecked());
      kps.push_back(kp->keyPoint);
    }
    return kps;
  };

  void setNativeProps(uint, cv::KeyPoint);
};

#endif