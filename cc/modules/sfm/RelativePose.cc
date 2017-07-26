#include "RelativePose.h"
#include "macros.h"

Nan::Persistent<v8::FunctionTemplate> RelativePose::constructor;

NAN_MODULE_INIT(RelativePose::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(RelativePose::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("RelativePose").ToLocalChecked());

  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("pos").ToLocalChecked(), GetPosition);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("rot").ToLocalChecked(), GetRotation);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("rotVec").ToLocalChecked(), GetRotationAsAngleAxis);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("essentialMat").ToLocalChecked(), GetEssentialMatrix);

  target->Set(Nan::New("RelativePose").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(RelativePose::New) {
	if (info.Length() > 0) {
		RelativePose *relativePose = new RelativePose();
		v8::Local<v8::Object> jsonRelativePose = info[0]->ToObject();
		theia::RelativePose rp;
		rp.position = FF::jsArrayToMatrixd(v8::Local<v8::Array>::Cast(FF_GET_JS_PROP(jsonRelativePose, pos)));
		rp.rotation = FF::jsArrayToMatrixd(v8::Local<v8::Array>::Cast(FF_GET_JS_PROP(jsonRelativePose, rot)));
		rp.essential_matrix = FF::jsArrayToMatrixd(v8::Local<v8::Array>::Cast(FF_GET_JS_PROP(jsonRelativePose, essentialMat)));
		relativePose->setNativeProps(rp);
		relativePose->Wrap(info.Holder());
	}
	else {
		(new RelativePose())->Wrap(info.Holder());
	}
  info.GetReturnValue().Set(info.Holder());
}

NAN_GETTER(RelativePose::GetPosition) {
	info.GetReturnValue().Set(FF::matrixdToJsArray(Nan::ObjectWrap::Unwrap<RelativePose>(info.This())->relativePose.position));
}

NAN_GETTER(RelativePose::GetRotation) {
  info.GetReturnValue().Set(FF::matrixdToJsArray(Nan::ObjectWrap::Unwrap<RelativePose>(info.This())->relativePose.rotation));
}

NAN_GETTER(RelativePose::GetRotationAsAngleAxis) {
  info.GetReturnValue().Set(FF::matrixdToJsArray(Nan::ObjectWrap::Unwrap<RelativePose>(info.This())->rotationAsAngleAxis));
}

NAN_GETTER(RelativePose::GetEssentialMatrix) {
	info.GetReturnValue().Set(FF::matrixdToJsArray(Nan::ObjectWrap::Unwrap<RelativePose>(info.This())->relativePose.essential_matrix));
}

void RelativePose::setNativeProps(theia::RelativePose relativePose) {
	this->relativePose = relativePose;
	theia::Camera cam;
	cam.SetOrientationFromRotationMatrix(relativePose.rotation);
	this->rotationAsAngleAxis = cam.GetOrientationAsAngleAxis();
};