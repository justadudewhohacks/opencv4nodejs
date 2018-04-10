#include "photo.h"
#include "photoBindings.h"

NAN_MODULE_INIT(Photo::Init) {
  Nan::SetMethod(target, "fastNlMeansDenoisingColored", FastNlMeansDenoisingColored);
  Nan::SetMethod(target, "inpaint", Inpaint);
  Nan::SetMethod(target, "inpaintAsync", InpaintAsync);
};

NAN_METHOD(Photo::FastNlMeansDenoisingColored) {
  FF_METHOD_CONTEXT("Photo::FastNlMeansDenoisingColored");

  FF_ARG_INSTANCE(0, cv::Mat src, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

  // optional args
  bool hasOptArgsObj = FF_HAS_ARG(1) && info[1]->IsObject();
  FF_OBJ optArgs = hasOptArgsObj ? info[1]->ToObject() : FF_NEW_OBJ();

  FF_GET_NUMBER_IFDEF(optArgs, double h, "h", 3.0);
  FF_GET_NUMBER_IFDEF(optArgs, double hColor, "hColor", 3.0);
  FF_GET_UINT_IFDEF(optArgs, uint templateWindowSize, "templateWindowSize", 7);
  FF_GET_UINT_IFDEF(optArgs, uint searchWindowSize, "searchWindowSize", 21);
  if (!hasOptArgsObj) {
    FF_ARG_NUMBER_IFDEF(1, h, h);
    FF_ARG_NUMBER_IFDEF(2, hColor, hColor);
    FF_ARG_UINT_IFDEF(3, templateWindowSize, templateWindowSize);
    FF_ARG_UINT_IFDEF(4, searchWindowSize, searchWindowSize);
  }

  FF_OBJ jsDst = FF_NEW_INSTANCE(Mat::constructor);
  cv::fastNlMeansDenoisingColored(src, FF_UNWRAP_MAT_AND_GET(jsDst), h, hColor, templateWindowSize, searchWindowSize);
  FF_RETURN(jsDst);
}

NAN_METHOD(Photo::Inpaint) {
  FF::SyncBinding(
    std::make_shared<PhotoBindings::InpaintWorker>(),
    "Photo::Inpaint",
    info
  );
}

NAN_METHOD(Photo::InpaintAsync) {
  FF::AsyncBinding(
    std::make_shared<PhotoBindings::InpaintWorker>(),
    "Photo::InpaintAsync",
    info
  );
}
