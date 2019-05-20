#include "imgproc.h"
#include "imgprocBindings.h"

#define FF_DEFINE_CALC_HIST(name, n, constRangesArray)                                                        \
  cv::MatND name(cv::Mat img, cv::Mat mask, int channels[], int histSize[], std::vector<float*> rangesVec) {  \
    const float* ranges[] = constRangesArray;                                                                  \
    cv::MatND hist;                                                                                            \
    cv::calcHist(&img, 1, channels, mask, hist, n, histSize, ranges, true, false);                            \
    return hist;                                                                                              \
  }

#define FF_HIST_RANGE_1 { rangesVec.at(0) }
#define FF_HIST_RANGE_2 { rangesVec.at(0), rangesVec.at(1) }
#define FF_HIST_RANGE_3 { rangesVec.at(0), rangesVec.at(1), rangesVec.at(2) }
#define FF_HIST_RANGE_4 { rangesVec.at(0), rangesVec.at(1), rangesVec.at(2), rangesVec.at(3) }

FF_DEFINE_CALC_HIST(calcHist1, 1, FF_HIST_RANGE_1);
FF_DEFINE_CALC_HIST(calcHist2, 2, FF_HIST_RANGE_2);
FF_DEFINE_CALC_HIST(calcHist3, 3, FF_HIST_RANGE_3);
FF_DEFINE_CALC_HIST(calcHist4, 4, FF_HIST_RANGE_4);

NAN_MODULE_INIT(Imgproc::Init) {
  Nan::SetMethod(target, "getStructuringElement", GetStructuringElement);
  Nan::SetMethod(target, "getRotationMatrix2D", GetRotationMatrix2D);
  Nan::SetMethod(target, "calcHist", CalcHist);
  Nan::SetMethod(target, "plot1DHist", Plot1DHist);
  Nan::SetMethod(target, "fitLine", FitLine);
  Nan::SetMethod(target, "getAffineTransform", GetAffineTransform);
  Nan::SetMethod(target, "getPerspectiveTransform", GetPerspectiveTransform);
  Nan::SetMethod(target, "undistortPoints", UndistortPoints);
  Nan::SetMethod(target, "undistortPointsAsync", UndistortPointsAsync);
  Nan::SetMethod(target, "getTextSize", GetTextSize);
  Nan::SetMethod(target, "getTextSizeAsync", GetTextSizeAsync);
  Nan::SetMethod(target, "applyColorMap", ApplyColorMap);
  Nan::SetMethod(target, "applyColorMapAsync", ApplyColorMapAsync);
#if CV_VERSION_MINOR > 1
  Nan::SetMethod(target, "canny", Canny);
  Nan::SetMethod(target, "cannyAsync", CannyAsync);
#endif
  Moments::Init(target);
  Contour::Init(target);
};

NAN_METHOD(Imgproc::GetStructuringElement) {
	FF::TryCatch tryCatch;

	uint shape;
	cv::Size2d size;
	cv::Point2d anchor = cv::Point2d(-1, -1);

	if (
		UintConverter::arg(0, &shape, info) ||
		Size::Converter::arg(1, &size, info) ||
		Point2::Converter::optArg(2, &anchor, info)
	) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Imgproc::GetStructuringElement"));
		return;
	}

	v8::Local<v8::Object> jsKernel = FF::newInstance(Nan::New(Mat::constructor));
	FF_UNWRAP_MAT_AND_GET(jsKernel) = cv::getStructuringElement(shape, size, anchor);
	info.GetReturnValue().Set(jsKernel);
}

NAN_METHOD(Imgproc::GetRotationMatrix2D) {
	FF::TryCatch tryCatch;

	cv::Point2d center;
	double angle, scale = 1.0;
	if (
		Point2::Converter::arg(0, &center, info) ||
		DoubleConverter::arg(1, &angle, info) ||
		DoubleConverter::optArg(2, &scale, info)
		) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Imgproc::GetRotationMatrix2D"));
		return;
	}

	v8::Local<v8::Object> jsRotationMat = FF::newInstance(Nan::New(Mat::constructor));
	FF_UNWRAP_MAT_AND_GET(jsRotationMat) = cv::getRotationMatrix2D(center, angle, scale);
	info.GetReturnValue().Set(jsRotationMat);
}

