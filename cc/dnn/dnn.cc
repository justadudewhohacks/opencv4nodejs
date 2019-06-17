#include "opencv_modules.h"

#ifdef HAVE_OPENCV_DNN

#include "opencv2/core.hpp"
#include "macros.h"
#include "dnn.h"
#include "dnnBindings.h"

NAN_MODULE_INIT(Dnn::Init) {
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
};


NAN_METHOD(Dnn::ReadNetFromTensorflow) {
  FF::executeSyncBinding(
    std::make_shared<DnnBindings::ReadNetFromTensorflowWorker>(),
    "ReadNetFromTensorflow",
    info
  );
}

NAN_METHOD(Dnn::ReadNetFromTensorflowAsync) {
  FF::executeAsyncBinding(
    std::make_shared<DnnBindings::ReadNetFromTensorflowWorker>(),
    "ReadNetFromTensorflowAsync",
    info
  );
}

NAN_METHOD(Dnn::ReadNetFromCaffe) {
  FF::executeSyncBinding(
    std::make_shared<DnnBindings::ReadNetFromCaffeWorker>(),
    "ReadNetFromCaffe",
    info
  );
}

NAN_METHOD(Dnn::ReadNetFromCaffeAsync) {
  FF::executeAsyncBinding(
    std::make_shared<DnnBindings::ReadNetFromCaffeWorker>(),
    "ReadNetFromCaffeAsync",
    info
  );
}

NAN_METHOD(Dnn::BlobFromImage) {
  FF::executeSyncBinding(
    std::make_shared<DnnBindings::BlobFromImageWorker>(true),
    "BlobFromImage",
    info
  );
}

NAN_METHOD(Dnn::BlobFromImageAsync) {
  FF::executeAsyncBinding(
    std::make_shared<DnnBindings::BlobFromImageWorker>(true),
    "BlobFromImageAsync",
    info
  );
}

NAN_METHOD(Dnn::BlobFromImages) {
  FF::executeSyncBinding(
    std::make_shared<DnnBindings::BlobFromImageWorker>(false),
    "BlobFromImages",
    info
  );
}

NAN_METHOD(Dnn::BlobFromImagesAsync) {
  FF::executeAsyncBinding(
    std::make_shared<DnnBindings::BlobFromImageWorker>(false),
    "BlobFromImagesAsync",
    info
  );
}

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
NAN_METHOD(Dnn::ReadNetFromDarknet) {
  FF::executeSyncBinding(
      std::make_shared<DnnBindings::ReadNetFromDarknetWorker>(),
      "ReadNetFromDarknet",
      info);
}

NAN_METHOD(Dnn::ReadNetFromDarknetAsync) {
  FF::executeAsyncBinding(
      std::make_shared<DnnBindings::ReadNetFromDarknetWorker>(),
      "ReadNetFromDarknetAsync",
      info);
}

NAN_METHOD(Dnn::NMSBoxes) {
  FF::executeSyncBinding(
    std::make_shared<DnnBindings::NMSBoxes>(),
    "NMSBoxes",
    info
  );
}
#endif

#endif
