#include "Mat.h"
#include <opencv2/calib3d.hpp>

#ifndef __FF_MATCALIB3D_H__
#define __FF_MATCALIB3D_H__

class MatCalib3d : public Nan::ObjectWrap {
public:
	static void Init(v8::Local<v8::FunctionTemplate> ctor);

	struct RodriguesWorker;
	static NAN_METHOD(Rodrigues);
	static NAN_METHOD(RodriguesAsync);

	struct RQDecomp3x3Worker;
	static NAN_METHOD(RQDecomp3x3);
	static NAN_METHOD(RQDecomp3x3Async);

	struct DecomposeProjectionMatrixWorker;
	static NAN_METHOD(DecomposeProjectionMatrix);
	static NAN_METHOD(DecomposeProjectionMatrixAsync);

	struct MatMulDerivWorker;
	static NAN_METHOD(MatMulDeriv);
	static NAN_METHOD(MatMulDerivAsync);

	struct FindChessboardCornersWorker;
	static NAN_METHOD(FindChessboardCorners);
	static NAN_METHOD(FindChessboardCornersAsync);

	// TODO findCirclesGrid

	struct DrawChessboardCornersWorker;
	static NAN_METHOD(DrawChessboardCorners);
	static NAN_METHOD(DrawChessboardCornersAsync);

	struct Find4QuadCornerSubpixWorker;
	static NAN_METHOD(Find4QuadCornerSubpix);
	static NAN_METHOD(Find4QuadCornerSubpixAsync);

	struct CalibrationMatrixValuesWorker;
	static NAN_METHOD(CalibrationMatrixValues);
	static NAN_METHOD(CalibrationMatrixValuesAsync);

	struct StereoRectifyWorker;
	static NAN_METHOD(StereoRectify);
	static NAN_METHOD(StereoRectifyAsync);

	struct Rectify3CollinearWorker;
	static NAN_METHOD(Rectify3Collinear);
	static NAN_METHOD(Rectify3CollinearAsync);

	struct GetOptimalNewCameraMatrixWorker;
	static NAN_METHOD(GetOptimalNewCameraMatrix);
	static NAN_METHOD(GetOptimalNewCameraMatrixAsync);

	struct DecomposeEssentialMatWorker;
	static NAN_METHOD(DecomposeEssentialMat);
	static NAN_METHOD(DecomposeEssentialMatAsync);

	struct TriangulatePointsWorker;
	static NAN_METHOD(TriangulatePoints);
	static NAN_METHOD(TriangulatePointsAsync);

	struct CorrectMatchesWorker;
	static NAN_METHOD(CorrectMatches);
	static NAN_METHOD(CorrectMatchesAsync);

	struct FilterSpecklesWorker;
	static NAN_METHOD(FilterSpeckles);
	static NAN_METHOD(FilterSpecklesAsync);

	struct ValidateDisparityWorker;
	static NAN_METHOD(ValidateDisparity);
	static NAN_METHOD(ValidateDisparityAsync);

	struct ReprojectImageTo3DWorker;
	static NAN_METHOD(ReprojectImageTo3D);
	static NAN_METHOD(ReprojectImageTo3DAsync);

	struct DecomposeHomographyMatWorker;
	static NAN_METHOD(DecomposeHomographyMat);
	static NAN_METHOD(DecomposeHomographyMatAsync);

#if CV_VERSION_MINOR > 0
	struct FindEssentialMatWorker;
	static NAN_METHOD(FindEssentialMat);
	static NAN_METHOD(FindEssentialMatAsync);

	struct RecoverPoseWorker;
	static NAN_METHOD(RecoverPose);
	static NAN_METHOD(RecoverPoseAsync);
#endif
};

#endif