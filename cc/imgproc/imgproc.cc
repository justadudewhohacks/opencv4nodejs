#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMGPROC

#include "imgproc.h"
#include "imgprocBindings.h"
#include "imgprocConstants.h"

NAN_MODULE_INIT(Imgproc::Init) {
	ImgprocConstants::Init(target);
  Nan::SetMethod(target, "getStructuringElement", GetStructuringElement);
  Nan::SetMethod(target, "getRotationMatrix2D", GetRotationMatrix2D);
  Nan::SetMethod(target, "plot1DHist", Plot1DHist);
  Nan::SetMethod(target, "fitLine", FitLine);
  Nan::SetMethod(target, "getAffineTransform", GetAffineTransform);
  Nan::SetMethod(target, "getPerspectiveTransform", GetPerspectiveTransform);
  Nan::SetMethod(target, "getTextSize", GetTextSize);
  Nan::SetMethod(target, "getTextSizeAsync", GetTextSizeAsync);
  Nan::SetMethod(target, "applyColorMap", ApplyColorMap);
  Nan::SetMethod(target, "applyColorMapAsync", ApplyColorMapAsync);
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  Nan::SetMethod(target, "canny", Canny);
  Nan::SetMethod(target, "cannyAsync", CannyAsync);
#endif
#if CV_VERSION_LOWER_THAN(4, 0, 0)
  Nan::SetMethod(target, "undistortPoints", UndistortPoints);
  Nan::SetMethod(target, "undistortPointsAsync", UndistortPointsAsync);
#endif
  Nan::SetMethod(target, "goodFeaturesToTrack", GoodFeaturesToTrack);
  Nan::SetMethod(target, "goodFeaturesToTrackAsync", GoodFeaturesToTrackAsync);
  Nan::SetMethod(target, "blur", Blur);
  Nan::SetMethod(target, "blurAsync", BlurAsync);
  Nan::SetMethod(target, "gaussianBlur", GaussianBlur);
  Nan::SetMethod(target, "gaussianBlurAsync", GaussianBlurAsync);
  Nan::SetMethod(target, "medianBlur", MedianBlur);
  Nan::SetMethod(target, "medianBlurAsync", MedianBlurAsync);
  Nan::SetMethod(target, "accumulate", Accumulate);
  Nan::SetMethod(target, "accumulateAsync", AccumulateAsync);
  Nan::SetMethod(target, "accumulateProduct", AccumulateProduct);
  Nan::SetMethod(target, "accumulateProductAsync", AccumulateProductAsync);
  Nan::SetMethod(target, "accumulateSquare", AccumulateSquare);
  Nan::SetMethod(target, "accumulateSquareAsync", AccumulateSquareAsync);
  Nan::SetMethod(target, "accumulateWeighted", AccumulateWeighted);
  Nan::SetMethod(target, "accumulateWeightedAsync", AccumulateWeightedAsync);
  Nan::SetMethod(target, "calcHist", CalcHist);
  Nan::SetMethod(target, "calcHistAsync", CalcHistAsync);

  Moments::Init(target);
  Contour::Init(target);
};

NAN_METHOD(Imgproc::GetStructuringElement) {
	FF::TryCatch tryCatch("Imgproc::GetStructuringElement");

	uint shape;
	cv::Size2d size;
	cv::Point2d anchor = cv::Point2d(-1, -1);

	if (
		FF::UintConverter::arg(0, &shape, info) ||
		Size::Converter::arg(1, &size, info) ||
		Point2::Converter::optArg(2, &anchor, info)
	) {
		return tryCatch.reThrow();
	}

	info.GetReturnValue().Set(Mat::Converter::wrap(cv::getStructuringElement(shape, size, anchor)));
}

NAN_METHOD(Imgproc::GetRotationMatrix2D) {
	FF::TryCatch tryCatch("Imgproc::GetRotationMatrix2D");

	cv::Point2d center;
	double angle, scale = 1.0;
	if (
		Point2::Converter::arg(0, &center, info) ||
		FF::DoubleConverter::arg(1, &angle, info) ||
		FF::DoubleConverter::optArg(2, &scale, info)
		) {
		return tryCatch.reThrow();
	}

	info.GetReturnValue().Set(Mat::Converter::wrap(cv::getRotationMatrix2D(center, angle, scale)));
}

NAN_METHOD(Imgproc::GetAffineTransform) {
	FF::TryCatch tryCatch("Imgproc::GetAffineTransform");

	std::vector<cv::Point2f> srcPoints, dstPoints;
	if (
		Point2::ArrayWithCastConverter<cv::Point2f>::arg(0, &srcPoints, info) ||
		Point2::ArrayWithCastConverter<cv::Point2f>::arg(1, &dstPoints, info)
		) {
		return tryCatch.reThrow();
	}

	info.GetReturnValue().Set(Mat::Converter::wrap(cv::getAffineTransform(srcPoints, dstPoints)));
}

