#include <nan.h>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include "macros.h"
#include "Mat.h"
#include "Point.h"

#ifndef __FF_CALIB3D_H__
#define __FF_CALIB3D_H__

class Calib3d {
public:
  static NAN_MODULE_INIT(Init);

	static NAN_METHOD(FindHomography);
};

#endif