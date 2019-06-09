#include "calib3dBindings.h"

#ifndef __FF_CALIB3D_H__
#define __FF_CALIB3D_H__

class Calib3d {
public:
  static NAN_MODULE_INIT(Init);

  static NAN_METHOD(FindHomography);
  static NAN_METHOD(FindHomographyAsync);
  static NAN_METHOD(ComposeRT);
  static NAN_METHOD(ComposeRTAsync);
  static NAN_METHOD(SolvePnP);
  static NAN_METHOD(SolvePnPAsync);
  static NAN_METHOD(SolvePnPRansac);
  static NAN_METHOD(SolvePnPRansacAsync);
  static NAN_METHOD(ProjectPoints);
  static NAN_METHOD(ProjectPointsAsync);
  static NAN_METHOD(InitCameraMatrix2D);
  static NAN_METHOD(InitCameraMatrix2DAsync);
  static NAN_METHOD(StereoCalibrate);
  static NAN_METHOD(StereoCalibrateAsync);
  static NAN_METHOD(StereoRectifyUncalibrated);
  static NAN_METHOD(StereoRectifyUncalibratedAsync);
  static NAN_METHOD(FindFundamentalMat);
  static NAN_METHOD(FindFundamentalMatAsync);
  static NAN_METHOD(FindEssentialMat);
  static NAN_METHOD(FindEssentialMatAsync);
  static NAN_METHOD(RecoverPose);
  static NAN_METHOD(RecoverPoseAsync);
  static NAN_METHOD(ComputeCorrespondEpilines);
  static NAN_METHOD(ComputeCorrespondEpilinesAsync);
  static NAN_METHOD(GetValidDisparityROI);
  static NAN_METHOD(GetValidDisparityROIAsync);
  static NAN_METHOD(EstimateAffine3D);
  static NAN_METHOD(EstimateAffine3DAsync);
#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  static NAN_METHOD(SampsonDistance);
  static NAN_METHOD(SampsonDistanceAsync);
  static NAN_METHOD(CalibrateCamera);
  static NAN_METHOD(CalibrateCameraAsync);
#endif
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  static NAN_METHOD(CalibrateCameraExtended);
  static NAN_METHOD(CalibrateCameraExtendedAsync);
  static NAN_METHOD(EstimateAffine2D);
  static NAN_METHOD(EstimateAffine2DAsync);
  static NAN_METHOD(EstimateAffinePartial2D);
  static NAN_METHOD(EstimateAffinePartial2DAsync);
#endif
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  static NAN_METHOD(SolveP3P);
  static NAN_METHOD(SolveP3PAsync);
#endif
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  static NAN_METHOD(UndistortPoints);
  static NAN_METHOD(UndistortPointsAsync);
#endif
};

#endif