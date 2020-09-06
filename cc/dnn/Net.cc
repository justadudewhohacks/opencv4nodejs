#include "opencv_modules.h"

#ifdef HAVE_OPENCV_DNN

#include "opencv2/core.hpp"
#include "opencv2/dnn.hpp"
#include "macros.h"

#include "Net.h"
#include "NetBindings.h"

// using namespace cv::dnn;

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

  // Change Backend Functions
  Nan::SetPrototypeMethod(ctor, "setPreferableBackend", SetPreferableBackend);
  Nan::SetPrototypeMethod(ctor, "setPreferableTarget", SetPreferableTarget);
  
  // DNN Backend Options
	// ----- For now hardcoded
	// DNN_BACKEND_DEFAULT = 0,
	// DNN_BACKEND_HALIDE,
	// DNN_BACKEND_INFERENCE_ENGINE,            //!< Intel's Inference Engine computational backend
	// 											//!< @sa setInferenceEngineBackendType
	// DNN_BACKEND_OPENCV,
	// DNN_BACKEND_VKCOM,
	// DNN_BACKEND_CUDA

  
  FF_SET_JS_PROP(target, DNN_BACKEND_DEFAULT, Nan::New<v8::Integer>(cv::dnn::DNN_BACKEND_DEFAULT));
  FF_SET_JS_PROP(target, DNN_BACKEND_HALIDE, Nan::New<v8::Integer>(cv::dnn::DNN_BACKEND_HALIDE));
  FF_SET_JS_PROP(target, DNN_BACKEND_INFERENCE_ENGINE, Nan::New<v8::Integer>(cv::dnn::DNN_BACKEND_INFERENCE_ENGINE));
  FF_SET_JS_PROP(target, DNN_BACKEND_OPENCV, Nan::New<v8::Integer>(cv::dnn::DNN_BACKEND_OPENCV));
  FF_SET_JS_PROP(target, DNN_BACKEND_VKCOM, Nan::New<v8::Integer>(cv::dnn::DNN_BACKEND_VKCOM));
  FF_SET_JS_PROP(target, DNN_BACKEND_CUDA, Nan::New<v8::Integer>(cv::dnn::DNN_BACKEND_CUDA));


  // DNN_TARGET_CPU = 0,
  // DNN_TARGET_OPENCL,
  // DNN_TARGET_OPENCL_FP16,
  // DNN_TARGET_MYRIAD,
  // DNN_TARGET_VULKAN,
  // DNN_TARGET_FPGA,  //!< FPGA device with CPU fallbacks using Inference Engine's Heterogeneous plugin.
  // DNN_TARGET_CUDA,
  // DNN_TARGET_CUDA_FP16

  FF_SET_JS_PROP(target, DNN_TARGET_CPU, Nan::New<v8::Integer>(cv::dnn::DNN_TARGET_CPU));
  FF_SET_JS_PROP(target, DNN_TARGET_OPENCL, Nan::New<v8::Integer>(cv::dnn::DNN_TARGET_OPENCL));
  FF_SET_JS_PROP(target, DNN_TARGET_OPENCL_FP16, Nan::New<v8::Integer>(cv::dnn::DNN_TARGET_OPENCL_FP16));
  FF_SET_JS_PROP(target, DNN_TARGET_MYRIAD, Nan::New<v8::Integer>(cv::dnn::DNN_TARGET_MYRIAD));
  FF_SET_JS_PROP(target, DNN_TARGET_VULKAN, Nan::New<v8::Integer>(cv::dnn::DNN_TARGET_VULKAN));
  FF_SET_JS_PROP(target, DNN_TARGET_FPGA, Nan::New<v8::Integer>(cv::dnn::DNN_TARGET_FPGA));
  FF_SET_JS_PROP(target, DNN_TARGET_CUDA, Nan::New<v8::Integer>(cv::dnn::DNN_TARGET_CUDA));
  FF_SET_JS_PROP(target, DNN_TARGET_CUDA_FP16, Nan::New<v8::Integer>(cv::dnn::DNN_TARGET_CUDA_FP16));
  





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

// ----------------------------------------------
// ----------------------------------------------

// Change Backend Functions
NAN_METHOD(Net::SetPreferableBackend) {
  FF::executeSyncBinding(
    std::make_shared<NetBindings::SetPreferableBackendWorker>(Net::unwrapSelf(info)),
    "Net::SetPreferableBackend",
    info
  );
}

NAN_METHOD(Net::SetPreferableTarget) {
  FF::executeSyncBinding(
    std::make_shared<NetBindings::SetPreferableTargetWorker>(Net::unwrapSelf(info)),
    "Net::SetPreferableTarget",
    info
  );
}


#endif
