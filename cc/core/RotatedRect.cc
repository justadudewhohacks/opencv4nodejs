#include "RotatedRect.h"

Nan::Persistent<v8::FunctionTemplate> RotatedRect::constructor;

NAN_MODULE_INIT(RotatedRect::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(RotatedRect::New);
	RotatedRect::constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("RotatedRect").ToLocalChecked());
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("angle"), RotatedRect::angle_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("center"), RotatedRect::center_getter);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString("size"), RotatedRect::size_getter);

	Nan::SetPrototypeMethod(ctor, "boundingRect", RotatedRect::BoundingRect);

  Nan::Set(target,Nan::New("RotatedRect").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(RotatedRect::New) {
	FF::TryCatch tryCatch("RotatedRect::New");
	FF_ASSERT_CONSTRUCT_CALL();
	RotatedRect* self = new RotatedRect();
	if (info.Length() == 0) {
		self->self = cv::RotatedRect();
	} else {
		if (info.Length() < 3) {
			return tryCatch.throwError("expected arguments center, size, angle");
		}
		if (!Point2::hasInstance(info[0])) {
			return tryCatch.throwError("expected arg0 to be an instance of Point2");
		}
		if (!Size::hasInstance(info[1])) {
			return tryCatch.throwError("expected arg1 to be an instance of Size");
		}
		double angle = info[2]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();

		self->self = cv::RotatedRect(
			Point2::Converter::unwrapUnchecked(info[0]),
			Size::Converter::unwrapUnchecked(info[1]),
			angle
		);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}
