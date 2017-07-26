#include "Camera.h"
#include "macros.h"

Nan::Persistent<v8::FunctionTemplate> Camera::constructor;

NAN_MODULE_INIT(Camera::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Camera::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Camera").ToLocalChecked());

  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("pos").ToLocalChecked(), GetPosition);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("rot").ToLocalChecked(), GetRotation);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("principalPoint").ToLocalChecked(), GetPrincipalPoint);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("focalLength").ToLocalChecked(), GetFocalLength);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("imgWidth").ToLocalChecked(), GetImgWidth);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("imgHeight").ToLocalChecked(), GetImgHeight);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("isEstimated").ToLocalChecked(), GetIsEstimated);

  target->Set(Nan::New("Camera").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Camera::New) {
	if (info.Length() > 0) {
		Camera *camera = new Camera();
		v8::Local<v8::Object> jsonCamera = info[0]->ToObject();
		camera->setNativeProps(
			FF::jsArrayToMatrixd(v8::Local<v8::Array>::Cast(FF_GET_JS_PROP(jsonCamera, pos))),
			FF::jsArrayToMatrixd(v8::Local<v8::Array>::Cast(FF_GET_JS_PROP(jsonCamera, rot))),
			FF::jsArrayToMatrixd(v8::Local<v8::Array>::Cast(FF_GET_JS_PROP(jsonCamera, principalPoint))),
			FF_GET_JS_PROP_DOUBLE(jsonCamera, focalLength),
			FF_GET_JS_PROP_INT(jsonCamera, imgWidth),
			FF_GET_JS_PROP_INT(jsonCamera, imgHeight),
			FF_GET_JS_PROP(jsonCamera, isEstimated)->BooleanValue()
		);
		camera->Wrap(info.Holder());
	}
	else {
		(new Camera())->Wrap(info.Holder());
	}
  info.GetReturnValue().Set(info.Holder());
}


NAN_GETTER(Camera::GetPosition) {
	info.GetReturnValue().Set(FF::matrixdToJsArray(Nan::ObjectWrap::Unwrap<Camera>(info.This())->pos));
}

NAN_GETTER(Camera::GetRotation) {
  info.GetReturnValue().Set(FF::matrixdToJsArray(Nan::ObjectWrap::Unwrap<Camera>(info.This())->rot));
}

NAN_GETTER(Camera::GetPrincipalPoint) {
	info.GetReturnValue().Set(FF::matrixdToJsArray(Nan::ObjectWrap::Unwrap<Camera>(info.This())->principalPoint));
}

NAN_GETTER(Camera::GetFocalLength) {
	info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<Camera>(info.This())->focalLength);
}

NAN_GETTER(Camera::GetImgWidth) {
  info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<Camera>(info.This())->imgWidth);
}

NAN_GETTER(Camera::GetImgHeight) {
  info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<Camera>(info.This())->imgHeight);
}

NAN_GETTER(Camera::GetIsEstimated) {
  info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<Camera>(info.This())->isEstimated);
}

void Camera::setNativeProps(Eigen::Vector3d pos, Eigen::Matrix3d rot, Eigen::Vector2d principalPoint, 
	double focalLength, int imgWidth, int imgHeight, bool isEstimated) {

	this->pos = pos;
	this->rot = rot;
	this->principalPoint = principalPoint;
	this->focalLength = focalLength;
	this->imgWidth = imgWidth;
	this->imgHeight = imgHeight;
	this->isEstimated = isEstimated;
};