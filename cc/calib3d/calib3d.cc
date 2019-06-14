#include "opencv_modules.h"

#ifdef HAVE_OPENCV_CALIB3D

#include "calib3d.h"
#include "calib3dConstants.h"

NAN_MODULE_INIT(Calib3d::Init) {
	Calib3dConstants::Init(target);
  Nan::SetMethod(target, "findHomography", FindHomography);
  Nan::SetMethod(target, "findHomographyAsync", FindHomographyAsync);
  Nan::SetMethod(target, "composeRT", ComposeRT);
  Nan::SetMethod(target, "composeRTAsync", ComposeRTAsync);
  Nan::SetMethod(target, "solvePnP", SolvePnP);
  Nan::SetMethod(target, "solvePnPAsync", SolvePnPAsync);
  Nan::SetMethod(target, "solvePnPRansac", SolvePnPRansac);
  Nan::SetMethod(target, "solvePnPRansacAsync", SolvePnPRansacAsync);
  Nan::SetMethod(target, "projectPoints", ProjectPoints);
  Nan::SetMethod(target, "projectPointsAsync", ProjectPointsAsync);
  Nan::SetMethod(target, "initCameraMatrix2D", InitCameraMatrix2D);
  Nan::SetMethod(target, "initCameraMatrix2DAsync", InitCameraMatrix2DAsync);
  Nan::SetMethod(target, "stereoCalibrate", StereoCalibrate);
  Nan::SetMethod(target, "stereoCalibrateAsync", StereoCalibrateAsync);
  Nan::SetMethod(target, "stereoRectifyUncalibrated", StereoRectifyUncalibrated);
  Nan::SetMethod(target, "stereoRectifyUncalibratedAsync", StereoRectifyUncalibratedAsync);
  Nan::SetMethod(target, "findFundamentalMat", FindFundamentalMat);
  Nan::SetMethod(target, "findFundamentalMatAsync", FindFundamentalMatAsync);
  Nan::SetMethod(target, "findEssentialMat", FindEssentialMat);
  Nan::SetMethod(target, "findEssentialMatAsync", FindEssentialMatAsync);
  Nan::SetMethod(target, "recoverPose", RecoverPose);
  Nan::SetMethod(target, "recoverPoseAsync", RecoverPoseAsync);
  Nan::SetMethod(target, "computeCorrespondEpilines", ComputeCorrespondEpilines);
  Nan::SetMethod(target, "computeCorrespondEpilinesAsync", ComputeCorrespondEpilinesAsync);
  Nan::SetMethod(target, "getValidDisparityROI", GetValidDisparityROI);
  Nan::SetMethod(target, "getValidDisparityROIAsync", GetValidDisparityROIAsync);
  Nan::SetMethod(target, "estimateAffine3D", EstimateAffine3D);
  Nan::SetMethod(target, "estimateAffine3DAsync", EstimateAffine3DAsync);
#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  Nan::SetMethod(target, "sampsonDistance", SampsonDistance);
  Nan::SetMethod(target, "sampsonDistanceAsync", SampsonDistanceAsync);
  Nan::SetMethod(target, "calibrateCamera", CalibrateCamera);
  Nan::SetMethod(target, "calibrateCameraAsync", CalibrateCameraAsync);
#endif
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  Nan::SetMethod(target, "calibrateCameraExtended", CalibrateCameraExtended);
  Nan::SetMethod(target, "calibrateCameraExtendedAsync", CalibrateCameraExtendedAsync);
  Nan::SetMethod(target, "estimateAffine2D", EstimateAffine2D);
  Nan::SetMethod(target, "estimateAffine2DAsync", EstimateAffine2DAsync);
  Nan::SetMethod(target, "estimateAffinePartial2D", EstimateAffinePartial2D);
  Nan::SetMethod(target, "estimateAffinePartial2DAsync", EstimateAffinePartial2DAsync);
#endif
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  Nan::SetMethod(target, "solveP3P", SolveP3P);
  Nan::SetMethod(target, "solveP3PAsync", SolveP3PAsync);
#endif
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  Nan::SetMethod(target, "undistortPoints", UndistortPoints);
  Nan::SetMethod(target, "undistortPointsAsync", UndistortPointsAsync);
#endif
};

