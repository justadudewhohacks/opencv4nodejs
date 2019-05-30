#include "MatImgproc.h"
#include "MatImgprocBindings.h"

void MatImgproc::Init(v8::Local<v8::FunctionTemplate> ctor) {
  Nan::SetPrototypeMethod(ctor, "rescale", Rescale);
  Nan::SetPrototypeMethod(ctor, "rescaleAsync", RescaleAsync);
  Nan::SetPrototypeMethod(ctor, "resize", Resize);
  Nan::SetPrototypeMethod(ctor, "resizeAsync", ResizeAsync);
  Nan::SetPrototypeMethod(ctor, "resizeToMax", ResizeToMax);
  Nan::SetPrototypeMethod(ctor, "resizeToMaxAsync", ResizeToMaxAsync);
  Nan::SetPrototypeMethod(ctor, "cvtColor", CvtColor);
  Nan::SetPrototypeMethod(ctor, "cvtColorAsync", CvtColorAsync);
  Nan::SetPrototypeMethod(ctor, "bgrToGray", BgrToGray);
  Nan::SetPrototypeMethod(ctor, "bgrToGrayAsync", BgrToGrayAsync);
  Nan::SetPrototypeMethod(ctor, "threshold", Threshold);
  Nan::SetPrototypeMethod(ctor, "thresholdAsync", ThresholdAsync);
  Nan::SetPrototypeMethod(ctor, "adaptiveThreshold", AdaptiveThreshold);
  Nan::SetPrototypeMethod(ctor, "adaptiveThresholdAsync", AdaptiveThresholdAsync);
  Nan::SetPrototypeMethod(ctor, "inRange", InRange);
  Nan::SetPrototypeMethod(ctor, "inRangeAsync", InRangeAsync);
  Nan::SetPrototypeMethod(ctor, "warpAffine", WarpAffine);
  Nan::SetPrototypeMethod(ctor, "warpAffineAsync", WarpAffineAsync);
  Nan::SetPrototypeMethod(ctor, "warpPerspective", WarpPerspective);
  Nan::SetPrototypeMethod(ctor, "warpPerspectiveAsync", WarpPerspectiveAsync);
  Nan::SetPrototypeMethod(ctor, "dilate", Dilate);
  Nan::SetPrototypeMethod(ctor, "dilateAsync", DilateAsync);
  Nan::SetPrototypeMethod(ctor, "erode", Erode);
  Nan::SetPrototypeMethod(ctor, "erodeAsync", ErodeAsync);
  Nan::SetPrototypeMethod(ctor, "morphologyEx", MorphologyEx);
  Nan::SetPrototypeMethod(ctor, "morphologyExAsync", MorphologyExAsync);
  Nan::SetPrototypeMethod(ctor, "distanceTransform", DistanceTransform);
  Nan::SetPrototypeMethod(ctor, "distanceTransformAsync", DistanceTransformAsync);
  Nan::SetPrototypeMethod(ctor, "distanceTransformWithLabels", DistanceTransformWithLabels);
  Nan::SetPrototypeMethod(ctor, "distanceTransformWithLabelsAsync", DistanceTransformWithLabelsAsync);
  Nan::SetPrototypeMethod(ctor, "blur", Blur);
  Nan::SetPrototypeMethod(ctor, "blurAsync", BlurAsync);
  Nan::SetPrototypeMethod(ctor, "gaussianBlur", GaussianBlur);
  Nan::SetPrototypeMethod(ctor, "gaussianBlurAsync", GaussianBlurAsync);
  Nan::SetPrototypeMethod(ctor, "medianBlur", MedianBlur);
  Nan::SetPrototypeMethod(ctor, "medianBlurAsync", MedianBlurAsync);
  Nan::SetPrototypeMethod(ctor, "connectedComponents", ConnectedComponents);
  Nan::SetPrototypeMethod(ctor, "connectedComponentsAsync", ConnectedComponentsAsync);
  Nan::SetPrototypeMethod(ctor, "connectedComponentsWithStats", ConnectedComponentsWithStats);
  Nan::SetPrototypeMethod(ctor, "connectedComponentsWithStatsAsync", ConnectedComponentsWithStatsAsync);
  Nan::SetPrototypeMethod(ctor, "grabCut", GrabCut);
  Nan::SetPrototypeMethod(ctor, "grabCutAsync", GrabCutAsync);
  Nan::SetPrototypeMethod(ctor, "watershed", Watershed);
  Nan::SetPrototypeMethod(ctor, "watershedAsync", WatershedAsync);
  Nan::SetPrototypeMethod(ctor, "moments", _Moments);
  Nan::SetPrototypeMethod(ctor, "momentsAsync", _MomentsAsync);
  Nan::SetPrototypeMethod(ctor, "findContours", FindContours);
  Nan::SetPrototypeMethod(ctor, "findContoursAsync", FindContoursAsync);
  Nan::SetPrototypeMethod(ctor, "drawContours", DrawContours);
  Nan::SetPrototypeMethod(ctor, "drawContoursAsync", DrawContoursAsync);
  Nan::SetPrototypeMethod(ctor, "drawLine", DrawLine);
  Nan::SetPrototypeMethod(ctor, "drawArrowedLine", DrawArrowedLine);
  Nan::SetPrototypeMethod(ctor, "drawCircle", DrawCircle);
  Nan::SetPrototypeMethod(ctor, "drawRectangle", DrawRectangle);
  Nan::SetPrototypeMethod(ctor, "drawEllipse", DrawEllipse);
  Nan::SetPrototypeMethod(ctor, "drawPolylines", DrawPolylines);
  Nan::SetPrototypeMethod(ctor, "drawFillPoly", DrawFillPoly);
  Nan::SetPrototypeMethod(ctor, "drawFillConvexPoly", DrawFillConvexPoly);
  Nan::SetPrototypeMethod(ctor, "putText", PutText);
  Nan::SetPrototypeMethod(ctor, "matchTemplate", MatchTemplate);
  Nan::SetPrototypeMethod(ctor, "matchTemplateAsync", MatchTemplateAsync);
  Nan::SetPrototypeMethod(ctor, "canny", Canny);
  Nan::SetPrototypeMethod(ctor, "cannyAsync", CannyAsync);
  Nan::SetPrototypeMethod(ctor, "sobel", Sobel);
  Nan::SetPrototypeMethod(ctor, "sobelAsync", SobelAsync);
  Nan::SetPrototypeMethod(ctor, "scharr", Scharr);
  Nan::SetPrototypeMethod(ctor, "scharrAsync", ScharrAsync);
  Nan::SetPrototypeMethod(ctor, "laplacian", Laplacian);
  Nan::SetPrototypeMethod(ctor, "laplacianAsync", LaplacianAsync);
  Nan::SetPrototypeMethod(ctor, "pyrDown", PyrDown);
  Nan::SetPrototypeMethod(ctor, "pyrDownAsync", PyrDownAsync);
  Nan::SetPrototypeMethod(ctor, "pyrUp", PyrUp);
  Nan::SetPrototypeMethod(ctor, "pyrUpAsync", PyrUpAsync);
  Nan::SetPrototypeMethod(ctor, "buildPyramid", BuildPyramid);
  Nan::SetPrototypeMethod(ctor, "buildPyramidAsync", BuildPyramidAsync);
  Nan::SetPrototypeMethod(ctor, "houghLines", HoughLines);
  Nan::SetPrototypeMethod(ctor, "houghLinesAsync", HoughLinesAsync);
  Nan::SetPrototypeMethod(ctor, "houghLinesP", HoughLinesP);
  Nan::SetPrototypeMethod(ctor, "houghLinesPAsync", HoughLinesPAsync);
  Nan::SetPrototypeMethod(ctor, "houghCircles", HoughCircles);
  Nan::SetPrototypeMethod(ctor, "houghCirclesAsync", HoughCirclesAsync);
  Nan::SetPrototypeMethod(ctor, "equalizeHist", EqualizeHist);
  Nan::SetPrototypeMethod(ctor, "equalizeHistAsync", EqualizeHistAsync);
  Nan::SetPrototypeMethod(ctor, "compareHist", CompareHist);
  Nan::SetPrototypeMethod(ctor, "compareHistAsync", CompareHistAsync);
  Nan::SetPrototypeMethod(ctor, "floodFill", FloodFill);
  Nan::SetPrototypeMethod(ctor, "floodFillAsync", FloodFillAsync);
  Nan::SetPrototypeMethod(ctor, "bilateralFilter", BilateralFilter);
  Nan::SetPrototypeMethod(ctor, "bilateralFilterAsync", BilateralFilterAsync);
  Nan::SetPrototypeMethod(ctor, "boxFilter", BoxFilter);
  Nan::SetPrototypeMethod(ctor, "boxFilterAsync", BoxFilterAsync);
  Nan::SetPrototypeMethod(ctor, "sqrBoxFilter", SqrBoxFilter);
  Nan::SetPrototypeMethod(ctor, "sqrBoxFilterAsync", SqrBoxFilterAsync);
  Nan::SetPrototypeMethod(ctor, "filter2D", Filter2D);
  Nan::SetPrototypeMethod(ctor, "filter2DAsync", Filter2DAsync);
  Nan::SetPrototypeMethod(ctor, "sepFilter2D", SepFilter2D);
  Nan::SetPrototypeMethod(ctor, "sepFilter2DAsync", SepFilter2DAsync);
  Nan::SetPrototypeMethod(ctor, "cornerHarris", CornerHarris);
  Nan::SetPrototypeMethod(ctor, "cornerHarrisAsync", CornerHarrisAsync);
  Nan::SetPrototypeMethod(ctor, "cornerSubPix", CornerSubPix);
  Nan::SetPrototypeMethod(ctor, "cornerSubPixAsync", CornerSubPixAsync);
  Nan::SetPrototypeMethod(ctor, "cornerMinEigenVal", CornerMinEigenVal);
  Nan::SetPrototypeMethod(ctor, "cornerMinEigenValAsync", CornerMinEigenValAsync);
  Nan::SetPrototypeMethod(ctor, "cornerEigenValsAndVecs", CornerEigenValsAndVecs);
  Nan::SetPrototypeMethod(ctor, "cornerEigenValsAndVecsAsync", CornerEigenValsAndVecsAsync);
  Nan::SetPrototypeMethod(ctor, "integral", Integral);
  Nan::SetPrototypeMethod(ctor, "integralAsync", IntegralAsync);
  Nan::SetPrototypeMethod(ctor, "undistort", Undistort);
  Nan::SetPrototypeMethod(ctor, "undistortAsync", UndistortAsync);
};

