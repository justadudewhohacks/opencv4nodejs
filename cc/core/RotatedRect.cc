#include "RotatedRect.h"

Nan::Persistent<v8::FunctionTemplate> RotatedRect::constructor;

NAN_MODULE_INIT(RotatedRect::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(RotatedRect::New);
	RotatedRect::constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("RotatedRect").ToLocalChecked());
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("angle"), RotatedRect::GetAngle);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("center"), RotatedRect::GetCenter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("size"), RotatedRect::GetSize);

	Nan::SetPrototypeMethod(ctor, "boundingRect", RotatedRect::BoundingRect);

  target->Set(Nan::New("RotatedRect").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(RotatedRect::New) {
	RotatedRect* self = new RotatedRect();
	if (info.Length() == 0) {
		self->rect = cv::RotatedRect();
	} else {
		if (info.Length() < 3) {
			return Nan::ThrowError("RotatedRect::New - expected arguments center, size, angle");
		}
		if (!FF_IS_INSTANCE(Point2::constructor, info[0])) {
			return Nan::ThrowError("RotatedRect::New - expected arg0 to be an instance of Point2");
		}
		if (!FF_IS_INSTANCE(Size::constructor, info[1])) {
			return Nan::ThrowError("RotatedRect::New - expected arg1 to be an instance of Size");
		}
		double angle = info[2]->NumberValue();

		self->rect = cv::RotatedRect(
			FF_UNWRAP_PT2_AND_GET(info[0]->ToObject()),
			FF_UNWRAP_SIZE_AND_GET(info[1]->ToObject()),
			angle
		);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}