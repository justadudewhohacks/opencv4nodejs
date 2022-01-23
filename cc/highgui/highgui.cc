#include "opencv_modules.h"

#ifdef HAVE_OPENCV_HIGHGUI

#include "opencv2/core.hpp"
#include "macros.h"
#include "highgui.h"
#include "highguiBindings.h"
#include "highguiConstants.h"

NAN_MODULE_INIT(Highgui::Init) {
    HighguiConstants::Init(target);

    Nan::SetMethod(target, "setWindowProperty", setWindowProperty);
    Nan::SetMethod(target, "getWindowProperty", getWindowProperty);
    Nan::SetMethod(target, "setWindowTitle", setWindowTitle);

};

NAN_METHOD(Highgui::setWindowProperty) {
  FF::TryCatch tryCatch("Highgui::setWindowProperty");
  int prop_id;
  double prop_value;
  if (!info[0]->IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }

  if (!info[1]->IsNumber()) {
    return tryCatch.throwError("expected arg1 (prop_id) to be a number");
  }
  if (!info[2]->IsNumber()) {
    return tryCatch.throwError("expected arg2 (prop_value) to be a number");
  }
  FF::IntConverter::arg(1, &prop_id, info);
  FF::DoubleConverter::arg(2, &prop_value, info);

  cv::setWindowProperty(FF::StringConverter::unwrapUnchecked(info[0]), prop_id, prop_value);
}

NAN_METHOD(Highgui::setWindowTitle) {
  FF::TryCatch tryCatch("Highgui::setWindowTitle");
  if (!info[0]->IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }

  if (!info[1]->IsString()) {
    return tryCatch.throwError("expected arg1 to be the new window title");
  }

  cv::setWindowTitle(FF::StringConverter::unwrapUnchecked(info[0]), FF::StringConverter::unwrapUnchecked(info[1]));
}


NAN_METHOD(Highgui::getWindowProperty) {
  FF::TryCatch tryCatch("Highgui::getWindowProperty");
  int prop_id;
  double prop_value;
  if (!info[0]->IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }
  if (!info[1]->IsNumber()) {
    return tryCatch.throwError("expected arg1 (prop_id) to be a number");
  }
  FF::IntConverter::arg(1, &prop_id, info);
  info.GetReturnValue().Set(Nan::New(cv::getWindowProperty(FF::StringConverter::unwrapUnchecked(info[0]), prop_id)));
}

#endif
