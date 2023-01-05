#include "opencv_modules.h"

#ifdef HAVE_OPENCV_DNN

#include "opencv2/core.hpp"
#include "macros.h"
#include "dnn.h"
#include "dnnBindings.h"

#define FF_CONST_TYPE(CONST, VALUE) \
	Nan::Set(target, Nan::New<v8::String>(#CONST).ToLocalChecked(), Nan::New<v8::Integer>(VALUE));

NAN_MODULE_INIT(Dnn::Init) {

#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
  FF_CONST_TYPE(DNN_BACKEND_OPENCV, cv::dnn::DNN_BACKEND_OPENCV)
#endif

#if CV_VERSION_GREATER_EQUAL(3, 4, 1)
  FF_CONST_TYPE(DNN_BACKEND_INFERENCE_ENGINE, cv::dnn::DNN_BACKEND_INFERENCE_ENGINE)
#endif

#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  FF_CONST_TYPE(DNN_BACKEND_HALIDE, cv::dnn::DNN_BACKEND_HALIDE)
#endif

#if CV_VERSION_GREATER_EQUAL(4, 2, 0)
  FF_CONST_TYPE(DNN_BACKEND_CUDA, cv::dnn::DNN_BACKEND_CUDA)
#endif

  FF_CONST_TYPE(DNN_TARGET_CPU, cv::dnn::DNN_TARGET_CPU)

#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  FF_CONST_TYPE(DNN_TARGET_OPENCL, cv::dnn::DNN_TARGET_OPENCL)
#endif

#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
  FF_CONST_TYPE(DNN_TARGET_OPENCL_FP16, cv::dnn::DNN_TARGET_OPENCL_FP16)
  FF_CONST_TYPE(DNN_TARGET_MYRIAD, cv::dnn::DNN_TARGET_MYRIAD)
#endif

#if CV_VERSION_GREATER_EQUAL(4, 2, 0)
  FF_CONST_TYPE(DNN_TARGET_CUDA, cv::dnn::DNN_TARGET_CUDA)
  FF_CONST_TYPE(DNN_TARGET_CUDA_FP16, cv::dnn::DNN_TARGET_CUDA_FP16)
#endif

#if CV_VERSION_GREATER_EQUAL(4, 5, 1)
  FF_CONST_TYPE(DNN_TARGET_HDDL, cv::dnn::DNN_TARGET_HDDL)
#endif


  Net::Init(target);

  Nan::SetMethod(target, "readNetFromTensorflow", ReadNetFromTensorflow);
  Nan::SetMethod(target, "readNetFromTensorflowAsync", ReadNetFromTensorflowAsync);
  Nan::SetMethod(target, "readNetFromCaffe", ReadNetFromCaffe);
  Nan::SetMethod(target, "readNetFromCaffeAsync", ReadNetFromCaffeAsync);
  Nan::SetMethod(target, "blobFromImage", BlobFromImage);
  Nan::SetMethod(target, "blobFromImageAsync", BlobFromImageAsync);
  Nan::SetMethod(target, "blobFromImages", BlobFromImages);
  Nan::SetMethod(target, "blobFromImagesAsync", BlobFromImagesAsync);
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
  Nan::SetMethod(target, "readNetFromDarknet", ReadNetFromDarknet);
  Nan::SetMethod(target, "readNetFromDarknetAsync", ReadNetFromDarknetAsync);
  Nan::SetMethod(target, "NMSBoxes", NMSBoxes);
#endif
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  Nan::SetMethod(target, "readNetFromONNX", ReadNetFromONNX);
  Nan::SetMethod(target, "readNetFromONNXAsync", ReadNetFromONNXAsync);
#endif
#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
  Nan::SetMethod(target, "readNet", ReadNet);
  Nan::SetMethod(target, "readNetAsync", ReadNetAsync);
#endif
};


NAN_METHOD(Dnn::ReadNetFromTensorflow) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::ReadNetFromTensorflowWorker>(), "ReadNetFromTensorflow", info);
}

NAN_METHOD(Dnn::ReadNetFromTensorflowAsync) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::ReadNetFromTensorflowWorker>(), "ReadNetFromTensorflowAsync", info);
}

NAN_METHOD(Dnn::ReadNetFromCaffe) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::ReadNetFromCaffeWorker>(), "ReadNetFromCaffe", info);
}

NAN_METHOD(Dnn::ReadNetFromCaffeAsync) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::ReadNetFromCaffeWorker>(), "ReadNetFromCaffeAsync", info);
}

NAN_METHOD(Dnn::BlobFromImage) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::BlobFromImageWorker>(true), "BlobFromImage", info);
}

NAN_METHOD(Dnn::BlobFromImageAsync) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::BlobFromImageWorker>(true), "BlobFromImageAsync", info);
}

NAN_METHOD(Dnn::BlobFromImages) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::BlobFromImageWorker>(false), "BlobFromImages", info);
}

NAN_METHOD(Dnn::BlobFromImagesAsync) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::BlobFromImageWorker>(false), "BlobFromImagesAsync", info);
}

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
NAN_METHOD(Dnn::ReadNetFromDarknet) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::ReadNetFromDarknetWorker>(), "ReadNetFromDarknet", info);
}

NAN_METHOD(Dnn::ReadNetFromDarknetAsync) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::ReadNetFromDarknetWorker>(), "ReadNetFromDarknetAsync", info);
}

NAN_METHOD(Dnn::NMSBoxes) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::NMSBoxes>(), "NMSBoxes", info);
}
#endif

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
NAN_METHOD(Dnn::ReadNetFromONNX) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::ReadNetFromONNXWorker>(), "ReadNetFromONNX", info);
}

NAN_METHOD(Dnn::ReadNetFromONNXAsync) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::ReadNetFromONNXWorker>(), "ReadNetFromONNXAsync", info);
}
#endif

#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
NAN_METHOD(Dnn::ReadNet) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::ReadNetWorker>(), "ReadNet", info);
}

NAN_METHOD(Dnn::ReadNetAsync) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::ReadNetWorker>(), "ReadNetAsync", info);
}
#endif

#endif
