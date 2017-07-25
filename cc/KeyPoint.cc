#include "KeyPoint.h"
#include "macros.h"

Nan::Persistent<v8::FunctionTemplate> KeyPoint::constructor;

NAN_MODULE_INIT(KeyPoint::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(KeyPoint::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("KeyPoint").ToLocalChecked());

  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("localId").ToLocalChecked(), GetLocalId);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), GetX);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), GetY);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("angle").ToLocalChecked(), GetAngle);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("classId").ToLocalChecked(), GetClassId);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("response").ToLocalChecked(), GetResponse);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("size").ToLocalChecked(), GetSize);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("octave").ToLocalChecked(), GetOctave);

  target->Set(Nan::New("KeyPoint").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(KeyPoint::New) {
  if (info.Length() > 0) {
    // TODO check args
    KeyPoint *keyPoint = new KeyPoint();
    v8::Local<v8::Object> jsKp = info[0]->ToObject();
    keyPoint->setNativeProps(
      (uint)Nan::Get(jsKp, Nan::New("localId").ToLocalChecked()).ToLocalChecked()->NumberValue(),
      cv::KeyPoint(
				FF_GET_JS_PROP_FLOAT(jsKp, x),
				FF_GET_JS_PROP_FLOAT(jsKp, y),
				FF_GET_JS_PROP_FLOAT(jsKp, size),
				FF_GET_JS_PROP_FLOAT(jsKp, angle),
				FF_GET_JS_PROP_FLOAT(jsKp, response),
				FF_GET_JS_PROP_INT(jsKp, octave),
				FF_GET_JS_PROP_INT(jsKp, classId)
      )
    );
    keyPoint->Wrap(info.Holder());
  } else {
    (new KeyPoint())->Wrap(info.Holder());
  }
  info.GetReturnValue().Set(info.Holder());
}

NAN_GETTER(KeyPoint::GetLocalId) {
  info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<KeyPoint>(info.This())->localId);
}

NAN_GETTER(KeyPoint::GetX) {
  info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<KeyPoint>(info.This())->keyPoint.pt.x);
}

NAN_GETTER(KeyPoint::GetY) {
  info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<KeyPoint>(info.This())->keyPoint.pt.y);
}

NAN_GETTER(KeyPoint::GetAngle) {
  info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<KeyPoint>(info.This())->keyPoint.angle);
}

NAN_GETTER(KeyPoint::GetClassId) {
  info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<KeyPoint>(info.This())->keyPoint.class_id);
}

NAN_GETTER(KeyPoint::GetResponse) {
  info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<KeyPoint>(info.This())->keyPoint.response);
}

NAN_GETTER(KeyPoint::GetSize) {
  info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<KeyPoint>(info.This())->keyPoint.size);
}

NAN_GETTER(KeyPoint::GetOctave) {
  info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<KeyPoint>(info.This())->keyPoint.octave);
}

void KeyPoint::setNativeProps(uint localId, cv::KeyPoint keyPoint) {
  this->localId = localId;
  this->keyPoint = keyPoint;
};