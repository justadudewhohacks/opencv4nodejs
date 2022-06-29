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
    Nan::SetMethod(target, "moveWindow", moveWindow);
    Nan::SetMethod(target, "namedWindow", namedWindow);
    Nan::SetMethod(target, "resizeWindow", resizeWindow);
    Nan::SetMethod(target, "startWindowThread", startWindowThread);
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
  if (FF::IntConverter::arg(1, &prop_id, info) || FF::DoubleConverter::arg(2, &prop_value, info)) {
    return tryCatch.reThrow();
  }
  cv::setWindowProperty(FF::StringConverter::unwrapUnchecked(info[0]), prop_id, prop_value);
}

// NAN_METHOD(Io::MoveWindow) {
// 	FF::TryCatch tryCatch("Io::MoveWindow");
// 	std::string winName;
// 	int x, y;
// 	if (FF::StringConverter::arg(0, &winName, info) || FF::IntConverter::arg(1, &x, info) || FF::IntConverter::arg(2, &y, info)) {
// 		return tryCatch.reThrow();
// 	}
// 	cv::moveWindow(winName, x, y);
// }

NAN_METHOD(Highgui::moveWindow) {
  FF::TryCatch tryCatch("Highgui::moveWindow");
	std::string winName;
  int x;
  int y;
  if (!info[0]->IsString()) {
    return tryCatch.throwError("expected arg0 (winName) to be the window name");
  }
  if (!info[1]->IsNumber()) {
    return tryCatch.throwError("expected arg1 (x) to be a number");
  }
  if (!info[2]->IsNumber()) {
    return tryCatch.throwError("expected arg2 (y) to be a number");
  }
  FF::StringConverter::arg(0, &winName, info);
  FF::IntConverter::arg(2, &x, info);
  FF::IntConverter::arg(3, &y, info);
  cv::moveWindow(FF::StringConverter::unwrapUnchecked(info[0]), x, y);
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

  if (!info[0]->IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }
  if (!info[1]->IsNumber()) {
    return tryCatch.throwError("expected arg1 (prop_id) to be a number");
  }
  FF::IntConverter::arg(1, &prop_id, info);
  info.GetReturnValue().Set(Nan::New(cv::getWindowProperty(FF::StringConverter::unwrapUnchecked(info[0]), prop_id)));
}

NAN_METHOD(Highgui::namedWindow) {
  FF::TryCatch tryCatch("Highgui::namedWindow");

	std::string winName;
  int flags = cv::WINDOW_AUTOSIZE;

  if (!info[0]->IsString()) {
    return tryCatch.throwError("expected arg0 (winName) to be the window name");
  }
  FF::IntConverter::optArg(1, &flags, info);
  FF::StringConverter::arg(0, &winName, info);
  cv::namedWindow(FF::StringConverter::unwrapUnchecked(info[0]), flags);
}

NAN_METHOD(Highgui::resizeWindow) {
  FF::TryCatch tryCatch("Highgui::resizeWindow");
  int width;
  int height;

  if (!info[0]->IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }

  if (!info[1]->IsNumber()) {
    return tryCatch.throwError("expected arg1 (width) to be a number");
  }

  if (!info[2]->IsNumber()) {
    return tryCatch.throwError("expected arg2 (height) to be a number");
  }

  FF::IntConverter::arg(1, &width, info);
  FF::IntConverter::arg(2, &height, info);
  cv::resizeWindow(FF::StringConverter::unwrapUnchecked(info[0]), width, height);
}

NAN_METHOD(Highgui::startWindowThread) {
  FF::TryCatch tryCatch("Highgui::startWindowThread");
  int retval = cv::startWindowThread();
  info.GetReturnValue().Set(Nan::New(retval));
}

#endif