NAN_METHOD(Calib3d::FindHomography) {
	FF::executeSyncBinding(
		std::make_shared<Calib3dBindings::FindHomographyWorker>(),
		"Calib3d::FindHomography",
		info
	);
}

NAN_METHOD(Calib3d::FindHomographyAsync) {
	FF::executeAsyncBinding(
		std::make_shared<Calib3dBindings::FindHomographyWorker>(),
		"Calib3d::FindHomographyAsync",
		info
	);
}

NAN_METHOD(Calib3d::ComposeRT) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::ComposeRTWorker>(),
    "Calib3d::ComposeRT",
    info
  );
}

NAN_METHOD(Calib3d::ComposeRTAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::ComposeRTWorker>(),
    "Calib3d::ComposeRTAsync",
    info
  );
}

NAN_METHOD(Calib3d::SolvePnP) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::SolvePnPWorker>(),
    "Calib3d::SolvePnP",
    info
  );
}

NAN_METHOD(Calib3d::SolvePnPAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::SolvePnPWorker>(),
    "Calib3d::SolvePnPAsync",
    info
  );
}

NAN_METHOD(Calib3d::SolvePnPRansac) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::SolvePnPRansacWorker>(),
    "Calib3d::SolvePnPRansac",
    info
  );
}

NAN_METHOD(Calib3d::SolvePnPRansacAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::SolvePnPRansacWorker>(),
    "Calib3d::SolvePnPRansacAsync",
    info
  );
}

NAN_METHOD(Calib3d::ProjectPoints) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::ProjectPointsWorker>(),
    "Calib3d::ProjectPoints",
    info
  );
}

NAN_METHOD(Calib3d::ProjectPointsAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::ProjectPointsWorker>(),
    "Calib3d::ProjectPointsAsync",
    info
  );
}

NAN_METHOD(Calib3d::InitCameraMatrix2D) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::InitCameraMatrix2DWorker>(),
    "Calib3d::InitCameraMatrix2D",
    info
  );
}

NAN_METHOD(Calib3d::InitCameraMatrix2DAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::InitCameraMatrix2DWorker>(),
    "Calib3d::InitCameraMatrix2DAsync",
    info
  );
}

NAN_METHOD(Calib3d::StereoCalibrate) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::StereoCalibrateWorker>(),
    "Calib3d::StereoCalibrate",
    info
  );
}

NAN_METHOD(Calib3d::StereoCalibrateAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::StereoCalibrateWorker>(),
    "Calib3d::StereoCalibrateAsync",
    info
  );
}

NAN_METHOD(Calib3d::StereoRectifyUncalibrated) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::StereoRectifyUncalibratedWorker>(),
    "Calib3d::StereoRectifyUncalibrated",
    info
  );
}

NAN_METHOD(Calib3d::StereoRectifyUncalibratedAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::StereoRectifyUncalibratedWorker>(),
    "Calib3d::StereoRectifyUncalibratedAsync",
    info
  );
}

NAN_METHOD(Calib3d::FindFundamentalMat) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::FindFundamentalMatWorker>(),
    "Calib3d::FindFundamentalMat",
    info
  );
}

NAN_METHOD(Calib3d::FindFundamentalMatAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::FindFundamentalMatWorker>(),
    "Calib3d::FindFundamentalMatAsync",
    info
  );
}

NAN_METHOD(Calib3d::FindEssentialMat) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::FindEssentialMatWorker>(),
    "Calib3d::FindEssentialMat",
    info
  );
}

NAN_METHOD(Calib3d::FindEssentialMatAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::FindEssentialMatWorker>(),
    "Calib3d::FindEssentialMatAsync",
    info
  );
}

NAN_METHOD(Calib3d::RecoverPose) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::RecoverPoseWorker>(),
    "Calib3d::RecoverPose",
    info
  );
}

NAN_METHOD(Calib3d::RecoverPoseAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::RecoverPoseWorker>(),
    "Calib3d::RecoverPoseAsync",
    info
  );
}

