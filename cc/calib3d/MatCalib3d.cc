#include "opencv_modules.h"

#ifdef HAVE_OPENCV_CALIB3D

#include "MatCalib3d.h"
#include "MatCalib3dBindings.h"

void MatCalib3d::Init(v8::Local<v8::FunctionTemplate> ctor) {
  Nan::SetPrototypeMethod(ctor, "rodrigues", Rodrigues);
  Nan::SetPrototypeMethod(ctor, "rodriguesAsync", RodriguesAsync);
  Nan::SetPrototypeMethod(ctor, "rqDecomp3x3", RQDecomp3x3);
  Nan::SetPrototypeMethod(ctor, "rqDecomp3x3Async", RQDecomp3x3Async);
  Nan::SetPrototypeMethod(ctor, "decomposeProjectionMatrix", DecomposeProjectionMatrix);
  Nan::SetPrototypeMethod(ctor, "decomposeProjectionMatrixAsync", DecomposeProjectionMatrixAsync);
  Nan::SetPrototypeMethod(ctor, "matMulDeriv", MatMulDeriv);
  Nan::SetPrototypeMethod(ctor, "matMulDerivAsync", MatMulDerivAsync);
  Nan::SetPrototypeMethod(ctor, "findChessboardCorners", FindChessboardCorners);
  Nan::SetPrototypeMethod(ctor, "findChessboardCornersAsync", FindChessboardCornersAsync);
  Nan::SetPrototypeMethod(ctor, "drawChessboardCorners", DrawChessboardCorners);
  Nan::SetPrototypeMethod(ctor, "drawChessboardCornersAsync", DrawChessboardCornersAsync);
  Nan::SetPrototypeMethod(ctor, "find4QuadCornerSubpix", Find4QuadCornerSubpix);
  Nan::SetPrototypeMethod(ctor, "find4QuadCornerSubpixAsync", Find4QuadCornerSubpixAsync);
  Nan::SetPrototypeMethod(ctor, "calibrationMatrixValues", CalibrationMatrixValues);
  Nan::SetPrototypeMethod(ctor, "calibrationMatrixValuesAsync", CalibrationMatrixValuesAsync);
  Nan::SetPrototypeMethod(ctor, "stereoRectify", StereoRectify);
  Nan::SetPrototypeMethod(ctor, "stereoRectifyAsync", StereoRectifyAsync);
  Nan::SetPrototypeMethod(ctor, "rectify3Collinear", Rectify3Collinear);
  Nan::SetPrototypeMethod(ctor, "rectify3CollinearAsync", Rectify3CollinearAsync);
  Nan::SetPrototypeMethod(ctor, "getOptimalNewCameraMatrix", GetOptimalNewCameraMatrix);
  Nan::SetPrototypeMethod(ctor, "getOptimalNewCameraMatrixAsync", GetOptimalNewCameraMatrixAsync);
  Nan::SetPrototypeMethod(ctor, "decomposeEssentialMat", DecomposeEssentialMat);
  Nan::SetPrototypeMethod(ctor, "decomposeEssentialMatAsync", DecomposeEssentialMatAsync);
  Nan::SetPrototypeMethod(ctor, "triangulatePoints", TriangulatePoints);
  Nan::SetPrototypeMethod(ctor, "triangulatePointsAsync", TriangulatePointsAsync);
  Nan::SetPrototypeMethod(ctor, "correctMatches", CorrectMatches);
  Nan::SetPrototypeMethod(ctor, "correctMatchesAsync", CorrectMatchesAsync);
  Nan::SetPrototypeMethod(ctor, "filterSpeckles", FilterSpeckles);
  Nan::SetPrototypeMethod(ctor, "filterSpecklesAsync", FilterSpecklesAsync);
  Nan::SetPrototypeMethod(ctor, "validateDisparity", ValidateDisparity);
  Nan::SetPrototypeMethod(ctor, "validateDisparityAsync", ValidateDisparityAsync);
  Nan::SetPrototypeMethod(ctor, "reprojectImageTo3D", ReprojectImageTo3D);
  Nan::SetPrototypeMethod(ctor, "reprojectImageTo3DAsync", ReprojectImageTo3DAsync);
  Nan::SetPrototypeMethod(ctor, "decomposeHomographyMat", DecomposeHomographyMat);
  Nan::SetPrototypeMethod(ctor, "decomposeHomographyMatAsync", DecomposeHomographyMatAsync);
#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  Nan::SetPrototypeMethod(ctor, "findEssentialMat", FindEssentialMat);
  Nan::SetPrototypeMethod(ctor, "findEssentialMatAsync", FindEssentialMatAsync);
  Nan::SetPrototypeMethod(ctor, "recoverPose", RecoverPose);
  Nan::SetPrototypeMethod(ctor, "recoverPoseAsync", RecoverPoseAsync);
#endif
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  Nan::SetPrototypeMethod(ctor, "undistort", Undistort);
  Nan::SetPrototypeMethod(ctor, "undistortAsync", UndistortAsync);
#endif
};