NAN_METHOD(MatImgproc::DrawContours) {
	FF::SyncBinding(
		std::make_shared<MatImgprocBindings::DrawContoursWorker>(Mat::unwrapSelf(info)),
		"Mat::DrawContours",
		info
	);
}

NAN_METHOD(MatImgproc::DrawContoursAsync) {
	FF::AsyncBinding(
		std::make_shared<MatImgprocBindings::DrawContoursWorker>(Mat::unwrapSelf(info)),
		"Mat::DrawContoursAsync",
		info
	);
}

NAN_METHOD(MatImgproc::Rescale) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::RescaleWorker>(Mat::unwrapSelf(info)),
    "Mat::Rescale",
    info
  );
}

NAN_METHOD(MatImgproc::RescaleAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::RescaleWorker>(Mat::unwrapSelf(info)),
    "Mat::RescaleAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Resize) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ResizeWorker>(Mat::unwrapSelf(info)),
    "Mat::Resize",
    info
  );
}

NAN_METHOD(MatImgproc::ResizeAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ResizeWorker>(Mat::unwrapSelf(info)),
    "Mat::ResizeAsync",
    info
  );
}

NAN_METHOD(MatImgproc::ResizeToMax) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ResizeToMaxWorker>(Mat::unwrapSelf(info)),
    "Mat::ResizeToMax",
    info
  );
}

