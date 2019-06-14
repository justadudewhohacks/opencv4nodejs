#include "macros.h"
#include <opencv2/calib3d.hpp>

#ifndef __FF_CALIB3D_CONSTANTS_H__
#define __FF_CALIB3D_CONSTANTS_H__

class Calib3dConstants {
public:
  static void Init(v8::Local<v8::Object> module);
};

#endif