NAN_METHOD(MatCalib3d::Rodrigues) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::RodriguesWorker>(Mat::unwrapSelf(info)),
    "Mat::Rodrigues",
    info
  );
}

NAN_METHOD(MatCalib3d::RodriguesAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::RodriguesWorker>(Mat::unwrapSelf(info)),
    "Mat::RodriguesAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::RQDecomp3x3) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::RQDecomp3x3Worker>(Mat::unwrapSelf(info)),
    "Mat::RQDecomp3x3",
    info
  );
}

NAN_METHOD(MatCalib3d::RQDecomp3x3Async) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::RQDecomp3x3Worker>(Mat::unwrapSelf(info)),
    "Mat::RQDecomp3x3Async",
    info
  );
}

NAN_METHOD(MatCalib3d::DecomposeProjectionMatrix) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::DecomposeProjectionMatrixWorker>(Mat::unwrapSelf(info)),
    "Mat::DecomposeProjectionMatrix",
    info
  );
}

NAN_METHOD(MatCalib3d::DecomposeProjectionMatrixAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::DecomposeProjectionMatrixWorker>(Mat::unwrapSelf(info)),
    "Mat::DecomposeProjectionMatrixAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::MatMulDeriv) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::MatMulDerivWorker>(Mat::unwrapSelf(info)),
    "Mat::MatMulDeriv",
    info
  );
}

NAN_METHOD(MatCalib3d::MatMulDerivAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::MatMulDerivWorker>(Mat::unwrapSelf(info)),
    "Mat::MatMulDerivAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::FindChessboardCorners) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::FindChessboardCornersWorker>(Mat::unwrapSelf(info)),
    "Mat::FindChessboardCorners",
    info
  );
}

NAN_METHOD(MatCalib3d::FindChessboardCornersAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::FindChessboardCornersWorker>(Mat::unwrapSelf(info)),
    "Mat::FindChessboardCornersAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::DrawChessboardCorners) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::DrawChessboardCornersWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawChessboardCorners",
    info
  );
}

NAN_METHOD(MatCalib3d::DrawChessboardCornersAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::DrawChessboardCornersWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawChessboardCornersAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::Find4QuadCornerSubpix) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::Find4QuadCornerSubpixWorker>(Mat::unwrapSelf(info)),
    "Mat::Find4QuadCornerSubpix",
    info
  );
}

NAN_METHOD(MatCalib3d::Find4QuadCornerSubpixAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::Find4QuadCornerSubpixWorker>(Mat::unwrapSelf(info)),
    "Mat::Find4QuadCornerSubpixAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::CalibrationMatrixValues) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::CalibrationMatrixValuesWorker>(Mat::unwrapSelf(info)),
    "Mat::CalibrationMatrixValues",
    info
  );
}

NAN_METHOD(MatCalib3d::CalibrationMatrixValuesAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::CalibrationMatrixValuesWorker>(Mat::unwrapSelf(info)),
    "Mat::CalibrationMatrixValuesAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::StereoRectify) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::StereoRectifyWorker>(Mat::unwrapSelf(info)),
    "Mat::StereoRectify",
    info
  );
}

NAN_METHOD(MatCalib3d::StereoRectifyAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::StereoRectifyWorker>(Mat::unwrapSelf(info)),
    "Mat::StereoRectifyAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::Rectify3Collinear) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::Rectify3CollinearWorker>(Mat::unwrapSelf(info)),
    "Mat::Rectify3Collinear",
    info
  );
}

