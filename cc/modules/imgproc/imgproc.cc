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
  Nan::SetMethod(target, "getTextSize", GetTextSize);
  Nan::SetMethod(target, "getTextSizeAsync", GetTextSizeAsync);
#if CV_VERSION_MINOR > 1
  Nan::SetMethod(target, "canny", Canny);
#endif
  Moments::Init(target);
  Contour::Init(target);
};

NAN_METHOD(Imgproc::GetStructuringElement) {
  FF_METHOD_CONTEXT("GetStructuringElement");

  FF_ARG_UINT(0, uint shape);
  FF_ARG_INSTANCE(1, cv::Size2d size, Size::constructor, FF_UNWRAP_SIZE_AND_GET);
  FF_ARG_INSTANCE_IFDEF(2, cv::Point2d anchor, Point2::constructor, FF_UNWRAP_PT2_AND_GET, cv::Point2d(-1, -1));

  FF_OBJ jsKernel = FF_NEW_INSTANCE(Mat::constructor);
  FF_UNWRAP_MAT_AND_GET(jsKernel) = cv::getStructuringElement(shape, size, anchor);
  FF_RETURN(jsKernel);
}

NAN_METHOD(Imgproc::GetRotationMatrix2D) {
  FF_METHOD_CONTEXT("GetRotationMatrix2D");

  FF_ARG_INSTANCE(0, cv::Point2d center, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
  FF_ARG_NUMBER(1, double angle);

  FF_ARG_NUMBER_IFDEF(2, double scale, 1.0);

  FF_OBJ jsRotationMat = FF_NEW_INSTANCE(Mat::constructor);
  FF_UNWRAP_MAT_AND_GET(jsRotationMat) = cv::getRotationMatrix2D(center, angle, scale);
  FF_RETURN(jsRotationMat);
}

NAN_METHOD(Imgproc::GetAffineTransform) {
  FF_METHOD_CONTEXT("GetAffineTransform");

  FF_ARG_ARRAY(0, FF_ARR jsSrcPoints);
  FF_ARG_ARRAY(1, FF_ARR jsDstPoints);

  // TODO FF_ARG_UNPACK_ARRAY_INSTANCE
  Nan::TryCatch tryCatch;
  std::vector<cv::Point2f> srcPoints, dstPoints;
  Point::unpackJSPoint2Array<float>(srcPoints, jsSrcPoints);
  Point::unpackJSPoint2Array<float>(dstPoints, jsDstPoints);
  if (tryCatch.HasCaught()) {
    return info.GetReturnValue().Set(tryCatch.ReThrow());
  }

  FF_OBJ jsMat = FF_NEW_INSTANCE(Mat::constructor);
  FF_UNWRAP_MAT_AND_GET(jsMat) = cv::getAffineTransform(srcPoints, dstPoints);
  FF_RETURN(jsMat);
}

NAN_METHOD(Imgproc::GetPerspectiveTransform) {
  FF_METHOD_CONTEXT("GetPerspectiveTransform");

  FF_ARG_ARRAY(0, FF_ARR jsSrcPoints);
  FF_ARG_ARRAY(1, FF_ARR jsDstPoints);

  // TODO FF_ARG_UNPACK_ARRAY_INSTANCE
  Nan::TryCatch tryCatch;
  std::vector<cv::Point2f> srcPoints, dstPoints;
  Point::unpackJSPoint2Array<float>(srcPoints, jsSrcPoints);
  Point::unpackJSPoint2Array<float>(dstPoints, jsDstPoints);
  if (tryCatch.HasCaught()) {
    return info.GetReturnValue().Set(tryCatch.ReThrow());
  }

  FF_OBJ jsMat = FF_NEW_INSTANCE(Mat::constructor);
  FF_UNWRAP_MAT_AND_GET(jsMat) = cv::getPerspectiveTransform(srcPoints, dstPoints);
  FF_RETURN(jsMat);
}

NAN_METHOD(Imgproc::CalcHist) {
  FF_METHOD_CONTEXT("CalcHist");

  FF_ARG_INSTANCE(0, cv::Mat img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
  FF_ARG_ARRAY(1, FF_ARR jsHistAxes);
  FF_ARG_INSTANCE_IFDEF(2, cv::Mat mask, Mat::constructor, FF_UNWRAP_MAT_AND_GET, cv::noArray().getMat());

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
    FF_OBJ jsAxis = FF_CAST_OBJ(jsHistAxes->Get(i));
    FF_ARR jsRanges;
	FF_GET_ARRAY_REQUIRED(jsAxis, jsRanges, "ranges");
	if (jsRanges->Length() != 2) {
		return Nan::ThrowError(FF_NEW_STRING("expected ranges to be an array of length " + std::to_string(2)));
	}
    ranges.at(i)[0] = jsRanges->Get(0)->NumberValue();
    ranges.at(i)[1] = jsRanges->Get(1)->NumberValue();
    int channel, bins;
    FF_DESTRUCTURE_JSPROP_REQUIRED(jsAxis, channel, IntegerValue);
    FF_DESTRUCTURE_JSPROP_REQUIRED(jsAxis, bins, IntegerValue);
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

  FF_OBJ jsMat = FF_NEW_INSTANCE(Mat::constructor);
  int outputType = CV_MAKETYPE(CV_64F, img.channels());
  if (outputType != hist.type()) {
    hist.convertTo(hist, outputType);
  }

  FF_UNWRAP_MAT_AND_GET(jsMat) = hist;
  FF_RETURN(jsMat);
}

NAN_METHOD(Imgproc::Plot1DHist) {
  FF_METHOD_CONTEXT("Plot1DHist");

  FF_ARG_INSTANCE(0, cv::Mat hist, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
  FF_ARG_INSTANCE(1, cv::Mat plot, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
  FF_ARG_INSTANCE(2, cv::Vec3d color, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);											
  if (1 != hist.cols) {																													
	return Nan::ThrowError(FF_NEW_STRING("Plot1DHist - hist rows mismatch, expected "	
	  + std::to_string(1) + ", have " + std::to_string(hist.cols)));		
  }
  if (hist.channels() != 1) {
    FF_THROW("expected hist to be single channeled");
  }

  // optional args
  bool hasOptArgsObj = FF_HAS_ARG(3) && info[3]->IsObject();
  FF_OBJ optArgs = hasOptArgsObj ? info[3]->ToObject() : FF_NEW_OBJ();
  FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
  FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 2);
  FF_GET_INT_IFDEF(optArgs, int shift, "shift", 0);
  if (!hasOptArgsObj) {
    FF_ARG_INT_IFDEF(3, lineType, lineType);
    FF_ARG_INT_IFDEF(4, thickness, thickness);
    FF_ARG_INT_IFDEF(5, shift, shift);
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

  FF_OBJ jsMat = FF_NEW_INSTANCE(Mat::constructor);
  FF_UNWRAP_MAT_AND_GET(jsMat) = plot;
  FF_RETURN(jsMat);
}

NAN_METHOD(Imgproc::FitLine) {
  FF_METHOD_CONTEXT("FitLine");

  FF_ARG_ARRAY(0, FF_ARR jsPoints);
  if (jsPoints->Length() < 2) {
    FF_THROW("expected arg0 to be an Array with atleast 2 Points");
  }
  FF_VAL jsPt1 = jsPoints->Get(0);
  bool isPoint2 = FF_IS_INSTANCE(Point2::constructor, jsPt1);
  bool isPoint3 = FF_IS_INSTANCE(Point3::constructor, jsPt1);
  if (!isPoint2 && !isPoint3) {
    FF_THROW("expected arg0 to be an Array containing instances of Point2 or Point3");
  }

  FF_ARG_UINT(1, uint distType);
  FF_ARG_NUMBER(2, double param);
  FF_ARG_NUMBER(3, double reps);
  FF_ARG_NUMBER(4, double aeps);

  FF_ARR jsLineParams;
  if (isPoint2) {
    std::vector<cv::Point2d> pts;
    Point::unpackJSPoint2Array(pts, jsPoints);
    cv::Vec4f lineParams;
    cv::fitLine(pts, lineParams, (int)distType, param, reps, aeps);
    jsLineParams = FF_NEW_ARRAY(4);
    for (int i = 0; i < 4; i++) {
      jsLineParams->Set(i, Nan::New(lineParams[i]));
    }
  }
  else {
    std::vector<cv::Point3d> pts;
    Point::unpackJSPoint3Array(pts, jsPoints);
    cv::Vec6f lineParams;
    cv::fitLine(pts, lineParams, (int)distType, param, reps, aeps);
    jsLineParams = FF_NEW_ARRAY(6);
    for (int i = 0; i < 6; i++) {
      jsLineParams->Set(i, Nan::New(lineParams[i]));
    }
  }
  FF_RETURN(jsLineParams);
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

#if CV_VERSION_MINOR > 1
NAN_METHOD(Imgproc::Canny) {
	FF_METHOD_CONTEXT("Canny");

	FF_ARG_INSTANCE(0, cv::Mat dx, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Mat dy, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_NUMBER(2, double threshold1);
	FF_ARG_NUMBER(3, double threshold2);
	FF_ARG_BOOL_IFDEF(4, bool L2gradient, false);

	FF_OBJ jsMat = FF_NEW_INSTANCE(Mat::constructor);
	cv::Canny(dx, dy, FF_UNWRAP_MAT_AND_GET(jsMat), threshold1, threshold2, L2gradient);

	FF_RETURN(jsMat);
}
#endif