NAN_METHOD(Imgproc::GetPerspectiveTransform) {
  FF::TryCatch tryCatch("Imgproc::GetPerspectiveTransform");

  std::vector<cv::Point2f> srcPoints, dstPoints;
  if (Point2::ArrayWithCastConverter<cv::Point2f>::arg(0, &srcPoints, info)
	  || Point2::ArrayWithCastConverter<cv::Point2f>::arg(1, &dstPoints, info)
	) {
	  return tryCatch.reThrow();
  }

  info.GetReturnValue().Set(Mat::Converter::wrap(cv::getPerspectiveTransform(srcPoints, dstPoints)));
}

NAN_METHOD(Imgproc::Plot1DHist) {
	FF::TryCatch tryCatch("Imgproc::Plot1DHist");

	cv::Mat hist, plot;
	cv::Vec3d color;
	int lineType = cv::LINE_8;
	int thickness = 2;
	int shift = 0;

	v8::Local<v8::Object> opts = FF::isArgObject(info, 3) ? info[3]->ToObject(Nan::GetCurrentContext()).ToLocalChecked() : Nan::New<v8::Object>();

	if (Mat::Converter::arg(0, &hist, info) ||
		Mat::Converter::arg(1, &plot, info) ||
		Vec3::Converter::arg(2, &color, info) ||
		(
			(FF::isArgObject(info, 3) && (
				FF::IntConverter::optProp(&lineType, "lineType", opts) ||
				FF::IntConverter::optProp(&thickness, "thickness", opts) ||
				FF::IntConverter::optProp(&shift, "shift", opts)
			)) || (
				FF::IntConverter::optArg(3, &lineType, info) ||
				FF::IntConverter::optArg(4, &thickness, info) ||
				FF::IntConverter::optArg(5, &shift, info)
			)
		)
	){
		return tryCatch.reThrow();
	}

	if (1 != hist.cols) {
		return tryCatch.throwError("hist rows mismatch, expected "
			+ std::to_string(1) + ", have " + std::to_string(hist.cols));
	}
	if (hist.channels() != 1) {
		return tryCatch.throwError("expected hist to be single channeled");
	}

  double binWidth = ((double)plot.cols / (double)hist.rows);
  int plotHeight = (cv::max)(256, plot.rows - 20);
  cv::Mat normHist = hist;
  if (hist.type() != CV_64F) {
    hist.convertTo(normHist, CV_64F);
  }
  cv::normalize(normHist, normHist, 0, 256, cv::NORM_MINMAX);

  for (int i = 1; i < hist.rows; i++) {
    cv::line(
      plot,
      cv::Point(binWidth*(i - 1), plotHeight - normHist.at<double>(i - 1)),
      cv::Point(binWidth*i, plotHeight - normHist.at<double>(i)),
      color,
      thickness,
      lineType,
      shift
    );
  }

  info.GetReturnValue().Set(Mat::Converter::wrap(plot));
}

NAN_METHOD(Imgproc::FitLine) {
	FF::TryCatch tryCatch("Imgproc::FitLine");

  if (!info[0]->IsArray()) {
	  return tryCatch.throwError("expected arg 0 to be an array");
  }
  v8::Local<v8::Array> jsPoints = v8::Local<v8::Array>::Cast(info[0]);

  if (jsPoints->Length() < 2) {
	  return tryCatch.throwError("expected arg0 to be an Array with atleast 2 Points");
  }
  v8::Local<v8::Value> jsPt1 = Nan::Get(jsPoints, 0).ToLocalChecked();
  bool isPoint2 = Point2::hasInstance(jsPt1);
  bool isPoint3 = Point3::hasInstance(jsPt1);
  if (!isPoint2 && !isPoint3) {
	  return tryCatch.throwError("expected arg0 to be an Array containing instances of Point2 or Point3");
  }

  std::vector<cv::Point2d> pts2d;
  std::vector<cv::Point3d> pts3d;
  uint distType;
  double param, reps, aeps;
  if ((
	(isPoint2 && Point2::ArrayConverter::arg(0, &pts2d, info)) ||
	(!isPoint2 && Point3::ArrayConverter::arg(0, &pts3d, info))
	) ||
	FF::UintConverter::arg(1, &distType, info) ||
	FF::DoubleConverter::arg(2, &param, info) ||
	FF::DoubleConverter::arg(3, &reps, info) ||
	FF::DoubleConverter::arg(4, &aeps, info)
	) {
	  return tryCatch.reThrow();
  }

  if (isPoint2) {
    cv::Vec4f lineParams;
    cv::fitLine(pts2d, lineParams, (int)distType, param, reps, aeps);
	info.GetReturnValue().Set(Vec4::Converter::wrap(lineParams));
  }
  else {
    cv::Vec6f lineParams;
    cv::fitLine(pts3d, lineParams, (int)distType, param, reps, aeps);
	v8::Local<v8::Array> jsLineParams = Nan::New<v8::Array>(6);
    for (int i = 0; i < 6; i++) {
		Nan::Set(jsLineParams, i, Nan::New(lineParams[i]));
    }
	info.GetReturnValue().Set(jsLineParams);
  }
}

NAN_METHOD(Imgproc::GetTextSize) {
  FF::executeSyncBinding(
    std::make_shared<ImgprocBindings::GetTextSizeWorker>(),
    "Imgproc::GetTextSize",
    info
  );
}