NAN_METHOD(MatCalib3d::Rectify3CollinearAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::Rectify3CollinearWorker>(Mat::unwrapSelf(info)),
    "Mat::Rectify3CollinearAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::GetOptimalNewCameraMatrix) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::GetOptimalNewCameraMatrixWorker>(Mat::unwrapSelf(info)),
    "Mat::GetOptimalNewCameraMatrix",
    info
  );
}

NAN_METHOD(MatCalib3d::GetOptimalNewCameraMatrixAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::GetOptimalNewCameraMatrixWorker>(Mat::unwrapSelf(info)),
    "Mat::GetOptimalNewCameraMatrixAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::DecomposeEssentialMat) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::DecomposeEssentialMatWorker>(Mat::unwrapSelf(info)),
    "Mat::DecomposeEssentialMat",
    info
  );
}

NAN_METHOD(MatCalib3d::DecomposeEssentialMatAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::DecomposeEssentialMatWorker>(Mat::unwrapSelf(info)),
    "Mat::DecomposeEssentialMatAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::TriangulatePoints) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::TriangulatePointsWorker>(Mat::unwrapSelf(info)),
    "Mat::TriangulatePoints",
    info
  );
}

NAN_METHOD(MatCalib3d::TriangulatePointsAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::TriangulatePointsWorker>(Mat::unwrapSelf(info)),
    "Mat::TriangulatePointsAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::CorrectMatches) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::CorrectMatchesWorker>(Mat::unwrapSelf(info)),
    "Mat::CorrectMatches",
    info
  );
}

NAN_METHOD(MatCalib3d::CorrectMatchesAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::CorrectMatchesWorker>(Mat::unwrapSelf(info)),
    "Mat::CorrectMatchesAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::FilterSpeckles) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::FilterSpecklesWorker>(Mat::unwrapSelf(info)),
    "Mat::FilterSpeckles",
    info
  );
}

NAN_METHOD(MatCalib3d::FilterSpecklesAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::FilterSpecklesWorker>(Mat::unwrapSelf(info)),
    "Mat::FilterSpecklesAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::ValidateDisparity) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::ValidateDisparityWorker>(Mat::unwrapSelf(info)),
    "Mat::ValidateDisparity",
    info
  );
}

NAN_METHOD(MatCalib3d::ValidateDisparityAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::ValidateDisparityWorker>(Mat::unwrapSelf(info)),
    "Mat::ValidateDisparityAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::ReprojectImageTo3D) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::ReprojectImageTo3DWorker>(Mat::unwrapSelf(info)),
    "Mat::ReprojectImageTo3D",
    info
  );
}

NAN_METHOD(MatCalib3d::ReprojectImageTo3DAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::ReprojectImageTo3DWorker>(Mat::unwrapSelf(info)),
    "Mat::ReprojectImageTo3DAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::DecomposeHomographyMat) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::DecomposeHomographyMatWorker>(Mat::unwrapSelf(info)),
    "Mat::DecomposeHomographyMat",
    info
  );
}

NAN_METHOD(MatCalib3d::DecomposeHomographyMatAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::DecomposeHomographyMatWorker>(Mat::unwrapSelf(info)),
    "Mat::DecomposeHomographyMatAsync",
    info
  );
}

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

NAN_METHOD(MatCalib3d::FindEssentialMat) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::FindEssentialMatWorker>(Mat::unwrapSelf(info)),
    "Mat::FindEssentialMat",
    info
  );
}

NAN_METHOD(MatCalib3d::FindEssentialMatAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::FindEssentialMatWorker>(Mat::unwrapSelf(info)),
    "Mat::FindEssentialMatAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::RecoverPose) {
  FF::executeSyncBinding(
    std::make_shared<MatCalib3dBindings::RecoverPoseWorker>(Mat::unwrapSelf(info)),
    "Mat::RecoverPose",
    info
  );
}

NAN_METHOD(MatCalib3d::RecoverPoseAsync) {
  FF::executeAsyncBinding(
    std::make_shared<MatCalib3dBindings::RecoverPoseWorker>(Mat::unwrapSelf(info)),
    "Mat::RecoverPoseAsync",
    info
  );
}

#endif

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
NAN_METHOD(MatCalib3d::Undistort) {
	Mat::syncBinding<MatCalib3dBindings::Undistort>("Undistort", info);
}

NAN_METHOD(MatCalib3d::UndistortAsync) {
	Mat::asyncBinding<MatCalib3dBindings::Undistort>("Undistort", info);
}
#endif

#endif