NAN_METHOD(Imgproc::GetAffineTransform) {
	FF::TryCatch tryCatch;

	std::vector<cv::Point2f> srcPoints, dstPoints;
	if (
		ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(0, &srcPoints, info) ||
		ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(1, &dstPoints, info)
		) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Imgproc::GetAffineTransform"));
		return;
	}

	v8::Local<v8::Object> jsMat = FF::newInstance(Nan::New(Mat::constructor));
	FF_UNWRAP_MAT_AND_GET(jsMat) = cv::getAffineTransform(srcPoints, dstPoints);
	info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Imgproc::GetPerspectiveTransform) {
  FF::TryCatch tryCatch;

  std::vector<cv::Point2f> srcPoints, dstPoints;
  if (ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(0, &srcPoints, info)
	  || ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(1, &dstPoints, info)
	) {
	  v8::Local<v8::Value> err = tryCatch.formatCatchedError("Imgproc::GetPerspectiveTransform");
	  tryCatch.throwNew(err);
	  return;
  }

  v8::Local<v8::Object> jsMat = FF::newInstance(Nan::New(Mat::constructor));
  FF_UNWRAP_MAT_AND_GET(jsMat) = cv::getPerspectiveTransform(srcPoints, dstPoints);
  info.GetReturnValue().Set(jsMat);
}
NAN_METHOD(Imgproc::UndistortPoints) {
  FF::SyncBinding(std::make_shared<ImgprocBindings::UndistortPointsWorker>(),
                  "Imgproc::UndistortPoints", info);
}

NAN_METHOD(Imgproc::UndistortPointsAsync) {
  FF::AsyncBinding(std::make_shared<ImgprocBindings::UndistortPointsWorker>(),
                   "Imgproc::UndistortPointsAsync", info);
}

NAN_METHOD(Imgproc::CalcHist) {
  FF_METHOD_CONTEXT("CalcHist");

  FF::TryCatch tryCatch;
  cv::Mat img, mask = cv::noArray().getMat();
  std::vector<std::vector<float>> _ranges;
  if (
	  Mat::Converter::arg(0, &img, info) ||
	  Mat::Converter::optArg(2, &mask, info)
	) {
	  tryCatch.throwNew(tryCatch.formatCatchedError("Imgproc::CalcHist"));
	  return;
  }
  if (!info[1]->IsArray()) {
	  return tryCatch.throwNew(FF_NEW_STRING("Imgproc::CalcHist - expected arg 1 to be an array"));
  }
  v8::Local<v8::Array> jsHistAxes = v8::Local<v8::Array>::Cast(info[1]);

  cv::Mat inputImg = img;
  int inputType = CV_MAKETYPE(CV_32F, img.channels());
  if (inputType != img.type()) {
    img.convertTo(inputImg, inputType);
  }

  int dims = jsHistAxes->Length();
  int* channels = new int[dims];
  int* histSize = new int[dims];
  std::vector<float*> ranges;
  // TODO replace old macros
  for (int i = 0; i < dims; ++i) {
    ranges.push_back(new float[dims]);
    v8::Local<v8::Object> jsAxis = FF_CAST_OBJ(jsHistAxes->Get(i));
	if (!Nan::HasOwnProperty(jsAxis, Nan::New("ranges").ToLocalChecked()).FromJust()) {
		return tryCatch.throwNew(FF_NEW_STRING("Imgproc::CalcHist - expected axis object to have ranges property"));
	}
	v8::Local<v8::Value> jsRangesVal = Nan::Get(jsAxis, Nan::New("ranges").ToLocalChecked()).ToLocalChecked();
	if (!jsRangesVal->IsArray()) {
		return tryCatch.throwNew(FF_NEW_STRING("Imgproc::CalcHist - expected ranges to be an array"));
	}
	v8::Local<v8::Array> jsRanges = v8::Local<v8::Array>::Cast(jsRangesVal);
	if (jsRanges->Length() != 2) {
		return tryCatch.throwNew(FF_NEW_STRING("Imgproc::CalcHist - expected ranges to be an array of length 2"));
	}
    ranges.at(i)[0] = jsRanges->Get(0)->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    ranges.at(i)[1] = jsRanges->Get(1)->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    int channel, bins;

	if (IntConverter::prop(&channel, "channel", jsAxis) || IntConverter::prop(&bins, "bins", jsAxis)) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Imgproc::CalcHist"));
		return;
	}
    channels[i] = channel;
    histSize[i] = bins;
  }

  cv::MatND hist;
  if (dims == 1) {
    hist = calcHist1(inputImg, mask, channels, histSize, ranges);
  }
  else if (dims == 2) {
    hist = calcHist2(inputImg, mask, channels, histSize, ranges);
  }
  else if (dims == 3) {
    hist = calcHist3(inputImg, mask, channels, histSize, ranges);
  }
  else if (dims == 4) {
    hist = calcHist4(inputImg, mask, channels, histSize, ranges);
  }

  for (int i = 0; i < dims; ++i) {
    delete[] ranges.at(i);
  }
  delete[] channels;
  delete[] histSize;

  v8::Local<v8::Object> jsMat = FF::newInstance(Nan::New(Mat::constructor));
  int outputType = CV_MAKETYPE(CV_64F, img.channels());
  if (outputType != hist.type()) {
    hist.convertTo(hist, outputType);
  }

  FF_UNWRAP_MAT_AND_GET(jsMat) = hist;
  info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Imgproc::Plot1DHist) {
	FF::TryCatch tryCatch;

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
			FF::isArgObject(info, 3) && (
				IntConverter::optProp(&lineType, "lineType", opts) ||
				IntConverter::optProp(&thickness, "thickness", opts) ||
				IntConverter::optProp(&shift, "shift", opts)
			) || (
				IntConverter::optArg(3, &lineType, info) ||
				IntConverter::optArg(4, &thickness, info) ||
				IntConverter::optArg(5, &shift, info)
			)
		)
	){
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("Imgproc::Plot1DHist");
		tryCatch.throwNew(err);
		return;
	}

	if (1 != hist.cols) {
		return Nan::ThrowError(FF_NEW_STRING("Imgproc::Plot1DHist - hist rows mismatch, expected "
			+ std::to_string(1) + ", have " + std::to_string(hist.cols)));
	}
	if (hist.channels() != 1) {
		return Nan::ThrowError(FF_NEW_STRING("Imgproc::Plot1DHist - expected hist to be single channeled"));
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

  v8::Local<v8::Object> jsMat = FF::newInstance(Nan::New(Mat::constructor));
  FF_UNWRAP_MAT_AND_GET(jsMat) = plot;
  info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Imgproc::FitLine) {
  FF_METHOD_CONTEXT("FitLine");

  if (!info[0]->IsArray()) {
	  FF_THROW("expected arg 0 to be an array");
  }
  v8::Local<v8::Array> jsPoints = v8::Local<v8::Array>::Cast(info[0]);

  if (jsPoints->Length() < 2) {
    FF_THROW("expected arg0 to be an Array with atleast 2 Points");
  }
  v8::Local<v8::Value> jsPt1 = jsPoints->Get(0);
  bool isPoint2 = FF_IS_INSTANCE(Point2::constructor, jsPt1);
  bool isPoint3 = FF_IS_INSTANCE(Point3::constructor, jsPt1);
  if (!isPoint2 && !isPoint3) {
    FF_THROW("expected arg0 to be an Array containing instances of Point2 or Point3");
  }

  FF::TryCatch tryCatch;

  std::vector<cv::Point2d> pts2d;
  std::vector<cv::Point3d> pts3d;
  uint distType;
  double param, reps, aeps;
  if ((
	isPoint2 && ObjectArrayConverter<Point2, cv::Point2d>::arg(0, &pts2d, info) ||
	!isPoint2 && ObjectArrayConverter<Point3, cv::Point3d>::arg(0, &pts3d, info)
	) ||
	UintConverter::arg(1, &distType, info) ||
	DoubleConverter::arg(2, &param, info) ||
	DoubleConverter::arg(3, &reps, info) ||
	DoubleConverter::arg(4, &aeps, info)
	) {
	tryCatch.throwNew(tryCatch.formatCatchedError("Imgproc::FitLine"));
	return;
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
      jsLineParams->Set(i, Nan::New(lineParams[i]));
    }
	info.GetReturnValue().Set(jsLineParams);
  }
}

