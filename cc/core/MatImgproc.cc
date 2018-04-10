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
};

NAN_METHOD(MatImgproc::DrawContours) {
  FF_METHOD_CONTEXT("Mat::DrawContours");

  FF_ARG_ARRAY(0, FF_ARR jsContours);
  FF_ARG_INSTANCE(1, cv::Vec3d color, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);

  // optional args
  bool hasOptArgsObj = FF_HAS_ARG(2) && info[2]->IsObject();
  FF_OBJ optArgs = hasOptArgsObj ? info[2]->ToObject() : FF_NEW_OBJ();
  FF_GET_INT_IFDEF(optArgs, int contourIdx, "contourIdx", 0);
  FF_GET_INT_IFDEF(optArgs, int maxLevel, "maxLevel", INT_MAX);
  FF_GET_INSTANCE_IFDEF(optArgs, cv::Point2d offset, "offset", Point2::constructor, FF_UNWRAP_PT2_AND_GET, Point2, cv::Point2d());
  FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
  FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 1);
  if (!hasOptArgsObj) {
    FF_ARG_INT_IFDEF(2, contourIdx, contourIdx);
    FF_ARG_UINT_IFDEF(3, maxLevel, maxLevel);
    FF_ARG_INSTANCE_IFDEF(4, offset, Point2::constructor, FF_UNWRAP_PT2_AND_GET, offset);
    FF_ARG_INT_IFDEF(5, lineType, lineType);
    FF_ARG_INT_IFDEF(6, thickness, thickness);
  }

  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  for (int i = 0; i < jsContours->Length(); i++) {
    FF_OBJ jsContour = jsContours->Get(i)->ToObject();
    contours.push_back(FF_UNWRAP_CONTOUR_AND_GET(jsContour));
    hierarchy.push_back(FF_UNWRAP_CONTOUR(jsContour)->hierarchy);
  }

  cv::drawContours(
    FF_UNWRAP_MAT_AND_GET(info.This()),
    contours,
    contourIdx,
    color,
    thickness,
    lineType,
    hierarchy,
    (int)maxLevel,
    offset
  );
  FF_RETURN(info.This());
}

NAN_METHOD(MatImgproc::Rescale) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::RescaleWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::Rescale",
    info
  );
}

NAN_METHOD(MatImgproc::RescaleAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::RescaleWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::RescaleAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Resize) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ResizeWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::Resize",
    info
  );
}

NAN_METHOD(MatImgproc::ResizeAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ResizeWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::ResizeAsync",
    info
  );
}

NAN_METHOD(MatImgproc::ResizeToMax) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ResizeToMaxWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::ResizeToMax",
    info
  );
}

NAN_METHOD(MatImgproc::ResizeToMaxAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ResizeToMaxWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::ResizeToMaxAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Threshold) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ThresholdWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::Threshold",
    info
  );
}

NAN_METHOD(MatImgproc::ThresholdAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ThresholdWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::ThresholdAsync",
    info
  );
}

NAN_METHOD(MatImgproc::AdaptiveThreshold) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::AdaptiveThresholdWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::AdaptiveThreshold",
    info
  );
}

NAN_METHOD(MatImgproc::AdaptiveThresholdAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::AdaptiveThresholdWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::AdaptiveThresholdAsync",
    info
  );
}

NAN_METHOD(MatImgproc::InRange) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::InRangeWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::InRange",
    info
  );
}

NAN_METHOD(MatImgproc::InRangeAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::InRangeWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::InRangeAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CvtColor) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CvtColorWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::CvtColor",
    info
  );
}

NAN_METHOD(MatImgproc::CvtColorAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CvtColorWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::CvtColorAsync",
    info
  );
}

NAN_METHOD(MatImgproc::BgrToGray) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::BgrToGrayWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::BgrToGray",
    info
  );
}

NAN_METHOD(MatImgproc::BgrToGrayAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::BgrToGrayWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::BgrToGrayAsync",
    info
  );
}

NAN_METHOD(MatImgproc::WarpAffine) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::WarpAffineWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::WarpAffine",
    info
  );
}

NAN_METHOD(MatImgproc::WarpAffineAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::WarpAffineWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::WarpAffineAsync",
    info
  );
}

NAN_METHOD(MatImgproc::WarpPerspective) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::WarpPerspectiveWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::WarpPerspective",
    info
  );
}

NAN_METHOD(MatImgproc::WarpPerspectiveAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::WarpPerspectiveWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::WarpPerspectiveAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Erode) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ErodeWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::Erode",
    info
  );
}

NAN_METHOD(MatImgproc::ErodeAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ErodeWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::ErodeAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Dilate) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DilateWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::Dilate",
    info
  );
}

NAN_METHOD(MatImgproc::DilateAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::DilateWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::DilateAsync",
    info
  );
}

NAN_METHOD(MatImgproc::MorphologyEx) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::MorphologyExWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::MorphologyEx",
    info
  );
}

NAN_METHOD(MatImgproc::MorphologyExAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::MorphologyExWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::MorphologyExAsync",
    info
  );
}

