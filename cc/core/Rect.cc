#include "Rect.h"
#include "RectBindings.h"

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

  Nan::SetPrototypeMethod(ctor, "and", And);
  Nan::SetPrototypeMethod(ctor, "or", Or);
  Nan::SetPrototypeMethod(ctor, "toSquare", ToSquare);
  Nan::SetPrototypeMethod(ctor, "toSquareAsync", ToSquareAsync);
  Nan::SetPrototypeMethod(ctor, "pad", Pad);
  Nan::SetPrototypeMethod(ctor, "padAsync", PadAsync);
  Nan::SetPrototypeMethod(ctor, "rescale", Rescale);
  Nan::SetPrototypeMethod(ctor, "rescaleAsync", RescaleAsync);

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

NAN_METHOD(Rect::And) {
  FF::SyncBinding(
    std::make_shared<RectBindings::AndWorker>(Rect::Converter::unwrap(info.This())),
    "Rect::And",
    info
  );
}

NAN_METHOD(Rect::Or) {
  FF::SyncBinding(
    std::make_shared<RectBindings::OrWorker>(Rect::Converter::unwrap(info.This())),
    "Rect::Or",
    info
  );
}

NAN_METHOD(Rect::ToSquare) {
  FF::SyncBinding(
    std::make_shared<RectBindings::ToSquareWorker>(Rect::Converter::unwrap(info.This())),
    "Rect::ToSquare",
    info
  );
}

NAN_METHOD(Rect::ToSquareAsync) {
  FF::AsyncBinding(
    std::make_shared<RectBindings::ToSquareWorker>(Rect::Converter::unwrap(info.This())),
    "Rect::ToSquareAsync",
    info
  );
}

NAN_METHOD(Rect::Pad) {
  FF::SyncBinding(
    std::make_shared<RectBindings::PadWorker>(Rect::Converter::unwrap(info.This())),
    "Rect::Pad",
    info
  );
}

NAN_METHOD(Rect::PadAsync) {
  FF::AsyncBinding(
    std::make_shared<RectBindings::PadWorker>(Rect::Converter::unwrap(info.This())),
    "Rect::PadAsync",
    info
  );
}

NAN_METHOD(Rect::Rescale) {
  FF::SyncBinding(
    std::make_shared<RectBindings::RescaleWorker>(Rect::Converter::unwrap(info.This())),
    "Rect::Rescale",
    info
  );
}

NAN_METHOD(Rect::RescaleAsync) {
  FF::AsyncBinding(
    std::make_shared<RectBindings::RescaleWorker>(Rect::Converter::unwrap(info.This())),
    "Rect::RescaleAsync",
    info
  );
}
