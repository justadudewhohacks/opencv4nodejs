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
#if CV_VERSION_LOWER_THAN(4, 0, 0)
  Nan::SetPrototypeMethod(ctor, "undistort", Undistort);
  Nan::SetPrototypeMethod(ctor, "undistortAsync", UndistortAsync);
#endif
};

NAN_METHOD(MatImgproc::DrawContours) {
	FF::SyncBindingBase(
		std::make_shared<MatImgprocBindings::DrawContoursWorker>(Mat::unwrapSelf(info)),
		"Mat::DrawContours",
		info
	);
}

NAN_METHOD(MatImgproc::DrawContoursAsync) {
	FF::AsyncBindingBase(
		std::make_shared<MatImgprocBindings::DrawContoursWorker>(Mat::unwrapSelf(info)),
		"Mat::DrawContoursAsync",
		info
	);
}

NAN_METHOD(MatImgproc::Rescale) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::RescaleWorker>(Mat::unwrapSelf(info)),
    "Mat::Rescale",
    info
  );
}

NAN_METHOD(MatImgproc::RescaleAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::RescaleWorker>(Mat::unwrapSelf(info)),
    "Mat::RescaleAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Resize) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::ResizeWorker>(Mat::unwrapSelf(info)),
    "Mat::Resize",
    info
  );
}

NAN_METHOD(MatImgproc::ResizeAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::ResizeWorker>(Mat::unwrapSelf(info)),
    "Mat::ResizeAsync",
    info
  );
}

NAN_METHOD(MatImgproc::ResizeToMax) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::ResizeToMaxWorker>(Mat::unwrapSelf(info)),
    "Mat::ResizeToMax",
    info
  );
}

NAN_METHOD(MatImgproc::ResizeToMaxAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::ResizeToMaxWorker>(Mat::unwrapSelf(info)),
    "Mat::ResizeToMaxAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Threshold) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::ThresholdWorker>(Mat::unwrapSelf(info)),
    "Mat::Threshold",
    info
  );
}

NAN_METHOD(MatImgproc::ThresholdAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::ThresholdWorker>(Mat::unwrapSelf(info)),
    "Mat::ThresholdAsync",
    info
  );
}

NAN_METHOD(MatImgproc::AdaptiveThreshold) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::AdaptiveThresholdWorker>(Mat::unwrapSelf(info)),
    "Mat::AdaptiveThreshold",
    info
  );
}

NAN_METHOD(MatImgproc::AdaptiveThresholdAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::AdaptiveThresholdWorker>(Mat::unwrapSelf(info)),
    "Mat::AdaptiveThresholdAsync",
    info
  );
}

NAN_METHOD(MatImgproc::InRange) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::InRangeWorker>(Mat::unwrapSelf(info)),
    "Mat::InRange",
    info
  );
}

NAN_METHOD(MatImgproc::InRangeAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::InRangeWorker>(Mat::unwrapSelf(info)),
    "Mat::InRangeAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CvtColor) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::CvtColorWorker>(Mat::unwrapSelf(info)),
    "Mat::CvtColor",
    info
  );
}

NAN_METHOD(MatImgproc::CvtColorAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::CvtColorWorker>(Mat::unwrapSelf(info)),
    "Mat::CvtColorAsync",
    info
  );
}

NAN_METHOD(MatImgproc::BgrToGray) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::BgrToGrayWorker>(Mat::unwrapSelf(info)),
    "Mat::BgrToGray",
    info
  );
}

NAN_METHOD(MatImgproc::BgrToGrayAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::BgrToGrayWorker>(Mat::unwrapSelf(info)),
    "Mat::BgrToGrayAsync",
    info
  );
}

NAN_METHOD(MatImgproc::WarpAffine) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::WarpAffineWorker>(Mat::unwrapSelf(info)),
    "Mat::WarpAffine",
    info
  );
}

NAN_METHOD(MatImgproc::WarpAffineAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::WarpAffineWorker>(Mat::unwrapSelf(info)),
    "Mat::WarpAffineAsync",
    info
  );
}

NAN_METHOD(MatImgproc::WarpPerspective) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::WarpPerspectiveWorker>(Mat::unwrapSelf(info)),
    "Mat::WarpPerspective",
    info
  );
}

NAN_METHOD(MatImgproc::WarpPerspectiveAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::WarpPerspectiveWorker>(Mat::unwrapSelf(info)),
    "Mat::WarpPerspectiveAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Erode) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::ErodeWorker>(Mat::unwrapSelf(info)),
    "Mat::Erode",
    info
  );
}

NAN_METHOD(MatImgproc::ErodeAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::ErodeWorker>(Mat::unwrapSelf(info)),
    "Mat::ErodeAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Dilate) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::DilateWorker>(Mat::unwrapSelf(info)),
    "Mat::Dilate",
    info
  );
}

