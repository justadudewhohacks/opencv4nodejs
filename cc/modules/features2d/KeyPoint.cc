#include "KeyPoint.h"

Nan::Persistent<v8::FunctionTemplate> KeyPoint::constructor;

NAN_MODULE_INIT(KeyPoint::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(KeyPoint::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
	instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("KeyPoint").ToLocalChecked());

  Nan::SetAccessor(instanceTemplate, Nan::New("localId").ToLocalChecked(), GetLocalId);
  Nan::SetAccessor(instanceTemplate, Nan::New("point").ToLocalChecked(), GetPoint);
  Nan::SetAccessor(instanceTemplate, Nan::New("angle").ToLocalChecked(), GetAngle);
  Nan::SetAccessor(instanceTemplate, Nan::New("classId").ToLocalChecked(), GetClassId);
  Nan::SetAccessor(instanceTemplate, Nan::New("response").ToLocalChecked(), GetResponse);
  Nan::SetAccessor(instanceTemplate, Nan::New("size").ToLocalChecked(), GetSize);
  Nan::SetAccessor(instanceTemplate, Nan::New("octave").ToLocalChecked(), GetOctave);

  target->Set(Nan::New("KeyPoint").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(KeyPoint::New) {
	FF_METHOD_CONTEXT("KeyPoint::New");
	KeyPoint* self = new KeyPoint();
  if (info.Length() > 0) {
		FF_ARG_INSTANCE(0, cv::Point2d pt, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
		FF_ARG_NUMBER(1, double size);
		FF_ARG_NUMBER(2, double angle);
		FF_ARG_NUMBER(3, double response);
		FF_ARG_INT(4, int octave);
		FF_ARG_INT(5, int classId);
		self->keyPoint = cv::KeyPoint(pt, size, angle, response, octave, classId);
  }
	self->Wrap(info.Holder());
  FF_RETURN(info.Holder());
}