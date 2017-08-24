#include "Rect.h"

Nan::Persistent<v8::FunctionTemplate> Rect::constructor;

NAN_MODULE_INIT(Rect::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Rect::New);
	Rect::constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("Rect").ToLocalChecked());
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Rect::GetX);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Rect::GetY);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("width").ToLocalChecked(), Rect::GetWidth);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("height").ToLocalChecked(), Rect::GetHeight);

  target->Set(Nan::New("Rect").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Rect::New) {
	Rect* self = new Rect();
	if (info.Length() == 0) {
		self->rect = cv::Rect2d();
	} else {
		if (info.Length() < 4) {
			return Nan::ThrowError("Rect::New - expected arguments x, y, width, height");
		}
		double x = info[0]->NumberValue();
		double y = info[1]->NumberValue();
		double width = info[2]->NumberValue();
		double height = info[3]->NumberValue();
		self->rect = cv::Rect2d(x, y, width, height);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}