NAN_METHOD(MatImgproc::DilateAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::DilateWorker>(Mat::unwrapSelf(info)),
    "Mat::DilateAsync",
    info
  );
}

NAN_METHOD(MatImgproc::MorphologyEx) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::MorphologyExWorker>(Mat::unwrapSelf(info)),
    "Mat::MorphologyEx",
    info
  );
}

NAN_METHOD(MatImgproc::MorphologyExAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::MorphologyExWorker>(Mat::unwrapSelf(info)),
    "Mat::MorphologyExAsync",
    info
  );
}

NAN_METHOD(MatImgproc::DistanceTransform) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::DistanceTransformWorker>(Mat::unwrapSelf(info)),
    "Mat::DistanceTransform",
    info
  );
}

NAN_METHOD(MatImgproc::DistanceTransformAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::DistanceTransformWorker>(Mat::unwrapSelf(info)),
    "Mat::DistanceTransformAsync",
    info
  );
}

NAN_METHOD(MatImgproc::DistanceTransformWithLabels) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::DistanceTransformWithLabelsWorker>(Mat::unwrapSelf(info)),
    "Mat::DistanceTransformWithLabels",
    info
  );
}

NAN_METHOD(MatImgproc::DistanceTransformWithLabelsAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::DistanceTransformWithLabelsWorker>(Mat::unwrapSelf(info)),
    "Mat::DistanceTransformWithLabelsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Blur) {
	Mat::SyncBinding<MatImgprocBindings::Blur>("Blur", info);
}

NAN_METHOD(MatImgproc::BlurAsync) {
	Mat::AsyncBinding<MatImgprocBindings::Blur>("Blur", info);
}

NAN_METHOD(MatImgproc::GaussianBlur) {
	Mat::SyncBinding<MatImgprocBindings::GaussianBlur>("GaussianBlur", info);
}

NAN_METHOD(MatImgproc::GaussianBlurAsync) {
	Mat::AsyncBinding<MatImgprocBindings::GaussianBlur>("GaussianBlur", info);
}

NAN_METHOD(MatImgproc::MedianBlur) {
	Mat::SyncBinding<MatImgprocBindings::MedianBlur>("MedianBlur", info);
}

NAN_METHOD(MatImgproc::MedianBlurAsync) {
	Mat::AsyncBinding<MatImgprocBindings::MedianBlur>("MedianBlur", info);
}

NAN_METHOD(MatImgproc::ConnectedComponents) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::ConnectedComponentsWorker>(Mat::unwrapSelf(info)),
    "Mat::ConnectedComponents",
    info
  );
}

NAN_METHOD(MatImgproc::ConnectedComponentsAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::ConnectedComponentsWorker>(Mat::unwrapSelf(info)),
    "Mat::ConnectedComponentsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::ConnectedComponentsWithStats) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::ConnectedComponentsWithStatsWorker>(Mat::unwrapSelf(info)),
    "Mat::ConnectedComponentsWithStats",
    info
  );
}

NAN_METHOD(MatImgproc::ConnectedComponentsWithStatsAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::ConnectedComponentsWithStatsWorker>(Mat::unwrapSelf(info)),
    "Mat::ConnectedComponentsWithStatsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::GrabCut) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::GrabCutWorker>(Mat::unwrapSelf(info)),
    "Mat::GrabCut",
    info
  );
}

NAN_METHOD(MatImgproc::GrabCutAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::GrabCutWorker>(Mat::unwrapSelf(info)),
    "Mat::GrabCutAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Watershed) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::WatershedWorker>(Mat::unwrapSelf(info)),
    "Mat::Watershed",
    info
  );
}

NAN_METHOD(MatImgproc::WatershedAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::WatershedWorker>(Mat::unwrapSelf(info)),
    "Mat::WatershedAsync",
    info
  );
}

NAN_METHOD(MatImgproc::_Moments) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::MomentsWorker>(Mat::unwrapSelf(info)),
    "Mat::Moments",
    info
  );
}

NAN_METHOD(MatImgproc::_MomentsAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::MomentsWorker>(Mat::unwrapSelf(info)),
    "Mat::MomentsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::FindContours) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::FindContoursWorker>(Mat::unwrapSelf(info)),
    "Mat::FindContours",
    info
  );
}

NAN_METHOD(MatImgproc::FindContoursAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::FindContoursWorker>(Mat::unwrapSelf(info)),
    "Mat::FindContoursAsync",
    info
  );
}

NAN_METHOD(MatImgproc::DrawLine) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::DrawLineWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawLine",
    info
  );
}

NAN_METHOD(MatImgproc::DrawArrowedLine) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::DrawArrowedLineWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawArrowedLine",
    info
  );
}

