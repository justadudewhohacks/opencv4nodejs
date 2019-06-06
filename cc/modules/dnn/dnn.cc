#include "opencv2/core.hpp"
#include "macros.h"

#if CV_VERSION_GREATER_EQUAL(3, 3, 0)

// cv 3.3+ should have dnn by default
//#ifdef HAVE_DNN

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
  FF::SyncBindingBase(
    std::make_shared<DnnBindings::ReadNetFromTensorflowWorker>(),
    "ReadNetFromTensorflow",
    info
  );
}

NAN_METHOD(Dnn::ReadNetFromTensorflowAsync) {
  FF::AsyncBindingBase(
    std::make_shared<DnnBindings::ReadNetFromTensorflowWorker>(),
    "ReadNetFromTensorflowAsync",
    info
  );
}

NAN_METHOD(Dnn::ReadNetFromCaffe) {
  FF::SyncBindingBase(
    std::make_shared<DnnBindings::ReadNetFromCaffeWorker>(),
    "ReadNetFromCaffe",
    info
  );
}

NAN_METHOD(Dnn::ReadNetFromCaffeAsync) {
  FF::AsyncBindingBase(
    std::make_shared<DnnBindings::ReadNetFromCaffeWorker>(),
    "ReadNetFromCaffeAsync",
    info
  );
}

NAN_METHOD(Dnn::BlobFromImage) {
  FF::SyncBindingBase(
    std::make_shared<DnnBindings::BlobFromImageWorker>(true),
    "BlobFromImage",
    info
  );
}

NAN_METHOD(Dnn::BlobFromImageAsync) {
  FF::AsyncBindingBase(
    std::make_shared<DnnBindings::BlobFromImageWorker>(true),
    "BlobFromImageAsync",
    info
  );
}

NAN_METHOD(Dnn::BlobFromImages) {
  FF::SyncBindingBase(
    std::make_shared<DnnBindings::BlobFromImageWorker>(false),
    "BlobFromImages",
    info
  );
}

NAN_METHOD(Dnn::BlobFromImagesAsync) {
  FF::AsyncBindingBase(
    std::make_shared<DnnBindings::BlobFromImageWorker>(false),
    "BlobFromImagesAsync",
    info
  );
}

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
NAN_METHOD(Dnn::ReadNetFromDarknet) {
  FF::SyncBindingBase(
      std::make_shared<DnnBindings::ReadNetFromDarknetWorker>(),
      "ReadNetFromDarknet",
      info);
}

NAN_METHOD(Dnn::ReadNetFromDarknetAsync) {
  FF::AsyncBindingBase(
      std::make_shared<DnnBindings::ReadNetFromDarknetWorker>(),
      "ReadNetFromDarknetAsync",
      info);
}

NAN_METHOD(Dnn::NMSBoxes) {
  FF::SyncBindingBase(
    std::make_shared<DnnBindings::NMSBoxes>(),
    "NMSBoxes",
    info
  );
}
#endif

#endif