NAN_METHOD(MatImgproc::ResizeToMaxAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ResizeToMaxWorker>(Mat::unwrapSelf(info)),
    "Mat::ResizeToMaxAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Threshold) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ThresholdWorker>(Mat::unwrapSelf(info)),
    "Mat::Threshold",
    info
  );
}

NAN_METHOD(MatImgproc::ThresholdAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ThresholdWorker>(Mat::unwrapSelf(info)),
    "Mat::ThresholdAsync",
    info
  );
}

NAN_METHOD(MatImgproc::AdaptiveThreshold) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::AdaptiveThresholdWorker>(Mat::unwrapSelf(info)),
    "Mat::AdaptiveThreshold",
    info
  );
}

NAN_METHOD(MatImgproc::AdaptiveThresholdAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::AdaptiveThresholdWorker>(Mat::unwrapSelf(info)),
    "Mat::AdaptiveThresholdAsync",
    info
  );
}

NAN_METHOD(MatImgproc::InRange) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::InRangeWorker>(Mat::unwrapSelf(info)),
    "Mat::InRange",
    info
  );
}

NAN_METHOD(MatImgproc::InRangeAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::InRangeWorker>(Mat::unwrapSelf(info)),
    "Mat::InRangeAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CvtColor) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CvtColorWorker>(Mat::unwrapSelf(info)),
    "Mat::CvtColor",
    info
  );
}

