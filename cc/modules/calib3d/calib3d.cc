#include "calib3d.h"

NAN_MODULE_INIT(Calib3d::Init) {
  Nan::SetMethod(target, "findHomography", FindHomography);
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
#if CV_VERSION_MINOR > 0
  Nan::SetMethod(target, "sampsonDistance", SampsonDistance);
  Nan::SetMethod(target, "sampsonDistanceAsync", SampsonDistanceAsync);
  Nan::SetMethod(target, "calibrateCamera", CalibrateCamera);
  Nan::SetMethod(target, "calibrateCameraAsync", CalibrateCameraAsync);
#endif
#if CV_VERSION_MINOR > 1
  Nan::SetMethod(target, "calibrateCameraExtended", CalibrateCameraExtended);
  Nan::SetMethod(target, "calibrateCameraExtendedAsync", CalibrateCameraExtendedAsync);
  Nan::SetMethod(target, "estimateAffine2D", EstimateAffine2D);
  Nan::SetMethod(target, "estimateAffine2DAsync", EstimateAffine2DAsync);
  Nan::SetMethod(target, "estimateAffinePartial2D", EstimateAffinePartial2D);
  Nan::SetMethod(target, "estimateAffinePartial2DAsync", EstimateAffinePartial2DAsync);
#endif
#if CV_VERSION_MINOR > 2
  Nan::SetMethod(target, "solveP3P", SolveP3P);
  Nan::SetMethod(target, "solveP3PAsync", SolveP3PAsync);
#endif
};




















































#if CV_VERSION_MINOR > 0







#endif

#if CV_VERSION_MINOR > 1












#endif

#if CV_VERSION_MINOR > 2




#endif
NAN_METHOD(Calib3d::FindHomography) {
  FF_METHOD_CONTEXT("FindHomography");

  FF_ARG_ARRAY(0, FF_ARR jsSrcPoints);
  FF_ARG_ARRAY(1, FF_ARR jsDstPoints);

  // TODO FF_ARG_UNPACK_ARRAY_INSTANCE
  Nan::TryCatch tryCatch;
  std::vector<cv::Point2d> srcPoints, dstPoints;
  Point::unpackJSPoint2Array(srcPoints, jsSrcPoints);
  Point::unpackJSPoint2Array(dstPoints, jsDstPoints);
  if (tryCatch.HasCaught()) {
    return info.GetReturnValue().Set(tryCatch.ReThrow());
  }

  // optional args
  bool hasOptArgsObj = FF_HAS_ARG(2) && info[2]->IsObject();
  FF_OBJ optArgs = hasOptArgsObj ? info[2]->ToObject() : FF_NEW_OBJ();

  FF_GET_UINT_IFDEF(optArgs, uint method, "method", 0);
  FF_GET_NUMBER_IFDEF(optArgs, double ransacReprojThreshold, "ransacReprojThreshold", 3);
  FF_GET_UINT_IFDEF(optArgs, uint maxIters, "maxIters", 2000);
  FF_GET_NUMBER_IFDEF(optArgs, double confidence, "confidence", 0.995);
  if (!hasOptArgsObj) {
    FF_ARG_UINT_IFDEF(2, method, method);
    FF_ARG_NUMBER_IFDEF(3, ransacReprojThreshold, ransacReprojThreshold);
    FF_ARG_UINT_IFDEF(4, maxIters, maxIters);
    FF_ARG_NUMBER_IFDEF(5, confidence, confidence);
  }

  FF_OBJ jsMat = FF_NEW_INSTANCE(Mat::constructor);
  FF_OBJ mask = FF_NEW_INSTANCE(Mat::constructor);
  FF_UNWRAP_MAT_AND_GET(jsMat) = cv::findHomography(srcPoints, dstPoints, method, ransacReprojThreshold, FF_UNWRAP_MAT_AND_GET(mask), maxIters, confidence);

  v8::Local<v8::Object> output = Nan::New<v8::Object>();
  Nan::Set(output, Nan::New("homography").ToLocalChecked(), jsMat);
  Nan::Set(output, Nan::New("mask").ToLocalChecked(), mask);
  info.GetReturnValue().Set(output);
}

NAN_METHOD(Calib3d::ComposeRT) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::ComposeRTWorker>(),
    "Calib3d::ComposeRT",
    info
  );
}

NAN_METHOD(Calib3d::ComposeRTAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::ComposeRTWorker>(),
    "Calib3d::ComposeRTAsync",
    info
  );
}

NAN_METHOD(Calib3d::SolvePnP) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::SolvePnPWorker>(),
    "Calib3d::SolvePnP",
    info
  );
}

NAN_METHOD(Calib3d::SolvePnPAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::SolvePnPWorker>(),
    "Calib3d::SolvePnPAsync",
    info
  );
}

NAN_METHOD(Calib3d::SolvePnPRansac) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::SolvePnPRansacWorker>(),
    "Calib3d::SolvePnPRansac",
    info
  );
}

NAN_METHOD(Calib3d::SolvePnPRansacAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::SolvePnPRansacWorker>(),
    "Calib3d::SolvePnPRansacAsync",
    info
  );
}

NAN_METHOD(Calib3d::ProjectPoints) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::ProjectPointsWorker>(),
    "Calib3d::ProjectPoints",
    info
  );
}

NAN_METHOD(Calib3d::ProjectPointsAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::ProjectPointsWorker>(),
    "Calib3d::ProjectPointsAsync",
    info
  );
}

NAN_METHOD(Calib3d::InitCameraMatrix2D) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::InitCameraMatrix2DWorker>(),
    "Calib3d::InitCameraMatrix2D",
    info
  );
}

