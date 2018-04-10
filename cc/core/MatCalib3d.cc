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
#if CV_VERSION_MINOR > 0
  Nan::SetPrototypeMethod(ctor, "findEssentialMat", FindEssentialMat);
  Nan::SetPrototypeMethod(ctor, "findEssentialMatAsync", FindEssentialMatAsync);
  Nan::SetPrototypeMethod(ctor, "recoverPose", RecoverPose);
  Nan::SetPrototypeMethod(ctor, "recoverPoseAsync", RecoverPoseAsync);
#endif
};

NAN_METHOD(MatCalib3d::Rodrigues) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::RodriguesWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::Rodrigues",
    info
  );
}

NAN_METHOD(MatCalib3d::RodriguesAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::RodriguesWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::RodriguesAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::RQDecomp3x3) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::RQDecomp3x3Worker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::RQDecomp3x3",
    info
  );
}

NAN_METHOD(MatCalib3d::RQDecomp3x3Async) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::RQDecomp3x3Worker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::RQDecomp3x3Async",
    info
  );
}

NAN_METHOD(MatCalib3d::DecomposeProjectionMatrix) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::DecomposeProjectionMatrixWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::DecomposeProjectionMatrix",
    info
  );
}

NAN_METHOD(MatCalib3d::DecomposeProjectionMatrixAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::DecomposeProjectionMatrixWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::DecomposeProjectionMatrixAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::MatMulDeriv) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::MatMulDerivWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::MatMulDeriv",
    info
  );
}

NAN_METHOD(MatCalib3d::MatMulDerivAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::MatMulDerivWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::MatMulDerivAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::FindChessboardCorners) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::FindChessboardCornersWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::FindChessboardCorners",
    info
  );
}

NAN_METHOD(MatCalib3d::FindChessboardCornersAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::FindChessboardCornersWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::FindChessboardCornersAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::DrawChessboardCorners) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::DrawChessboardCornersWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::DrawChessboardCorners",
    info
  );
}

NAN_METHOD(MatCalib3d::DrawChessboardCornersAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::DrawChessboardCornersWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::DrawChessboardCornersAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::Find4QuadCornerSubpix) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::Find4QuadCornerSubpixWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::Find4QuadCornerSubpix",
    info
  );
}

NAN_METHOD(MatCalib3d::Find4QuadCornerSubpixAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::Find4QuadCornerSubpixWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::Find4QuadCornerSubpixAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::CalibrationMatrixValues) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::CalibrationMatrixValuesWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::CalibrationMatrixValues",
    info
  );
}

NAN_METHOD(MatCalib3d::CalibrationMatrixValuesAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::CalibrationMatrixValuesWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::CalibrationMatrixValuesAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::StereoRectify) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::StereoRectifyWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::StereoRectify",
    info
  );
}

NAN_METHOD(MatCalib3d::StereoRectifyAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::StereoRectifyWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::StereoRectifyAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::Rectify3Collinear) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::Rectify3CollinearWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::Rectify3Collinear",
    info
  );
}

NAN_METHOD(MatCalib3d::Rectify3CollinearAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::Rectify3CollinearWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::Rectify3CollinearAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::GetOptimalNewCameraMatrix) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::GetOptimalNewCameraMatrixWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::GetOptimalNewCameraMatrix",
    info
  );
}

NAN_METHOD(MatCalib3d::GetOptimalNewCameraMatrixAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::GetOptimalNewCameraMatrixWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::GetOptimalNewCameraMatrixAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::DecomposeEssentialMat) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::DecomposeEssentialMatWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::DecomposeEssentialMat",
    info
  );
}

NAN_METHOD(MatCalib3d::DecomposeEssentialMatAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::DecomposeEssentialMatWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::DecomposeEssentialMatAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::TriangulatePoints) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::TriangulatePointsWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::TriangulatePoints",
    info
  );
}

NAN_METHOD(MatCalib3d::TriangulatePointsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::TriangulatePointsWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::TriangulatePointsAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::CorrectMatches) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::CorrectMatchesWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::CorrectMatches",
    info
  );
}

NAN_METHOD(MatCalib3d::CorrectMatchesAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::CorrectMatchesWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::CorrectMatchesAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::FilterSpeckles) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::FilterSpecklesWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::FilterSpeckles",
    info
  );
}

NAN_METHOD(MatCalib3d::FilterSpecklesAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::FilterSpecklesWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::FilterSpecklesAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::ValidateDisparity) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::ValidateDisparityWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::ValidateDisparity",
    info
  );
}

NAN_METHOD(MatCalib3d::ValidateDisparityAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::ValidateDisparityWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::ValidateDisparityAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::ReprojectImageTo3D) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::ReprojectImageTo3DWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::ReprojectImageTo3D",
    info
  );
}

NAN_METHOD(MatCalib3d::ReprojectImageTo3DAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::ReprojectImageTo3DWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::ReprojectImageTo3DAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::DecomposeHomographyMat) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::DecomposeHomographyMatWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::DecomposeHomographyMat",
    info
  );
}

NAN_METHOD(MatCalib3d::DecomposeHomographyMatAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::DecomposeHomographyMatWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::DecomposeHomographyMatAsync",
    info
  );
}

#if CV_VERSION_MINOR > 0

NAN_METHOD(MatCalib3d::FindEssentialMat) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::FindEssentialMatWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::FindEssentialMat",
    info
  );
}

NAN_METHOD(MatCalib3d::FindEssentialMatAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::FindEssentialMatWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::FindEssentialMatAsync",
    info
  );
}

NAN_METHOD(MatCalib3d::RecoverPose) {
  FF::SyncBinding(
    std::make_shared<MatCalib3dBindings::RecoverPoseWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::RecoverPose",
    info
  );
}

NAN_METHOD(MatCalib3d::RecoverPoseAsync) {
  FF::AsyncBinding(
    std::make_shared<MatCalib3dBindings::RecoverPoseWorker>(Mat::Converter::unwrap(info.This())),
    "MatCalib3d::RecoverPoseAsync",
    info
  );
}

#endif