NAN_METHOD(Imgproc::GetTextSize) {
  FF::SyncBinding(
    std::make_shared<ImgprocBindings::GetTextSizeWorker>(),
    "Imgproc::GetTextSize",
    info
  );
}

NAN_METHOD(Imgproc::GetTextSizeAsync) {
  FF::AsyncBinding(
    std::make_shared<ImgprocBindings::GetTextSizeWorker>(),
    "Imgproc::GetTextSizeAsync",
    info
  );
}

NAN_METHOD(Imgproc::ApplyColorMap) {
  FF::SyncBinding(std::make_shared<ImgprocBindings::ApplyColorMapWorker>(),
                  "Imgproc::ApplyColorMap", info);
}

NAN_METHOD(Imgproc::ApplyColorMapAsync) {
  FF::AsyncBinding(std::make_shared<ImgprocBindings::ApplyColorMapWorker>(),
                   "Imgproc::ApplyColorMapAsync", info);
}

#if CV_VERSION_MINOR > 1

NAN_METHOD(Imgproc::Canny) {
	FF::SyncBinding(std::make_shared<ImgprocBindings::CannyWorker>(),
		"Imgproc::Canny", info);
}

NAN_METHOD(Imgproc::CannyAsync) {
	FF::AsyncBinding(std::make_shared<ImgprocBindings::CannyWorker>(),
		"Imgproc::CannyAsync", info);
}

#endif