NAN_METHOD(MatImgproc::CvtColorAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CvtColorWorker>(Mat::unwrapSelf(info)),
    "Mat::CvtColorAsync",
    info
  );
}

NAN_METHOD(MatImgproc::BgrToGray) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::BgrToGrayWorker>(Mat::unwrapSelf(info)),
    "Mat::BgrToGray",
    info
  );
}

NAN_METHOD(MatImgproc::BgrToGrayAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::BgrToGrayWorker>(Mat::unwrapSelf(info)),
    "Mat::BgrToGrayAsync",
    info
  );
}

NAN_METHOD(MatImgproc::WarpAffine) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::WarpAffineWorker>(Mat::unwrapSelf(info)),
    "Mat::WarpAffine",
    info
  );
}

NAN_METHOD(MatImgproc::WarpAffineAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::WarpAffineWorker>(Mat::unwrapSelf(info)),
    "Mat::WarpAffineAsync",
    info
  );
}

NAN_METHOD(MatImgproc::WarpPerspective) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::WarpPerspectiveWorker>(Mat::unwrapSelf(info)),
    "Mat::WarpPerspective",
    info
  );
}

NAN_METHOD(MatImgproc::WarpPerspectiveAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::WarpPerspectiveWorker>(Mat::unwrapSelf(info)),
    "Mat::WarpPerspectiveAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Erode) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ErodeWorker>(Mat::unwrapSelf(info)),
    "Mat::Erode",
    info
  );
}

NAN_METHOD(MatImgproc::ErodeAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ErodeWorker>(Mat::unwrapSelf(info)),
    "Mat::ErodeAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Dilate) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DilateWorker>(Mat::unwrapSelf(info)),
    "Mat::Dilate",
    info
  );
}

NAN_METHOD(MatImgproc::DilateAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::DilateWorker>(Mat::unwrapSelf(info)),
    "Mat::DilateAsync",
    info
  );
}

NAN_METHOD(MatImgproc::MorphologyEx) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::MorphologyExWorker>(Mat::unwrapSelf(info)),
    "Mat::MorphologyEx",
    info
  );
}

NAN_METHOD(MatImgproc::MorphologyExAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::MorphologyExWorker>(Mat::unwrapSelf(info)),
    "Mat::MorphologyExAsync",
    info
  );
}

NAN_METHOD(MatImgproc::DistanceTransform) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DistanceTransformWorker>(Mat::unwrapSelf(info)),
    "Mat::DistanceTransform",
    info
  );
}

NAN_METHOD(MatImgproc::DistanceTransformAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::DistanceTransformWorker>(Mat::unwrapSelf(info)),
    "Mat::DistanceTransformAsync",
    info
  );
}

NAN_METHOD(MatImgproc::DistanceTransformWithLabels) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DistanceTransformWithLabelsWorker>(Mat::unwrapSelf(info)),
    "Mat::DistanceTransformWithLabels",
    info
  );
}

NAN_METHOD(MatImgproc::DistanceTransformWithLabelsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::DistanceTransformWithLabelsWorker>(Mat::unwrapSelf(info)),
    "Mat::DistanceTransformWithLabelsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Blur) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::BlurWorker>(Mat::unwrapSelf(info)),
    "Mat::Blur",
    info
  );
}