NAN_METHOD(Calib3d::ComputeCorrespondEpilines) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::ComputeCorrespondEpilinesWorker>(),
    "Calib3d::ComputeCorrespondEpilines",
    info
  );
}

NAN_METHOD(Calib3d::ComputeCorrespondEpilinesAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::ComputeCorrespondEpilinesWorker>(),
    "Calib3d::ComputeCorrespondEpilinesAsync",
    info
  );
}

NAN_METHOD(Calib3d::GetValidDisparityROI) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::GetValidDisparityROIWorker>(),
    "Calib3d::GetValidDisparityROI",
    info
  );
}

NAN_METHOD(Calib3d::GetValidDisparityROIAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::GetValidDisparityROIWorker>(),
    "Calib3d::GetValidDisparityROIAsync",
    info
  );
}

NAN_METHOD(Calib3d::EstimateAffine3D) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::EstimateAffine3DWorker>(),
    "Calib3d::EstimateAffine3D",
    info
  );
}

NAN_METHOD(Calib3d::EstimateAffine3DAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::EstimateAffine3DWorker>(),
    "Calib3d::EstimateAffine3DAsync",
    info
  );
}

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

NAN_METHOD(Calib3d::SampsonDistance) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::SampsonDistanceWorker>(),
    "Calib3d::SampsonDistance",
    info
  );
}

NAN_METHOD(Calib3d::SampsonDistanceAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::SampsonDistanceWorker>(),
    "Calib3d::SampsonDistanceAsync",
    info
  );
}

NAN_METHOD(Calib3d::CalibrateCamera) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::CalibrateCameraWorker>(),
    "Calib3d::CalibrateCamera",
    info
  );
}

NAN_METHOD(Calib3d::CalibrateCameraAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::CalibrateCameraWorker>(),
    "Calib3d::CalibrateCameraAsync",
    info
  );
}

#endif

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)

NAN_METHOD(Calib3d::CalibrateCameraExtended) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::CalibrateCameraExtendedWorker>(),
    "Calib3d::CalibrateCameraExtended",
    info
  );
}

NAN_METHOD(Calib3d::CalibrateCameraExtendedAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::CalibrateCameraExtendedWorker>(),
    "Calib3d::CalibrateCameraExtendedAsync",
    info
  );
}

NAN_METHOD(Calib3d::EstimateAffine2D) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::EstimateAffine2DWorker>(),
    "Calib3d::EstimateAffine2D",
    info
  );
}

NAN_METHOD(Calib3d::EstimateAffine2DAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::EstimateAffine2DWorker>(),
    "Calib3d::EstimateAffine2DAsync",
    info
  );
}

NAN_METHOD(Calib3d::EstimateAffinePartial2D) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::EstimateAffinePartial2DWorker>(),
    "Calib3d::EstimateAffinePartial2D",
    info
  );
}

NAN_METHOD(Calib3d::EstimateAffinePartial2DAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::EstimateAffinePartial2DWorker>(),
    "Calib3d::EstimateAffinePartial2DAsync",
    info
  );
}
#endif

#if CV_VERSION_GREATER_EQUAL(3, 3, 0)

NAN_METHOD(Calib3d::SolveP3P) {
  FF::executeSyncBinding(
    std::make_shared<Calib3dBindings::SolveP3PWorker>(),
    "Calib3d::SolveP3P",
    info
  );
}

NAN_METHOD(Calib3d::SolveP3PAsync) {
  FF::executeAsyncBinding(
    std::make_shared<Calib3dBindings::SolveP3PWorker>(),
    "Calib3d::SolveP3PAsync",
    info
  );
}

#endif

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
NAN_METHOD(Calib3d::UndistortPoints) {
	FF::syncBinding<Calib3dBindings::UndistortPoints>("Calib3d", "UndistortPoints", info);
}

NAN_METHOD(Calib3d::UndistortPointsAsync) {
	FF::asyncBinding<Calib3dBindings::UndistortPoints>("Calib3d", "UndistortPoints", info);
}
#endif

#endif