NAN_METHOD(MatImgproc::DrawRectangle) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::DrawRectangleWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawRectangle",
    info
  );
}

NAN_METHOD(MatImgproc::DrawCircle) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::DrawCircleWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawCircle",
    info
  );
}

NAN_METHOD(MatImgproc::DrawEllipse) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::DrawEllipseWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawEllipse",
    info
  );
}

NAN_METHOD(MatImgproc::DrawPolylines) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::DrawPolylinesWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawPolylines",
    info
  );
}

NAN_METHOD(MatImgproc::DrawFillPoly) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::DrawFillPolyWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawFillPoly",
    info
  );
}

NAN_METHOD(MatImgproc::DrawFillConvexPoly) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::DrawFillConvexPolyWorker>(Mat::unwrapSelf(info)),
    "Mat::DrawFillConvexPoly",
    info
  );
}

NAN_METHOD(MatImgproc::PutText) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::PutTextWorker>(Mat::unwrapSelf(info)),
    "Mat::PutText",
    info
  );
}

NAN_METHOD(MatImgproc::MatchTemplate) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::MatchTemplateWorker>(Mat::unwrapSelf(info)),
    "Mat::MatchTemplate",
    info
  );
}

NAN_METHOD(MatImgproc::MatchTemplateAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::MatchTemplateWorker>(Mat::unwrapSelf(info)),
    "Mat::MatchTemplateAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Canny) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::CannyWorker>(Mat::unwrapSelf(info)),
    "Mat::Canny",
    info
  );
}

NAN_METHOD(MatImgproc::CannyAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::CannyWorker>(Mat::unwrapSelf(info)),
    "Mat::CannyAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Sobel) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::SobelWorker>(Mat::unwrapSelf(info), true),
    "Mat::Sobel",
    info
  );
}

NAN_METHOD(MatImgproc::SobelAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::SobelWorker>(Mat::unwrapSelf(info), true),
    "Mat::SobelAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Scharr) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::ScharrWorker>(Mat::unwrapSelf(info), false),
    "Mat::Scharr",
    info
  );
}

NAN_METHOD(MatImgproc::ScharrAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::ScharrWorker>(Mat::unwrapSelf(info), false),
    "Mat::ScharrAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Laplacian) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::LaplacianWorker>(Mat::unwrapSelf(info)),
    "Mat::Laplacian",
    info
  );
}

NAN_METHOD(MatImgproc::LaplacianAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::LaplacianWorker>(Mat::unwrapSelf(info)),
    "Mat::LaplacianAsync",
    info
  );
}

NAN_METHOD(MatImgproc::PyrDown) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::PyrWorker>(Mat::unwrapSelf(info)),
    "Mat::PyrDown",
    info
  );
}

NAN_METHOD(MatImgproc::PyrDownAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::PyrWorker>(Mat::unwrapSelf(info)),
    "Mat::PyrDownAsync",
    info
  );
}

NAN_METHOD(MatImgproc::PyrUp) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::PyrWorker>(Mat::unwrapSelf(info), true),
    "Mat::PyrUp",
    info
  );
}

NAN_METHOD(MatImgproc::PyrUpAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::PyrWorker>(Mat::unwrapSelf(info), true),
    "Mat::PyrUpAsync",
    info
  );
}

NAN_METHOD(MatImgproc::BuildPyramid) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::BuildPyramidWorker>(Mat::unwrapSelf(info)),
    "Mat::BuildPyramid",
    info
  );
}

NAN_METHOD(MatImgproc::BuildPyramidAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::BuildPyramidWorker>(Mat::unwrapSelf(info)),
    "Mat::BuildPyramidAsync",
    info
  );
}

NAN_METHOD(MatImgproc::HoughLines) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::HoughLinesWorker>(Mat::unwrapSelf(info)),
    "Mat::HoughLines",
    info
  );
}

NAN_METHOD(MatImgproc::HoughLinesAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::HoughLinesWorker>(Mat::unwrapSelf(info)),
    "Mat::HoughLinesAsync",
    info
  );
}

NAN_METHOD(MatImgproc::HoughLinesP) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::HoughLinesPWorker>(Mat::unwrapSelf(info)),
    "Mat::HoughLinesP",
    info
  );
}

NAN_METHOD(MatImgproc::HoughLinesPAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::HoughLinesPWorker>(Mat::unwrapSelf(info)),
    "Mat::HoughLinesPAsync",
    info
  );
}

NAN_METHOD(MatImgproc::HoughCircles) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::HoughCirclesWorker>(Mat::unwrapSelf(info)),
    "Mat::HoughCircles",
    info
  );
}

NAN_METHOD(MatImgproc::HoughCirclesAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::HoughCirclesWorker>(Mat::unwrapSelf(info)),
    "Mat::HoughCirclesAsync",
    info
  );
}