NAN_METHOD(MatImgproc::BlurAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::BlurWorker>(Mat::unwrapSelf(info)),
    "Mat::BlurAsync",
    info
  );
}

NAN_METHOD(MatImgproc::GaussianBlur) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::GaussianBlurWorker>(Mat::unwrapSelf(info)),
    "Mat::GaussianBlur",
    info
  );
}

NAN_METHOD(MatImgproc::GaussianBlurAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::GaussianBlurWorker>(Mat::unwrapSelf(info)),
    "Mat::GaussianBlurAsync",
    info
  );
}

NAN_METHOD(MatImgproc::MedianBlur) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::MedianBlurWorker>(Mat::unwrapSelf(info)),
    "Mat::MedianBlur",
    info
  );
}

NAN_METHOD(MatImgproc::MedianBlurAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::MedianBlurWorker>(Mat::unwrapSelf(info)),
    "Mat::MedianBlurAsync",
    info
  );
}

NAN_METHOD(MatImgproc::ConnectedComponents) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ConnectedComponentsWorker>(Mat::unwrapSelf(info)),
    "Mat::ConnectedComponents",
    info
  );
}

NAN_METHOD(MatImgproc::ConnectedComponentsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ConnectedComponentsWorker>(Mat::unwrapSelf(info)),
    "Mat::ConnectedComponentsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::ConnectedComponentsWithStats) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ConnectedComponentsWithStatsWorker>(Mat::unwrapSelf(info)),
    "Mat::ConnectedComponentsWithStats",
    info
  );
}

NAN_METHOD(MatImgproc::ConnectedComponentsWithStatsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ConnectedComponentsWithStatsWorker>(Mat::unwrapSelf(info)),
    "Mat::ConnectedComponentsWithStatsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::GrabCut) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::GrabCutWorker>(Mat::unwrapSelf(info)),
    "Mat::GrabCut",
    info
  );
}

NAN_METHOD(MatImgproc::GrabCutAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::GrabCutWorker>(Mat::unwrapSelf(info)),
    "Mat::GrabCutAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Watershed) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::WatershedWorker>(Mat::unwrapSelf(info)),
    "Mat::Watershed",
    info
  );
}

NAN_METHOD(MatImgproc::WatershedAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::WatershedWorker>(Mat::unwrapSelf(info)),
    "Mat::WatershedAsync",
    info
  );
}

NAN_METHOD(MatImgproc::_Moments) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::MomentsWorker>(Mat::unwrapSelf(info)),
    "Mat::Moments",
    info
  );
}

NAN_METHOD(MatImgproc::_MomentsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::MomentsWorker>(Mat::unwrapSelf(info)),
    "Mat::MomentsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::FindContours) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::FindContoursWorker>(Mat::unwrapSelf(info)),
    "Mat::FindContours",
    info
  );
}

NAN_METHOD(MatImgproc::FindContoursAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::FindContoursWorker>(Mat::unwrapSelf(info)),
    "Mat::FindContoursAsync",
    info
  );
}

NAN_METHOD(MatImgproc::DrawLine) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawLineWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawLine",
    info
  );
}

NAN_METHOD(MatImgproc::DrawArrowedLine) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawArrowedLineWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawArrowedLine",
    info
  );
}

NAN_METHOD(MatImgproc::DrawRectangle) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawRectangleWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawRectangle",
    info
  );
}

NAN_METHOD(MatImgproc::DrawCircle) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawCircleWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawCircle",
    info
  );
}

NAN_METHOD(MatImgproc::DrawEllipse) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawEllipseWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawEllipse",
    info
  );
}

NAN_METHOD(MatImgproc::DrawPolylines) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawPolylinesWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawPolylines",
    info
  );
}

NAN_METHOD(MatImgproc::DrawFillPoly) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawFillPolyWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawFillPoly",
    info
  );
}

NAN_METHOD(MatImgproc::DrawFillConvexPoly) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawFillConvexPolyWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawFillConvexPoly",
    info
  );
}

