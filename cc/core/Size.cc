#include "Size.h"

Nan::Persistent<v8::FunctionTemplate> Size::constructor;

NAN_MODULE_INIT(Size::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Size::New);
	Size::constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("Size").ToLocalChecked());
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("width").ToLocalChecked(), Size::GetWidth);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("height").ToLocalChecked(), Size::GetHeight);

  target->Set(Nan::New("Size").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Size::New) {
	Size* self = new Size();
	if (info.Length() > 0) {
		if (info.Length() < 2) {
			return Nan::ThrowError("Size::New - expected arguments width, height");
		}
		double width = info[0]->NumberValue();
		double height = info[1]->NumberValue();
		self->size = cv::Size2d(width, height);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}