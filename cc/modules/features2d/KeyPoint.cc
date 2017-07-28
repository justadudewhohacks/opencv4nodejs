#include "KeyPoint.h"

Nan::Persistent<v8::FunctionTemplate> KeyPoint::constructor;

NAN_MODULE_INIT(KeyPoint::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(KeyPoint::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
	instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("KeyPoint").ToLocalChecked());

  Nan::SetAccessor(instanceTemplate, Nan::New("localId").ToLocalChecked(), GetLocalId);
  Nan::SetAccessor(instanceTemplate, Nan::New("x").ToLocalChecked(), GetX);
  Nan::SetAccessor(instanceTemplate, Nan::New("y").ToLocalChecked(), GetY);
  Nan::SetAccessor(instanceTemplate, Nan::New("angle").ToLocalChecked(), GetAngle);
  Nan::SetAccessor(instanceTemplate, Nan::New("classId").ToLocalChecked(), GetClassId);
  Nan::SetAccessor(instanceTemplate, Nan::New("response").ToLocalChecked(), GetResponse);
  Nan::SetAccessor(instanceTemplate, Nan::New("size").ToLocalChecked(), GetSize);
  Nan::SetAccessor(instanceTemplate, Nan::New("octave").ToLocalChecked(), GetOctave);

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
				FF_GET_JSPROP_FLOAT(jsKp, x),
				FF_GET_JSPROP_FLOAT(jsKp, y),
				FF_GET_JSPROP_FLOAT(jsKp, size),
				FF_GET_JSPROP_FLOAT(jsKp, angle),
				FF_GET_JSPROP_FLOAT(jsKp, response),
				FF_GET_JSPROP_INT(jsKp, octave),
				FF_GET_JSPROP_INT(jsKp, classId)
      )
    );
    keyPoint->Wrap(info.Holder());
  } else {
    (new KeyPoint())->Wrap(info.Holder());
  }
  info.GetReturnValue().Set(info.Holder());
}

void KeyPoint::setNativeProps(uint localId, cv::KeyPoint keyPoint) {
  this->localId = localId;
  this->keyPoint = keyPoint;
};