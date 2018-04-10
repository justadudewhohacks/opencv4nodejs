#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "macros.h"
#include "Point.h"
#include "Size.h"
#include "Mat.h"
#include "Contour.h"
#include "Moments.h"

#ifndef __FF_IMGPROC_H__
#define __FF_IMGPROC_H__

class Imgproc {
public:
  static NAN_MODULE_INIT(Init);

  static NAN_METHOD(GetStructuringElement);
  static NAN_METHOD(GetRotationMatrix2D);
  static NAN_METHOD(GetAffineTransform);
  static NAN_METHOD(GetPerspectiveTransform);
  static NAN_METHOD(CalcHist);
  static NAN_METHOD(Plot1DHist);
  static NAN_METHOD(FitLine);
  static NAN_METHOD(GetTextSize);
  static NAN_METHOD(GetTextSizeAsync);
#if CV_VERSION_MINOR > 1
  static NAN_METHOD(Canny);
#endif
};

#endif