NAN_METHOD(MatImgproc::DistanceTransform) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DistanceTransformWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::DistanceTransform",
    info
  );
}

NAN_METHOD(MatImgproc::DistanceTransformAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::DistanceTransformWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::DistanceTransformAsync",
    info
  );
}

NAN_METHOD(MatImgproc::DistanceTransformWithLabels) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DistanceTransformWithLabelsWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::DistanceTransformWithLabels",
    info
  );
}

NAN_METHOD(MatImgproc::DistanceTransformWithLabelsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::DistanceTransformWithLabelsWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::DistanceTransformWithLabelsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Blur) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::BlurWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::Blur",
    info
  );
}

NAN_METHOD(MatImgproc::BlurAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::BlurWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::BlurAsync",
    info
  );
}

NAN_METHOD(MatImgproc::GaussianBlur) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::GaussianBlurWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::GaussianBlur",
    info
  );
}

NAN_METHOD(MatImgproc::GaussianBlurAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::GaussianBlurWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::GaussianBlurAsync",
    info
  );
}

NAN_METHOD(MatImgproc::MedianBlur) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::MedianBlurWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::MedianBlur",
    info
  );
}

NAN_METHOD(MatImgproc::MedianBlurAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::MedianBlurWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::MedianBlurAsync",
    info
  );
}

NAN_METHOD(MatImgproc::ConnectedComponents) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ConnectedComponentsWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::ConnectedComponents",
    info
  );
}

NAN_METHOD(MatImgproc::ConnectedComponentsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ConnectedComponentsWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::ConnectedComponentsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::ConnectedComponentsWithStats) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ConnectedComponentsWithStatsWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::ConnectedComponentsWithStats",
    info
  );
}

NAN_METHOD(MatImgproc::ConnectedComponentsWithStatsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ConnectedComponentsWithStatsWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::ConnectedComponentsWithStatsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::GrabCut) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::GrabCutWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::GrabCut",
    info
  );
}

NAN_METHOD(MatImgproc::GrabCutAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::GrabCutWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::GrabCutAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Watershed) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::WatershedWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::Watershed",
    info
  );
}

NAN_METHOD(MatImgproc::WatershedAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::WatershedWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::WatershedAsync",
    info
  );
}

NAN_METHOD(MatImgproc::_Moments) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::MomentsWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::_Moments",
    info
  );
}

NAN_METHOD(MatImgproc::_MomentsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::MomentsWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::_MomentsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::FindContours) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::FindContoursWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::FindContours",
    info
  );
}

NAN_METHOD(MatImgproc::FindContoursAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::FindContoursWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::FindContoursAsync",
    info
  );
}

NAN_METHOD(MatImgproc::DrawLine) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawLineWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::DrawLine",
    info
  );
}

NAN_METHOD(MatImgproc::DrawArrowedLine) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawArrowedLineWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::DrawArrowedLine",
    info
  );
}

NAN_METHOD(MatImgproc::DrawRectangle) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawRectangleWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::DrawRectangle",
    info
  );
}

NAN_METHOD(MatImgproc::DrawCircle) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawCircleWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::DrawCircle",
    info
  );
}

NAN_METHOD(MatImgproc::DrawEllipse) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawEllipseWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::DrawEllipse",
    info
  );
}

NAN_METHOD(MatImgproc::DrawPolylines) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawPolylinesWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::DrawPolylines",
    info
  );
}

NAN_METHOD(MatImgproc::DrawFillPoly) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawFillPolyWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::DrawFillPoly",
    info
  );
}

NAN_METHOD(MatImgproc::DrawFillConvexPoly) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::DrawFillConvexPolyWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::DrawFillConvexPoly",
    info
  );
}

NAN_METHOD(MatImgproc::PutText) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::PutTextWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::PutText",
    info
  );
}

NAN_METHOD(MatImgproc::MatchTemplate) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::MatchTemplateWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::MatchTemplate",
    info
  );
}

NAN_METHOD(MatImgproc::MatchTemplateAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::MatchTemplateWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::MatchTemplateAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Canny) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CannyWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::Canny",
    info
  );
}

NAN_METHOD(MatImgproc::CannyAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CannyWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::CannyAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Sobel) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::SobelWorker>(Mat::Converter::unwrap(info.This()), true),
    "MatImgproc::Sobel",
    info
  );
}

NAN_METHOD(MatImgproc::SobelAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::SobelWorker>(Mat::Converter::unwrap(info.This()), true),
    "MatImgproc::SobelAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Scharr) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::ScharrWorker>(Mat::Converter::unwrap(info.This()), false),
    "MatImgproc::Scharr",
    info
  );
}

NAN_METHOD(MatImgproc::ScharrAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::ScharrWorker>(Mat::Converter::unwrap(info.This()), false),
    "MatImgproc::ScharrAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Laplacian) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::LaplacianWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::Laplacian",
    info
  );
}

NAN_METHOD(MatImgproc::LaplacianAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::LaplacianWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::LaplacianAsync",
    info
  );
}