NAN_METHOD(MatImgproc::EqualizeHist) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::EqualizeHistWorker>(Mat::unwrapSelf(info)),
    "Mat::EqualizeHist",
    info
  );
}

NAN_METHOD(MatImgproc::EqualizeHistAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::EqualizeHistWorker>(Mat::unwrapSelf(info)),
    "Mat::EqualizeHistAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CompareHist) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::CompareHistWorker>(Mat::unwrapSelf(info)),
    "Mat::CompareHist",
    info
  );
}

NAN_METHOD(MatImgproc::CompareHistAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::CompareHistWorker>(Mat::unwrapSelf(info)),
    "Mat::CompareHistAsync",
    info
  );
}

NAN_METHOD(MatImgproc::FloodFill) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::FloodFillWorker>(Mat::unwrapSelf(info)),
    "Mat::FloodFill",
    info
  );
}

NAN_METHOD(MatImgproc::FloodFillAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::FloodFillWorker>(Mat::unwrapSelf(info)),
    "Mat::FloodFillAsync",
    info
  );
}

NAN_METHOD(MatImgproc::BilateralFilter) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::BilateralFilterWorker>(Mat::unwrapSelf(info)),
    "Mat::BilateralFilter",
    info
  );
}

NAN_METHOD(MatImgproc::BilateralFilterAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::BilateralFilterWorker>(Mat::unwrapSelf(info)),
    "Mat::BilateralFilterAsync",
    info
  );
}

NAN_METHOD(MatImgproc::BoxFilter) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::BoxFilterWorker>(Mat::unwrapSelf(info)),
    "Mat::BoxFilter",
    info
  );
}

NAN_METHOD(MatImgproc::BoxFilterAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::BoxFilterWorker>(Mat::unwrapSelf(info)),
    "Mat::BoxFilterAsync",
    info
  );
}

NAN_METHOD(MatImgproc::SqrBoxFilter) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::SqrBoxFilterWorker>(Mat::unwrapSelf(info)),
    "Mat::SqrBoxFilter",
    info
  );
}

NAN_METHOD(MatImgproc::SqrBoxFilterAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::SqrBoxFilterWorker>(Mat::unwrapSelf(info)),
    "Mat::SqrBoxFilterAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Filter2D) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::Filter2DWorker>(Mat::unwrapSelf(info)),
    "Mat::Filter2D",
    info
  );
}

NAN_METHOD(MatImgproc::Filter2DAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::Filter2DWorker>(Mat::unwrapSelf(info)),
    "Mat::Filter2DAsync",
    info
  );
}

NAN_METHOD(MatImgproc::SepFilter2D) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::SepFilter2DWorker>(Mat::unwrapSelf(info)),
    "Mat::SepFilter2D",
    info
  );
}

NAN_METHOD(MatImgproc::SepFilter2DAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::SepFilter2DWorker>(Mat::unwrapSelf(info)),
    "Mat::SepFilter2DAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CornerHarris) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::CornerHarrisWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerHarris",
    info
  );
}

NAN_METHOD(MatImgproc::CornerHarrisAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::CornerHarrisWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerHarrisAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CornerSubPix) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::CornerSubPixWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerSubPix",
    info
  );
}

NAN_METHOD(MatImgproc::CornerSubPixAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::CornerSubPixWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerSubPixAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CornerMinEigenVal) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::CornerMinEigenValWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerMinEigenVal",
    info
  );
}

NAN_METHOD(MatImgproc::CornerMinEigenValAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::CornerMinEigenValWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerMinEigenValAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CornerEigenValsAndVecs) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::CornerEigenValsAndVecsWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerEigenValsAndVecs",
    info
  );
}

NAN_METHOD(MatImgproc::CornerEigenValsAndVecsAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::CornerEigenValsAndVecsWorker>(Mat::unwrapSelf(info)),
    "Mat::CornerEigenValsAndVecsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Integral) {
  FF::SyncBindingBase(
    std::make_shared<MatImgprocBindings::IntegralWorker>(Mat::unwrapSelf(info)),
    "Mat::Integral",
    info
  );
}

NAN_METHOD(MatImgproc::IntegralAsync) {
  FF::AsyncBindingBase(
    std::make_shared<MatImgprocBindings::IntegralWorker>(Mat::unwrapSelf(info)),
    "Mat::IntegralAsync",
    info
  );
}

#if CV_VERSION_LOWER_THAN(4, 0, 0)
NAN_METHOD(MatImgproc::Undistort) {
	Mat::SyncBinding<MatImgprocBindings::Undistort>("Undistort", info);
}

NAN_METHOD(MatImgproc::UndistortAsync) {
	Mat::AsyncBinding<MatImgprocBindings::Undistort>("Undistort", info);
}
#endif

