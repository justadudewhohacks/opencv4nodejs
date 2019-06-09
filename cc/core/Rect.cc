#include "Rect.h"
#include "RectBindings.h"

Nan::Persistent<v8::FunctionTemplate> Rect::constructor;

NAN_MODULE_INIT(Rect::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Rect::New);
  Rect::constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Rect").ToLocalChecked());
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Rect::x_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Rect::y_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("width").ToLocalChecked(), Rect::width_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("height").ToLocalChecked(), Rect::height_getter);

  Nan::SetPrototypeMethod(ctor, "and", And);
  Nan::SetPrototypeMethod(ctor, "or", Or);
  Nan::SetPrototypeMethod(ctor, "toSquare", ToSquare);
  Nan::SetPrototypeMethod(ctor, "toSquareAsync", ToSquareAsync);
  Nan::SetPrototypeMethod(ctor, "pad", Pad);
  Nan::SetPrototypeMethod(ctor, "padAsync", PadAsync);
  Nan::SetPrototypeMethod(ctor, "rescale", Rescale);
  Nan::SetPrototypeMethod(ctor, "rescaleAsync", RescaleAsync);

  Nan::Set(target,Nan::New("Rect").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(Rect::New) {
	FF::TryCatch tryCatch("Rect::New");
	FF_ASSERT_CONSTRUCT_CALL();
  Rect* self = new Rect();
  if (info.Length() == 0) {
    self->self = cv::Rect2d();
  } else {
    if (info.Length() < 4) {
      return tryCatch.throwError("expected arguments x, y, width, height");
    }
    double x = info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    double y = info[1]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    double width = info[2]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    double height = info[3]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    self->self = cv::Rect2d(x, y, width, height);
  }
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Rect::And) {
  FF::executeSyncBinding(
    std::make_shared<RectBindings::AndWorker>(Rect::unwrapSelf(info)),
    "Rect::And",
    info
  );
}

NAN_METHOD(Rect::Or) {
  FF::executeSyncBinding(
    std::make_shared<RectBindings::OrWorker>(Rect::unwrapSelf(info)),
    "Rect::Or",
    info
  );
}

NAN_METHOD(Rect::ToSquare) {
  FF::executeSyncBinding(
    std::make_shared<RectBindings::ToSquareWorker>(Rect::unwrapSelf(info)),
    "Rect::ToSquare",
    info
  );
}

NAN_METHOD(Rect::ToSquareAsync) {
  FF::executeAsyncBinding(
    std::make_shared<RectBindings::ToSquareWorker>(Rect::unwrapSelf(info)),
    "Rect::ToSquareAsync",
    info
  );
}

NAN_METHOD(Rect::Pad) {
  FF::executeSyncBinding(
    std::make_shared<RectBindings::PadWorker>(Rect::unwrapSelf(info)),
    "Rect::Pad",
    info
  );
}

NAN_METHOD(Rect::PadAsync) {
  FF::executeAsyncBinding(
    std::make_shared<RectBindings::PadWorker>(Rect::unwrapSelf(info)),
    "Rect::PadAsync",
    info
  );
}

NAN_METHOD(Rect::Rescale) {
  FF::executeSyncBinding(
    std::make_shared<RectBindings::RescaleWorker>(Rect::unwrapSelf(info)),
    "Rect::Rescale",
    info
  );
}

NAN_METHOD(Rect::RescaleAsync) {
  FF::executeAsyncBinding(
    std::make_shared<RectBindings::RescaleWorker>(Rect::unwrapSelf(info)),
    "Rect::RescaleAsync",
    info
  );
}