NAN_METHOD(MatImgproc::PutText) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::PutTextWorker>(Mat::unwrapSelf(info)),
    "Mat::PutText",
    info
  );
}

NAN_METHOD(MatImgproc::MatchTemplate) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::MatchTemplateWorker>(Mat::unwrapSelf(info)),
    "Mat::MatchTemplate",
    info
  );
}

NAN_METHOD(MatImgproc::MatchTemplateAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::MatchTemplateWorker>(Mat::unwrapSelf(info)),
    "Mat::MatchTemplateAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Canny) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CannyWorker>(Mat::unwrapSelf(info)),
    "Mat::Canny",
    info
  );
}

NAN_METHOD(MatImgproc::CannyAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CannyWorker>(Mat::unwrapSelf(info)),
    "Mat::CannyAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Sobel) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::SobelWorker>(Mat::unwrapSelf(info), true),
    "Mat::Sobel",
    info
  );
}

NAN_METHOD(MatImgproc::SobelAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::SobelWorker>(Mat::unwrapSelf(info), true),
    "Mat::SobelAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Scharr) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ScharrWorker>(Mat::unwrapSelf(info), false),
    "Mat::Scharr",
    info
  );
}

NAN_METHOD(MatImgproc::ScharrAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ScharrWorker>(Mat::unwrapSelf(info), false),
    "Mat::ScharrAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Laplacian) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::LaplacianWorker>(Mat::unwrapSelf(info)),
    "Mat::Laplacian",
    info
  );
}

NAN_METHOD(MatImgproc::LaplacianAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::LaplacianWorker>(Mat::unwrapSelf(info)),
    "Mat::LaplacianAsync",
    info
  );
}

NAN_METHOD(MatImgproc::PyrDown) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::PyrWorker>(Mat::unwrapSelf(info)),
    "Mat::PyrDown",
    info
  );
}

NAN_METHOD(MatImgproc::PyrDownAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::PyrWorker>(Mat::unwrapSelf(info)),
    "Mat::PyrDownAsync",
    info
  );
}

NAN_METHOD(MatImgproc::PyrUp) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::PyrWorker>(Mat::unwrapSelf(info), true),
    "Mat::PyrUp",
    info
  );
}

NAN_METHOD(MatImgproc::PyrUpAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::PyrWorker>(Mat::unwrapSelf(info), true),
    "Mat::PyrUpAsync",
    info
  );
}

NAN_METHOD(MatImgproc::BuildPyramid) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::BuildPyramidWorker>(Mat::unwrapSelf(info)),
    "Mat::BuildPyramid",
    info
  );
}

NAN_METHOD(MatImgproc::BuildPyramidAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::BuildPyramidWorker>(Mat::unwrapSelf(info)),
    "Mat::BuildPyramidAsync",
    info
  );
}

NAN_METHOD(MatImgproc::HoughLines) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::HoughLinesWorker>(Mat::unwrapSelf(info)),
    "Mat::HoughLines",
    info
  );
}

NAN_METHOD(MatImgproc::HoughLinesAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::HoughLinesWorker>(Mat::unwrapSelf(info)),
    "Mat::HoughLinesAsync",
    info
  );
}

NAN_METHOD(MatImgproc::HoughLinesP) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::HoughLinesPWorker>(Mat::unwrapSelf(info)),
    "Mat::HoughLinesP",
    info
  );
}

NAN_METHOD(MatImgproc::HoughLinesPAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::HoughLinesPWorker>(Mat::unwrapSelf(info)),
    "Mat::HoughLinesPAsync",
    info
  );
}

NAN_METHOD(MatImgproc::HoughCircles) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::HoughCirclesWorker>(Mat::unwrapSelf(info)),
    "Mat::HoughCircles",
    info
  );
}

NAN_METHOD(MatImgproc::HoughCirclesAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::HoughCirclesWorker>(Mat::unwrapSelf(info)),
    "Mat::HoughCirclesAsync",
    info
  );
}

NAN_METHOD(MatImgproc::EqualizeHist) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::EqualizeHistWorker>(Mat::unwrapSelf(info)),
    "Mat::EqualizeHist",
    info
  );
}

