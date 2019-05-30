#include "RotatedRect.h"

Nan::Persistent<v8::FunctionTemplate> RotatedRect::constructor;

NAN_MODULE_INIT(RotatedRect::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(RotatedRect::New);
	RotatedRect::constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("RotatedRect").ToLocalChecked());
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("angle"), RotatedRect::GetAngle);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("center"), RotatedRect::GetCenter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("size"), RotatedRect::GetSize);

	Nan::SetPrototypeMethod(ctor, "boundingRect", RotatedRect::BoundingRect);

  Nan::Set(target,Nan::New("RotatedRect").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(RotatedRect::New) {
	FF_ASSERT_CONSTRUCT_CALL(RotatedRect);
	RotatedRect* self = new RotatedRect();
	if (info.Length() == 0) {
		self->rect = cv::RotatedRect();
	} else {
		if (info.Length() < 3) {
			return Nan::ThrowError("RotatedRect::New - expected arguments center, size, angle");
		}
		if (!Point2::Converter::hasInstance(info[0])) {
			return Nan::ThrowError("RotatedRect::New - expected arg0 to be an instance of Point2");
		}
		if (!Size::Converter::hasInstance(info[1])) {
			return Nan::ThrowError("RotatedRect::New - expected arg1 to be an instance of Size");
		}
		double angle = info[2]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();

		self->rect = cv::RotatedRect(
			Point2::Converter::unwrap(info[0]),
			Size::Converter::unwrap(info[1]),
			angle
		);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}
