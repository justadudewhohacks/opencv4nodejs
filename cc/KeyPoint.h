#include <nan.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>

class KeyPoint : public Nan::ObjectWrap {
public:
  uint localId;
  cv::KeyPoint keyPoint;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static NAN_GETTER(GetLocalId);
  static NAN_GETTER(GetX);
  static NAN_GETTER(GetY);
  static NAN_GETTER(GetAngle);
  static NAN_GETTER(GetClassId);
  static NAN_GETTER(GetResponse);
  static NAN_GETTER(GetSize);
  static NAN_GETTER(GetOctave);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static std::vector<cv::KeyPoint> unwrapJSKps(v8::Local<v8::Array> jsKps) {
    std::vector<cv::KeyPoint> kps;
    for (uint i = 0; i < jsKps->Length(); i++) {
      KeyPoint* kp = Nan::ObjectWrap::Unwrap<KeyPoint>(Nan::To<v8::Object>(jsKps->Get(i)).ToLocalChecked());
      kps.push_back(kp->keyPoint);
    }
    return kps;
  };

  void setNativeProps(uint localId, cv::KeyPoint);
};