NAN_METHOD(Calib3d::InitCameraMatrix2DAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::InitCameraMatrix2DWorker>(),
    "Calib3d::InitCameraMatrix2DAsync",
    info
  );
}

NAN_METHOD(Calib3d::StereoCalibrate) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::StereoCalibrateWorker>(),
    "Calib3d::StereoCalibrate",
    info
  );
}

NAN_METHOD(Calib3d::StereoCalibrateAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::StereoCalibrateWorker>(),
    "Calib3d::StereoCalibrateAsync",
    info
  );
}

NAN_METHOD(Calib3d::StereoRectifyUncalibrated) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::StereoRectifyUncalibratedWorker>(),
    "Calib3d::StereoRectifyUncalibrated",
    info
  );
}

NAN_METHOD(Calib3d::StereoRectifyUncalibratedAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::StereoRectifyUncalibratedWorker>(),
    "Calib3d::StereoRectifyUncalibratedAsync",
    info
  );
}

NAN_METHOD(Calib3d::FindFundamentalMat) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::FindFundamentalMatWorker>(),
    "Calib3d::FindFundamentalMat",
    info
  );
}

NAN_METHOD(Calib3d::FindFundamentalMatAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::FindFundamentalMatWorker>(),
    "Calib3d::FindFundamentalMatAsync",
    info
  );
}

NAN_METHOD(Calib3d::FindEssentialMat) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::FindEssentialMatWorker>(),
    "Calib3d::FindEssentialMat",
    info
  );
}

NAN_METHOD(Calib3d::FindEssentialMatAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::FindEssentialMatWorker>(),
    "Calib3d::FindEssentialMatAsync",
    info
  );
}

NAN_METHOD(Calib3d::RecoverPose) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::RecoverPoseWorker>(),
    "Calib3d::RecoverPose",
    info
  );
}

NAN_METHOD(Calib3d::RecoverPoseAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::RecoverPoseWorker>(),
    "Calib3d::RecoverPoseAsync",
    info
  );
}

NAN_METHOD(Calib3d::ComputeCorrespondEpilines) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::ComputeCorrespondEpilinesWorker>(),
    "Calib3d::ComputeCorrespondEpilines",
    info
  );
}

NAN_METHOD(Calib3d::ComputeCorrespondEpilinesAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::ComputeCorrespondEpilinesWorker>(),
    "Calib3d::ComputeCorrespondEpilinesAsync",
    info
  );
}

NAN_METHOD(Calib3d::GetValidDisparityROI) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::GetValidDisparityROIWorker>(),
    "Calib3d::GetValidDisparityROI",
    info
  );
}

NAN_METHOD(Calib3d::GetValidDisparityROIAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::GetValidDisparityROIWorker>(),
    "Calib3d::GetValidDisparityROIAsync",
    info
  );
}

NAN_METHOD(Calib3d::EstimateAffine3D) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::EstimateAffine3DWorker>(),
    "Calib3d::EstimateAffine3D",
    info
  );
}

NAN_METHOD(Calib3d::EstimateAffine3DAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::EstimateAffine3DWorker>(),
    "Calib3d::EstimateAffine3DAsync",
    info
  );
}

#if CV_VERSION_MINOR > 0

NAN_METHOD(Calib3d::SampsonDistance) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::SampsonDistanceWorker>(),
    "Calib3d::SampsonDistance",
    info
  );
}

NAN_METHOD(Calib3d::SampsonDistanceAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::SampsonDistanceWorker>(),
    "Calib3d::SampsonDistanceAsync",
    info
  );
}

NAN_METHOD(Calib3d::CalibrateCamera) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::CalibrateCameraWorker>(),
    "Calib3d::CalibrateCamera",
    info
  );
}

NAN_METHOD(Calib3d::CalibrateCameraAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::CalibrateCameraWorker>(),
    "Calib3d::CalibrateCameraAsync",
    info
  );
}

#endif

#if CV_VERSION_MINOR > 1

NAN_METHOD(Calib3d::CalibrateCameraExtended) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::CalibrateCameraExtendedWorker>(),
    "Calib3d::CalibrateCameraExtended",
    info
  );
}

NAN_METHOD(Calib3d::CalibrateCameraExtendedAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::CalibrateCameraExtendedWorker>(),
    "Calib3d::CalibrateCameraExtendedAsync",
    info
  );
}

NAN_METHOD(Calib3d::EstimateAffine2D) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::EstimateAffine2DWorker>(),
    "Calib3d::EstimateAffine2D",
    info
  );
}

NAN_METHOD(Calib3d::EstimateAffine2DAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::EstimateAffine2DWorker>(),
    "Calib3d::EstimateAffine2DAsync",
    info
  );
}

NAN_METHOD(Calib3d::EstimateAffinePartial2D) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::EstimateAffinePartial2DWorker>(),
    "Calib3d::EstimateAffinePartial2D",
    info
  );
}

NAN_METHOD(Calib3d::EstimateAffinePartial2DAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::EstimateAffinePartial2DWorker>(),
    "Calib3d::EstimateAffinePartial2DAsync",
    info
  );
}
#endif

#if CV_VERSION_MINOR > 2

NAN_METHOD(Calib3d::SolveP3P) {
  FF::SyncBinding(
    std::make_shared<Calib3dBindings::SolveP3PWorker>(),
    "Calib3d::SolveP3P",
    info
  );
}

NAN_METHOD(Calib3d::SolveP3PAsync) {
  FF::AsyncBinding(
    std::make_shared<Calib3dBindings::SolveP3PWorker>(),
    "Calib3d::SolveP3PAsync",
    info
  );
}

#endif