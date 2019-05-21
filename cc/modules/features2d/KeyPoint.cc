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

  Nan::Set(target,Nan::New("KeyPoint").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(KeyPoint::New) {
	FF_ASSERT_CONSTRUCT_CALL(KeyPoint);
	KeyPoint* self = new KeyPoint();

	if (info.Length() > 0) {
		FF::TryCatch tryCatch;

		cv::Point2d pt;
		double size, angle, response; 
		int octave, classId;
		if (
			Point2::Converter::arg(0, &pt, info) ||
			DoubleConverter::arg(1, &size, info) ||
			DoubleConverter::arg(2, &angle, info) ||
			DoubleConverter::arg(3, &response, info) ||
			IntConverter::arg(4, &octave, info) ||
			IntConverter::arg(5, &classId, info)
		) {
			v8::Local<v8::Value> err = tryCatch.formatCatchedError("KeyPoint::New");
			tryCatch.throwNew(err);
			return;
		}
		self->keyPoint = cv::KeyPoint(pt, size, angle, response, octave, classId);
	}

	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}
