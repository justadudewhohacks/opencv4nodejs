#include "Mat.h"
#include <opencv2/calib3d.hpp>

#ifndef __FF_MATCALIB3D_H__
#define __FF_MATCALIB3D_H__

class MatCalib3d : public Nan::ObjectWrap {
public:
  static void Init(v8::Local<v8::FunctionTemplate> ctor);

  static NAN_METHOD(Rodrigues);
  static NAN_METHOD(RodriguesAsync);
  static NAN_METHOD(RQDecomp3x3);
  static NAN_METHOD(RQDecomp3x3Async);
  static NAN_METHOD(DecomposeProjectionMatrix);
  static NAN_METHOD(DecomposeProjectionMatrixAsync);
  static NAN_METHOD(MatMulDeriv);
  static NAN_METHOD(MatMulDerivAsync);
  static NAN_METHOD(FindChessboardCorners);
  static NAN_METHOD(FindChessboardCornersAsync);
  static NAN_METHOD(DrawChessboardCorners);
  static NAN_METHOD(DrawChessboardCornersAsync);
  static NAN_METHOD(Find4QuadCornerSubpix);
  static NAN_METHOD(Find4QuadCornerSubpixAsync);
  static NAN_METHOD(CalibrationMatrixValues);
  static NAN_METHOD(CalibrationMatrixValuesAsync);
  static NAN_METHOD(StereoRectify);
  static NAN_METHOD(StereoRectifyAsync);
  static NAN_METHOD(Rectify3Collinear);
  static NAN_METHOD(Rectify3CollinearAsync);
  static NAN_METHOD(GetOptimalNewCameraMatrix);
  static NAN_METHOD(GetOptimalNewCameraMatrixAsync);
  static NAN_METHOD(DecomposeEssentialMat);
  static NAN_METHOD(DecomposeEssentialMatAsync);
  static NAN_METHOD(TriangulatePoints);
  static NAN_METHOD(TriangulatePointsAsync);
  static NAN_METHOD(CorrectMatches);
  static NAN_METHOD(CorrectMatchesAsync);
  static NAN_METHOD(FilterSpeckles);
  static NAN_METHOD(FilterSpecklesAsync);
  static NAN_METHOD(ValidateDisparity);
  static NAN_METHOD(ValidateDisparityAsync);
  static NAN_METHOD(ReprojectImageTo3D);
  static NAN_METHOD(ReprojectImageTo3DAsync);
  static NAN_METHOD(DecomposeHomographyMat);
  static NAN_METHOD(DecomposeHomographyMatAsync);
#if CV_VERSION_MINOR > 0
  static NAN_METHOD(FindEssentialMat);
  static NAN_METHOD(FindEssentialMatAsync);
  static NAN_METHOD(RecoverPose);
  static NAN_METHOD(RecoverPoseAsync);
#endif

};

#endif