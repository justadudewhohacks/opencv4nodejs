#include "WorldPoint.h"
#include "macros.h"

Nan::Persistent<v8::FunctionTemplate> WorldPoint::constructor;

NAN_MODULE_INIT(WorldPoint::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(WorldPoint::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("WorldPoint").ToLocalChecked());

  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("pt").ToLocalChecked(), GetPoint);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("color").ToLocalChecked(), GetColor);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("numObservations").ToLocalChecked(), GetNumObservations);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("isEstimated").ToLocalChecked(), GetIsEstimated);

  target->Set(Nan::New("WorldPoint").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(WorldPoint::New) {
	if (info.Length() > 0) {
		WorldPoint *worldPoint = new WorldPoint();
		v8::Local<v8::Object> jsonWorldPoint = info[0]->ToObject();
		worldPoint->setNativeProps(
			FF::jsArrayToMatrixd(v8::Local<v8::Array>::Cast(FF_GET_JS_PROP(jsonWorldPoint, point))),
			FF::jsArrayToMatrixd(v8::Local<v8::Array>::Cast(FF_GET_JS_PROP(jsonWorldPoint, color))),
			FF_GET_JS_PROP_INT(jsonWorldPoint, numObservations),
			FF_GET_JS_PROP(jsonWorldPoint, isEstimated)->BooleanValue()
		);
		worldPoint->Wrap(info.Holder());
	}
	else {
		(new WorldPoint())->Wrap(info.Holder());
	}
  info.GetReturnValue().Set(info.Holder());
}

NAN_GETTER(WorldPoint::GetPoint) {
	info.GetReturnValue().Set(FF::matrixdToJsArray(Nan::ObjectWrap::Unwrap<WorldPoint>(info.This())->point));
}

NAN_GETTER(WorldPoint::GetColor) {
  info.GetReturnValue().Set(FF::matrixdToJsArray(Nan::ObjectWrap::Unwrap<WorldPoint>(info.This())->color));
}

NAN_GETTER(WorldPoint::GetNumObservations) {
	info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<WorldPoint>(info.This())->numObservations);
}

NAN_GETTER(WorldPoint::GetIsEstimated) {
  info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<WorldPoint>(info.This())->isEstimated);
}

void WorldPoint::setNativeProps(Eigen::Vector3d point, Eigen::Vector3d color, int numObservations, bool isEstimated) {
	this->point = point;
	this->color = color;
	this->numObservations = numObservations;
	this->isEstimated = isEstimated;
};