NAN_METHOD(MatImgproc::PyrDown) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::PyrWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::PyrDown",
    info
  );
}

NAN_METHOD(MatImgproc::PyrDownAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::PyrWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::PyrDownAsync",
    info
  );
}

NAN_METHOD(MatImgproc::PyrUp) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::PyrWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::PyrUp",
    info
  );
}

NAN_METHOD(MatImgproc::PyrUpAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::PyrWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::PyrUpAsync",
    info
  );
}

NAN_METHOD(MatImgproc::BuildPyramid) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::BuildPyramidWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::BuildPyramid",
    info
  );
}

NAN_METHOD(MatImgproc::BuildPyramidAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::BuildPyramidWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::BuildPyramidAsync",
    info
  );
}

NAN_METHOD(MatImgproc::HoughLines) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::HoughLinesWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::HoughLines",
    info
  );
}

NAN_METHOD(MatImgproc::HoughLinesAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::HoughLinesWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::HoughLinesAsync",
    info
  );
}

NAN_METHOD(MatImgproc::HoughLinesP) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::HoughLinesPWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::HoughLinesP",
    info
  );
}

NAN_METHOD(MatImgproc::HoughLinesPAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::HoughLinesPWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::HoughLinesPAsync",
    info
  );
}

NAN_METHOD(MatImgproc::HoughCircles) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::HoughCirclesWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::HoughCircles",
    info
  );
}

NAN_METHOD(MatImgproc::HoughCirclesAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::HoughCirclesWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::HoughCirclesAsync",
    info
  );
}

NAN_METHOD(MatImgproc::EqualizeHist) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::EqualizeHistWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::EqualizeHist",
    info
  );
}

NAN_METHOD(MatImgproc::EqualizeHistAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::EqualizeHistWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::EqualizeHistAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CompareHist) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CompareHistWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::CompareHist",
    info
  );
}

NAN_METHOD(MatImgproc::CompareHistAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CompareHistWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::CompareHistAsync",
    info
  );
}

NAN_METHOD(MatImgproc::FloodFill) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::FloodFillWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::FloodFill",
    info
  );
}

NAN_METHOD(MatImgproc::FloodFillAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::FloodFillWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::FloodFillAsync",
    info
  );
}

NAN_METHOD(MatImgproc::BilateralFilter) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::BilateralFilterWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::BilateralFilter",
    info
  );
}

NAN_METHOD(MatImgproc::BilateralFilterAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::BilateralFilterWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::BilateralFilterAsync",
    info
  );
}

NAN_METHOD(MatImgproc::BoxFilter) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::BoxFilterWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::BoxFilter",
    info
  );
}

NAN_METHOD(MatImgproc::BoxFilterAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::BoxFilterWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::BoxFilterAsync",
    info
  );
}

NAN_METHOD(MatImgproc::SqrBoxFilter) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::SqrBoxFilterWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::SqrBoxFilter",
    info
  );
}

NAN_METHOD(MatImgproc::SqrBoxFilterAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::SqrBoxFilterWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::SqrBoxFilterAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Filter2D) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::Filter2DWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::Filter2D",
    info
  );
}

NAN_METHOD(MatImgproc::Filter2DAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::Filter2DWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::Filter2DAsync",
    info
  );
}

NAN_METHOD(MatImgproc::SepFilter2D) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::SepFilter2DWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::SepFilter2D",
    info
  );
}

NAN_METHOD(MatImgproc::SepFilter2DAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::SepFilter2DWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::SepFilter2DAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CornerHarris) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CornerHarrisWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::CornerHarris",
    info
  );
}

NAN_METHOD(MatImgproc::CornerHarrisAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CornerHarrisWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::CornerHarrisAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CornerSubPix) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CornerSubPixWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::CornerSubPix",
    info
  );
}

NAN_METHOD(MatImgproc::CornerSubPixAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CornerSubPixWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::CornerSubPixAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CornerMinEigenVal) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CornerMinEigenValWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::CornerMinEigenVal",
    info
  );
}

NAN_METHOD(MatImgproc::CornerMinEigenValAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CornerMinEigenValWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::CornerMinEigenValAsync",
    info
  );
}

NAN_METHOD(MatImgproc::CornerEigenValsAndVecs) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::CornerEigenValsAndVecsWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::CornerEigenValsAndVecs",
    info
  );
}

NAN_METHOD(MatImgproc::CornerEigenValsAndVecsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::CornerEigenValsAndVecsWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::CornerEigenValsAndVecsAsync",
    info
  );
}

NAN_METHOD(MatImgproc::Integral) {
  FF::SyncBinding(
    std::make_shared<MatImgprocBindings::IntegralWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::Integral",
    info
  );
}

NAN_METHOD(MatImgproc::IntegralAsync) {
  FF::AsyncBinding(
    std::make_shared<MatImgprocBindings::IntegralWorker>(Mat::Converter::unwrap(info.This())),
    "MatImgproc::IntegralAsync",
    info
  );
}
