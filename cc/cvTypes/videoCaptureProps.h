#include "macros.h"
#include <opencv2/highgui.hpp>

#ifndef __FF_VIDEOCAPTUREPROPS_H__
#define __FF_VIDEOCAPTUREPROPS_H__

class VideoCaptureProps {
public:
  static void Init(v8::Local<v8::Object> module);
};

#endif