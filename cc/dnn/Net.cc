#include "opencv_modules.h"

#ifdef HAVE_OPENCV_DNN

#include "opencv2/core.hpp"
#include "macros.h"

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
  Nan::SetPrototypeMethod(ctor, "getLayerNames", GetLayerNames);
  Nan::SetPrototypeMethod(ctor, "getLayerNamesAsync", GetLayerNamesAsync);
  Nan::SetPrototypeMethod(ctor, "getUnconnectedOutLayers", GetUnconnectedOutLayers);
  Nan::SetPrototypeMethod(ctor, "getUnconnectedOutLayersAsync", GetUnconnectedOutLayersAsync);

  Nan::Set(target,Nan::New("Net").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(Net::New) {
	FF::TryCatch tryCatch("Net::New");
	FF_ASSERT_CONSTRUCT_CALL();
  Net* self = new Net();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Net::SetInput) {
  FF::executeSyncBinding(
    std::make_shared<NetBindings::SetInputWorker>(Net::unwrapSelf(info)),
    "Net::SetInput",
    info
  );
}

NAN_METHOD(Net::SetInputAsync) {
  FF::executeAsyncBinding(
    std::make_shared<NetBindings::SetInputWorker>(Net::unwrapSelf(info)),
    "Net::SetInputAsync",
    info
  );
}

NAN_METHOD(Net::Forward) {
  FF::executeSyncBinding(
    std::make_shared<NetBindings::ForwardWorker>(Net::unwrapSelf(info)),
    "Net::Forward",
    info
  );
}

NAN_METHOD(Net::ForwardAsync) {
  FF::executeAsyncBinding(
    std::make_shared<NetBindings::ForwardWorker>(Net::unwrapSelf(info)),
    "Net::ForwardAsync",
    info
  );
}

NAN_METHOD(Net::GetLayerNames) {
  FF::executeSyncBinding(
      std::make_shared<NetBindings::GetLayerNamesWorker>(Net::unwrapSelf(info)),
      "Net::GetLayerNames",
      info);
}

NAN_METHOD(Net::GetLayerNamesAsync) {
  FF::executeAsyncBinding(
      std::make_shared<NetBindings::GetLayerNamesWorker>(Net::unwrapSelf(info)),
      "Net::GetLayerNamesAsync",
      info);
}

NAN_METHOD(Net::GetUnconnectedOutLayers) {
  FF::executeSyncBinding(
      std::make_shared<NetBindings::GetUnconnectedOutLayersWorker>(Net::unwrapSelf(info)),
      "Net::GetUnconnectedOutLayers",
      info);
}

NAN_METHOD(Net::GetUnconnectedOutLayersAsync) {
  FF::executeAsyncBinding(
      std::make_shared<NetBindings::GetUnconnectedOutLayersWorker>(Net::unwrapSelf(info)),
      "Net::GetUnconnectedOutLayersAsync",
      info);
}

#endif
