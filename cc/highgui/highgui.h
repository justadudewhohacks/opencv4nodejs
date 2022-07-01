#include "NativeNodeUtils.h"
#include "opencv2/highgui.hpp"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_HIGHGUI_H__
#define __FF_HIGHGUI_H__

class Highgui {
public:
  static NAN_MODULE_INIT(Init);

	static NAN_METHOD(setWindowProperty);
	static NAN_METHOD(getWindowProperty);
  static NAN_METHOD(setWindowTitle);
  static NAN_METHOD(moveWindow);
  static NAN_METHOD(namedWindow);
  static NAN_METHOD(resizeWindow);
  static NAN_METHOD(startWindowThread);
};

#endif