NAN_METHOD(Imgproc::GetTextSizeAsync) {
  FF::executeAsyncBinding(
    std::make_shared<ImgprocBindings::GetTextSizeWorker>(),
    "Imgproc::GetTextSizeAsync",
    info
  );
}

NAN_METHOD(Imgproc::ApplyColorMap) {
  FF::executeSyncBinding(std::make_shared<ImgprocBindings::ApplyColorMapWorker>(),
                  "Imgproc::ApplyColorMap", info);
}

NAN_METHOD(Imgproc::ApplyColorMapAsync) {
  FF::executeAsyncBinding(std::make_shared<ImgprocBindings::ApplyColorMapWorker>(),
                   "Imgproc::ApplyColorMapAsync", info);
}

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)

NAN_METHOD(Imgproc::Canny) {
	FF::executeSyncBinding(std::make_shared<ImgprocBindings::CannyWorker>(),
		"Imgproc::Canny", info);
}

NAN_METHOD(Imgproc::CannyAsync) {
	FF::executeAsyncBinding(std::make_shared<ImgprocBindings::CannyWorker>(),
		"Imgproc::CannyAsync", info);
}

#endif

#if CV_VERSION_LOWER_THAN(4, 0, 0)
NAN_METHOD(Imgproc::UndistortPoints) {
	FF::syncBinding<ImgprocBindings::UndistortPoints>("Imgproc", "UndistortPoints", info);
}

NAN_METHOD(Imgproc::UndistortPointsAsync) {
	FF::asyncBinding<ImgprocBindings::UndistortPoints>("Imgproc", "UndistortPoints", info);
}
#endif

NAN_METHOD(Imgproc::GoodFeaturesToTrack) {
	FF::syncBinding<ImgprocBindings::GoodFeaturesToTrack>("Imgproc", "GoodFeaturesToTrack", info);
}

NAN_METHOD(Imgproc::GoodFeaturesToTrackAsync) {
	FF::asyncBinding<ImgprocBindings::GoodFeaturesToTrack>("Imgproc", "GoodFeaturesToTrack", info);
}

NAN_METHOD(Imgproc::Blur) {
	FF::syncBinding<ImgprocBindings::Blur>("Imgproc", "Blur", info);
}

NAN_METHOD(Imgproc::BlurAsync) {
	FF::asyncBinding<ImgprocBindings::Blur>("Imgproc", "Blur", info);
}

NAN_METHOD(Imgproc::GaussianBlur) {
	FF::syncBinding<ImgprocBindings::GaussianBlur>("Imgproc", "GaussianBlur", info);
}

NAN_METHOD(Imgproc::GaussianBlurAsync) {
	FF::asyncBinding<ImgprocBindings::GaussianBlur>("Imgproc", "GaussianBlur", info);
}

NAN_METHOD(Imgproc::MedianBlur) {
	FF::syncBinding<ImgprocBindings::MedianBlur>("Imgproc", "MedianBlur", info);
}

NAN_METHOD(Imgproc::MedianBlurAsync) {
	FF::asyncBinding<ImgprocBindings::MedianBlur>("Imgproc", "MedianBlur", info);
}

NAN_METHOD(Imgproc::Accumulate) {
  FF::syncBinding<ImgprocBindings::Accumulate>("Imgproc", "Accumulate", info);
}

NAN_METHOD(Imgproc::AccumulateAsync) {
  FF::asyncBinding<ImgprocBindings::Accumulate>("Imgproc", "Accumulate", info);
}

NAN_METHOD(Imgproc::AccumulateProduct) {
  FF::syncBinding<ImgprocBindings::AccumulateProduct>("Imgproc", "AccumulateProduct", info);
}

NAN_METHOD(Imgproc::AccumulateProductAsync) {
  FF::asyncBinding<ImgprocBindings::AccumulateProduct>("Imgproc", "AccumulateProduct", info);
}

NAN_METHOD(Imgproc::AccumulateSquare) {
  FF::syncBinding<ImgprocBindings::AccumulateSquare>("Imgproc", "AccumulateSquare", info);
}

NAN_METHOD(Imgproc::AccumulateSquareAsync) {
  FF::asyncBinding<ImgprocBindings::AccumulateSquare>("Imgproc", "AccumulateSquare", info);
}

NAN_METHOD(Imgproc::AccumulateWeighted) {
  FF::syncBinding<ImgprocBindings::AccumulateWeighted>("Imgproc", "AccumulateWeighted", info);
}

NAN_METHOD(Imgproc::AccumulateWeightedAsync) {
  FF::asyncBinding<ImgprocBindings::AccumulateWeighted>("Imgproc", "AccumulateWeighted", info);
}

NAN_METHOD(Imgproc::CalcHist) {
  FF::syncBinding<ImgprocBindings::CalcHist>("Imgproc", "CalcHist", info);
}

NAN_METHOD(Imgproc::CalcHistAsync) {
  FF::asyncBinding<ImgprocBindings::CalcHist>("Imgproc", "CalcHist", info);
}

#endif