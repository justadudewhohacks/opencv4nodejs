#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include "Mat.h"
#include "Point.h"

#ifndef __FF_CALIB3D_H__
#define __FF_CALIB3D_H__

class Calib3d {
public:
  static NAN_MODULE_INIT(Init);

	static NAN_METHOD(FindHomography);

	struct ComposeRTWorker;
	static NAN_METHOD(ComposeRT);
	static NAN_METHOD(ComposeRTAsync);

	struct SolvePxPWorker;
	struct SolvePnPWorker;
	static NAN_METHOD(SolvePnP);
	static NAN_METHOD(SolvePnPAsync);
	struct SolvePnPRansacWorker;
	static NAN_METHOD(SolvePnPRansac);
	static NAN_METHOD(SolvePnPRansacAsync);

	struct ProjectPointsWorker;
	static NAN_METHOD(ProjectPoints);
	static NAN_METHOD(ProjectPointsAsync);

	struct InitCameraMatrix2DWorker;
	static NAN_METHOD(InitCameraMatrix2D);
	static NAN_METHOD(InitCameraMatrix2DAsync);

	struct CalibrateCameraWorker;
	static NAN_METHOD(CalibrateCamera);
	static NAN_METHOD(CalibrateCameraAsync);

	struct StereoCalibrateWorker;
	static NAN_METHOD(StereoCalibrate);
	static NAN_METHOD(StereoCalibrateAsync);

	struct StereoRectifyUncalibratedWorker;
	static NAN_METHOD(StereoRectifyUncalibrated);
	static NAN_METHOD(StereoRectifyUncalibratedAsync);

	struct FindFundamentalMatWorker;
	static NAN_METHOD(FindFundamentalMat);
	static NAN_METHOD(FindFundamentalMatAsync);

	struct FindEssentialMatWorker;
	static NAN_METHOD(FindEssentialMat);
	static NAN_METHOD(FindEssentialMatAsync);

	struct RecoverPoseWorker;
	static NAN_METHOD(RecoverPose);
	static NAN_METHOD(RecoverPoseAsync);

	struct ComputeCorrespondEpilinesWorker;
	static NAN_METHOD(ComputeCorrespondEpilines);
	static NAN_METHOD(ComputeCorrespondEpilinesAsync);

	struct GetValidDisparityROIWorker;
	static NAN_METHOD(GetValidDisparityROI);
	static NAN_METHOD(GetValidDisparityROIAsync);

	struct EstimateAffine3DWorker;
	static NAN_METHOD(EstimateAffine3D);
	static NAN_METHOD(EstimateAffine3DAsync);

#if CV_VERSION_MINOR > 0
	struct SampsonDistanceWorker;
	static NAN_METHOD(SampsonDistance);
	static NAN_METHOD(SampsonDistanceAsync);
#endif
#if CV_VERSION_MINOR > 1
	struct CalibrateCameraExtendedWorker;
	static NAN_METHOD(CalibrateCameraExtended);
	static NAN_METHOD(CalibrateCameraExtendedAsync);

	struct EstimateAffine2DWorker;
	static NAN_METHOD(EstimateAffine2D);
	static NAN_METHOD(EstimateAffine2DAsync);

	struct EstimateAffinePartial2DWorker;
	static NAN_METHOD(EstimateAffinePartial2D);
	static NAN_METHOD(EstimateAffinePartial2DAsync);
#endif
#if CV_VERSION_MINOR > 2
	struct SolveP3PWorker;
	static NAN_METHOD(SolveP3P);
	static NAN_METHOD(SolveP3PAsync);
#endif
	// TODO convertPointsHomogeneous
};

#endif