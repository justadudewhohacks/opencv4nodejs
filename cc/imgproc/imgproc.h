#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "macros.h"
#include "Point.h"
#include "Size.h"
#include "Mat.h"
#include "Contour.h"
#include "Moments.h"
#include "HistAxes.h"

#ifndef __FF_IMGPROC_H__
#define __FF_IMGPROC_H__

class Imgproc {
public:
  static NAN_MODULE_INIT(Init);

  static NAN_METHOD(GetStructuringElement);
  static NAN_METHOD(GetRotationMatrix2D);
  static NAN_METHOD(GetAffineTransform);
  static NAN_METHOD(GetPerspectiveTransform);
  static NAN_METHOD(Plot1DHist);
  static NAN_METHOD(FitLine);
  static NAN_METHOD(GetTextSize);
  static NAN_METHOD(GetTextSizeAsync);
  static NAN_METHOD(ApplyColorMap);
  static NAN_METHOD(ApplyColorMapAsync);
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  static NAN_METHOD(Canny);
  static NAN_METHOD(CannyAsync);
#endif
#if CV_VERSION_LOWER_THAN(4, 0, 0)
  static NAN_METHOD(UndistortPoints);
  static NAN_METHOD(UndistortPointsAsync);
#endif
  static NAN_METHOD(GoodFeaturesToTrack);
  static NAN_METHOD(GoodFeaturesToTrackAsync);
  static NAN_METHOD(Blur);
  static NAN_METHOD(BlurAsync);
  static NAN_METHOD(GaussianBlur);
  static NAN_METHOD(GaussianBlurAsync);
  static NAN_METHOD(MedianBlur);
  static NAN_METHOD(MedianBlurAsync);
  static NAN_METHOD(Accumulate);
  static NAN_METHOD(AccumulateAsync);
  static NAN_METHOD(AccumulateProduct);
  static NAN_METHOD(AccumulateProductAsync);
  static NAN_METHOD(AccumulateSquare);
  static NAN_METHOD(AccumulateSquareAsync);
  static NAN_METHOD(AccumulateWeighted);
  static NAN_METHOD(AccumulateWeightedAsync);
  static NAN_METHOD(CalcHist);
  static NAN_METHOD(CalcHistAsync);
};

#endif