NAN_METHOD(MatImgproc::EqualizeHistAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::EqualizeHistWorker>(Mat::unwrapSelf(info)),
    "Mat::EqualizeHistAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CompareHist) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CompareHistWorker>(Mat::unwrapSelf(info)),
    "Mat::CompareHist",
    info
  );
}

NAN_METHOD(MatImgproc::CompareHistAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CompareHistWorker>(Mat::unwrapSelf(info)),
    "Mat::CompareHistAsync",
    info
  );
}

NAN_METHOD(MatImgproc::FloodFill) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::FloodFillWorker>(Mat::unwrapSelf(info)),
    "Mat::FloodFill",
    info
  );
}

NAN_METHOD(MatImgproc::FloodFillAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::FloodFillWorker>(Mat::unwrapSelf(info)),
    "Mat::FloodFillAsync",
    info
  );
}

NAN_METHOD(MatImgproc::BilateralFilter) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::BilateralFilterWorker>(Mat::unwrapSelf(info)),
    "Mat::BilateralFilter",
    info
  );
}

NAN_METHOD(MatImgproc::BilateralFilterAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::BilateralFilterWorker>(Mat::unwrapSelf(info)),
    "Mat::BilateralFilterAsync",
    info
  );
}

NAN_METHOD(MatImgproc::BoxFilter) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::BoxFilterWorker>(Mat::unwrapSelf(info)),
    "Mat::BoxFilter",
    info
  );
}

NAN_METHOD(MatImgproc::BoxFilterAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::BoxFilterWorker>(Mat::unwrapSelf(info)),
    "Mat::BoxFilterAsync",
    info
  );
}

NAN_METHOD(MatImgproc::SqrBoxFilter) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::SqrBoxFilterWorker>(Mat::unwrapSelf(info)),
    "Mat::SqrBoxFilter",
    info
  );
}

NAN_METHOD(MatImgproc::SqrBoxFilterAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::SqrBoxFilterWorker>(Mat::unwrapSelf(info)),
    "Mat::SqrBoxFilterAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Filter2D) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::Filter2DWorker>(Mat::unwrapSelf(info)),
    "Mat::Filter2D",
    info
  );
}

NAN_METHOD(MatImgproc::Filter2DAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::Filter2DWorker>(Mat::unwrapSelf(info)),
    "Mat::Filter2DAsync",
    info
  );
}

NAN_METHOD(MatImgproc::SepFilter2D) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::SepFilter2DWorker>(Mat::unwrapSelf(info)),
    "Mat::SepFilter2D",
    info
  );
}

NAN_METHOD(MatImgproc::SepFilter2DAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::SepFilter2DWorker>(Mat::unwrapSelf(info)),
    "Mat::SepFilter2DAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CornerHarris) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CornerHarrisWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerHarris",
    info
  );
}

NAN_METHOD(MatImgproc::CornerHarrisAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CornerHarrisWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerHarrisAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CornerSubPix) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CornerSubPixWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerSubPix",
    info
  );
}

NAN_METHOD(MatImgproc::CornerSubPixAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CornerSubPixWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerSubPixAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CornerMinEigenVal) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CornerMinEigenValWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerMinEigenVal",
    info
  );
}

NAN_METHOD(MatImgproc::CornerMinEigenValAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CornerMinEigenValWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerMinEigenValAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CornerEigenValsAndVecs) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CornerEigenValsAndVecsWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerEigenValsAndVecs",
    info
  );
}

NAN_METHOD(MatImgproc::CornerEigenValsAndVecsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CornerEigenValsAndVecsWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerEigenValsAndVecsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Integral) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::IntegralWorker>(Mat::unwrapSelf(info)),
    "Mat::Integral",
    info
  );
}

NAN_METHOD(MatImgproc::IntegralAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::IntegralWorker>(Mat::unwrapSelf(info)),
    "Mat::IntegralAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Undistort) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::UndistortWorker>(Mat::unwrapSelf(info)),
    "Mat::Undistort",
    info
  );
}

NAN_METHOD(MatImgproc::UndistortAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::UndistortWorker>(Mat::unwrapSelf(info)),
    "Mat::UndistortAsync",
    info
  );
}

