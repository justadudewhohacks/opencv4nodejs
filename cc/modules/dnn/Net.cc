#include "opencv2/core.hpp"

#if CV_VERSION_MINOR > 2

// cv 3.3+ should have dnn by default
//#ifdef HAVE_DNN

#include "Net.h"
#include "NetBindings.h"

Nan::Persistent<v8::FunctionTemplate> Net::constructor;

NAN_MODULE_INIT(Net::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Net::New);
  Net::constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Net").ToLocalChecked());

  Nan::SetPrototypeMethod(ctor, "setInput", SetInput);
  Nan::SetPrototypeMethod(ctor, "setInputAsync", SetInputAsync);
  Nan::SetPrototypeMethod(ctor, "forward", Forward);
  Nan::SetPrototypeMethod(ctor, "forwardAsync", ForwardAsync);

  target->Set(Nan::New("Net").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Net::New) {
  Net* self = new Net();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Net::SetInput) {
  FF::SyncBinding(
    std::make_shared<NetBindings::SetInputWorker>(Net::Converter::unwrap(info.This())),
    "Net::SetInput",
    info
  );
}

NAN_METHOD(Net::SetInputAsync) {
  FF::AsyncBinding(
    std::make_shared<NetBindings::SetInputWorker>(Net::Converter::unwrap(info.This())),
    "Net::SetInputAsync",
    info
  );
}

NAN_METHOD(Net::Forward) {
  FF::SyncBinding(
    std::make_shared<NetBindings::ForwardWorker>(Net::Converter::unwrap(info.This())),
    "Net::Forward",
    info
  );
}

NAN_METHOD(Net::ForwardAsync) {
  FF::AsyncBinding(
    std::make_shared<NetBindings::ForwardWorker>(Net::Converter::unwrap(info.This())),
    "Net::ForwardAsync",
    info
  );
}

#endif