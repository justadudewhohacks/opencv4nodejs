#include "MatImgproc.h"
#include "imgproc/Moments.h"
#include "imgproc/Contour.h"
#include "TermCriteria.h"

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

struct MatImgproc::BaseResizeWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	BaseResizeWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat dst;

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(dst);
	}
};

struct MatImgproc::RescaleWorker : public BaseResizeWorker {
public:
	RescaleWorker(cv::Mat self) : BaseResizeWorker(self) {
	}

	double factor;

	std::string executeCatchCvExceptionWorker() {
		cv::resize(self, dst, cv::Size(), factor, factor);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::arg(0, &factor, info)
		);
	}
};

NAN_METHOD(MatImgproc::Rescale) {
	RescaleWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Rescale", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::RescaleAsync) {
	RescaleWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::RescaleAsync", RescaleWorker, worker);
}

struct MatImgproc::ResizeWorker : BaseResizeWorker {
public:
	ResizeWorker(cv::Mat self) : BaseResizeWorker(self) {
	}

	int rows;
	int cols;
	cv::Size2d dsize;
	double fx = 0;
	double fy = 0;
	int interpolation = cv::INTER_LINEAR;

	std::string executeCatchCvExceptionWorker() {
		cv::resize(self, dst, dsize, fx, fy, interpolation);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		if (hasDsize(info)) {
			return Size::Converter::arg(0, &dsize, info);
		}
		bool didThrow = IntConverter::arg(0, &rows, info)
			|| IntConverter::arg(1, &cols, info);
		dsize = cv::Size2d(cols, rows);
		return didThrow;
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		int o = hasDsize(info) ? 0 : 1;
		return (
			DoubleConverter::optArg(1 + o, &fx, info) ||
			DoubleConverter::optArg(2 + o, &fy, info) ||
			IntConverter::optArg(3 + o, &interpolation, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(getOptArgIndex(info));
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[getOptArgIndex(info)]->ToObject();
		return (
			DoubleConverter::optProp(&fx, "fx", opts) ||
			DoubleConverter::optProp(&fy, "fy", opts) ||
			IntConverter::optProp(&interpolation, "interpolation", opts)
		);
	}

	bool hasDsize(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (Size::Converter::hasInstance(info[0]));
	}

	int getOptArgIndex(Nan::NAN_METHOD_ARGS_TYPE info) {
		return hasDsize(info) ? 1 : 2;
	}
};

NAN_METHOD(MatImgproc::Resize) {
	ResizeWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Resize", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::ResizeAsync) {
	ResizeWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::ResizeAsync", ResizeWorker, worker);
}

struct MatImgproc::ResizeToMaxWorker : BaseResizeWorker {
public:
	ResizeToMaxWorker(cv::Mat self) : BaseResizeWorker(self) {
	}

	int maxRowsOrCols;

	std::string executeCatchCvExceptionWorker() {
		double ratioY = (double)maxRowsOrCols / (double)self.rows;
		double ratioX = (double)maxRowsOrCols / (double)self.cols;
		double scale = (std::min)(ratioY, ratioX);
		cv::resize(self, dst, cv::Size((int)(self.cols * scale), (int)(self.rows * scale)));
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &maxRowsOrCols, info)
		);
	}
};

NAN_METHOD(MatImgproc::ResizeToMax) {
	ResizeToMaxWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::ResizeToMax", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::ResizeToMaxAsync) {
	ResizeToMaxWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::ResizeToMaxAsync", ResizeToMaxWorker, worker);
}

struct MatImgproc::ThresholdWorker : CatchCvExceptionWorker {
public:
	cv::Mat mat;

	ThresholdWorker(cv::Mat mat) {
		this->mat = mat;
	}

	double thresh;
	double maxVal;
	uint type;

	cv::Mat thresholdMat;

	std::string executeCatchCvExceptionWorker() {
		cv::threshold(mat, thresholdMat, thresh, maxVal, (int)type);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(thresholdMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::arg(0, &thresh, info) ||
			DoubleConverter::arg(1, &maxVal, info) ||
			UintConverter::arg(2, &type, info)
		);
	}
};

NAN_METHOD(MatImgproc::Threshold) {
	ThresholdWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Threshold", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::ThresholdAsync) {
	ThresholdWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::ThresholdAsync", ThresholdWorker, worker);
}

struct MatImgproc::AdaptiveThresholdWorker : CatchCvExceptionWorker {
public:
	cv::Mat mat;

	AdaptiveThresholdWorker(cv::Mat mat) {
		this->mat = mat;
	}

	double maxVal;
	int adaptiveMethod;
	int thresholdType;
	int blockSize;
	double C;

	cv::Mat thresholdMat;

	std::string executeCatchCvExceptionWorker() {
		cv::adaptiveThreshold(mat, thresholdMat, maxVal, adaptiveMethod, thresholdType, blockSize, C);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(thresholdMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::arg(0, &maxVal, info) ||
			IntConverter::arg(1, &adaptiveMethod, info) ||
			IntConverter::arg(2, &thresholdType, info) ||
			IntConverter::arg(3, &blockSize, info) ||
			DoubleConverter::arg(4, &C, info)
		);
	}
};

NAN_METHOD(MatImgproc::AdaptiveThreshold) {
	AdaptiveThresholdWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::AdaptiveThreshold", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::AdaptiveThresholdAsync) {
	AdaptiveThresholdWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::AdaptiveThresholdAsync", AdaptiveThresholdWorker, worker);
}

struct MatImgproc::InRangeWorker : CatchCvExceptionWorker {
public:
	cv::Mat mat;

	InRangeWorker(cv::Mat mat) {
		this->mat = mat;
	}

	double lower;
	double upper;
	cv::Vec3d lowerVec;
	cv::Vec3d upperVec;

	cv::Mat inRangeMat;

	std::string executeCatchCvExceptionWorker() {
		if (mat.channels() == 3) {
			cv::inRange(mat, lowerVec, upperVec, inRangeMat);
		} else {
			cv::inRange(mat, lower, upper, inRangeMat);
		}
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(inRangeMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		if (mat.channels() == 3) {
			return (
				Vec3::Converter::arg(0, &lowerVec, info)
				|| Vec3::Converter::arg(1, &upperVec, info)
			);
		}
		return (
			DoubleConverter::arg(0, &lower, info)
			|| DoubleConverter::arg(1, &upper, info)
		);
	}
};

NAN_METHOD(MatImgproc::InRange) {
	InRangeWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::InRange", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::InRangeAsync) {
	InRangeWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::InRangeAsync", InRangeWorker, worker);
}


struct MatImgproc::CvtColorWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	CvtColorWorker(cv::Mat self) {
		this->self = self;
	}

	int code;
	int dstCn = 0;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		cv::cvtColor(self, dst, code, dstCn);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &code, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(1, &dstCn, info)
		);
	}
};

NAN_METHOD(MatImgproc::CvtColor) {
	CvtColorWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::CvtColor", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::CvtColorAsync) {
	CvtColorWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::CvtColorAsync", CvtColorWorker, worker);
}


struct MatImgproc::BgrToGrayWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	BgrToGrayWorker(cv::Mat self) {
		this->self = self;
	}

	int code;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		cv::cvtColor(self, dst, CV_BGR2GRAY);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}
};

NAN_METHOD(MatImgproc::BgrToGray) {
	BgrToGrayWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::BgrToGray", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::BgrToGrayAsync) {
	BgrToGrayWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::BgrToGrayAsync", BgrToGrayWorker, worker);
}

struct MatImgproc::WarpWorker: public CatchCvExceptionWorker {
public:
	cv::Mat mat;

	WarpWorker(cv::Mat mat) {
		this->mat = mat;
		this->size = cv::Size2d(mat.cols, mat.rows);
	}

	cv::Mat transformationMatrix;
	cv::Size2d size;
	int flags = cv::INTER_LINEAR;
	int borderMode = cv::BORDER_CONSTANT;

	cv::Mat warpedMat;

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(warpedMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Mat::Converter::arg(0, &transformationMatrix, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Size::Converter::optArg(1, &size, info) ||
			IntConverter::optArg(2, &flags, info) ||
			IntConverter::optArg(3, &borderMode, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1) && !Size::Converter::hasInstance(info[1]->ToObject());
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[1]->ToObject();
		return (
			Size::Converter::optProp(&size, "size", opts) ||
			IntConverter::optProp(&flags, "flags", opts) ||
			IntConverter::optProp(&borderMode, "borderMode", opts)
		);
	}
};

struct MatImgproc::WarpAffineWorker : public WarpWorker {
	WarpAffineWorker(cv::Mat mat) : WarpWorker(mat) {
	}

	std::string executeCatchCvExceptionWorker() {
		cv::warpAffine(mat, warpedMat, transformationMatrix, (cv::Size)size, flags, borderMode, cv::Scalar());
		return "";
	}
};

NAN_METHOD(MatImgproc::WarpAffine) {
	WarpAffineWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::WarpAffine", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::WarpAffineAsync) {
	WarpAffineWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::WarpAffineAsync", WarpAffineWorker, worker);
}

struct MatImgproc::WarpPerspectiveWorker : public WarpWorker {
	WarpPerspectiveWorker(cv::Mat mat) : WarpWorker(mat) {
	}

	std::string executeCatchCvExceptionWorker() {
		cv::warpPerspective(mat, warpedMat, transformationMatrix, (cv::Size)size, flags, borderMode, cv::Scalar());
		return "";
	}
};

NAN_METHOD(MatImgproc::WarpPerspective) {
	WarpPerspectiveWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::WarpPerspective", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::WarpPerspectiveAsync) {
	WarpPerspectiveWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::WarpPerspectiveAsync", WarpPerspectiveWorker, worker);
}


struct MatImgproc::MorphWorker: public CatchCvExceptionWorker {
public:
	cv::Mat mat;
	bool withOp;

	MorphWorker(cv::Mat mat, bool withOp = false) {
		this->mat = mat;
		this->withOp = withOp;
	}

	cv::Mat kernel;

	int op;
	cv::Point2d anchor = cv::Point2d(-1, -1);
	int iterations = 1;
	int borderType = cv::BORDER_CONSTANT;

	cv::Mat resultMat;

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(resultMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &kernel, info) ||
			(withOp && IntConverter::optArg(1, &op, info))
			);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		int off = (withOp ? 1 : 0);
		return (
			Point2::Converter::optArg(1 + off, &anchor, info) ||
			IntConverter::optArg(2 + off, &iterations, info) ||
			IntConverter::optArg(3 + off, &borderType, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		int optArgN = (withOp ? 2 : 1);
		return FF_ARG_IS_OBJECT(optArgN) && !Point2::Converter::hasInstance(info[optArgN]->ToObject());
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		int optArgN = (withOp ? 2 : 1);
		FF_OBJ opts = info[optArgN]->ToObject();
		return (
			Point2::Converter::optProp(&anchor, "anchor", opts) ||
			IntConverter::optProp(&iterations, "iterations", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
		);
	}
};

struct MatImgproc::ErodeWorker : public MorphWorker {
	ErodeWorker(cv::Mat mat) : MorphWorker(mat) {
	}

	std::string executeCatchCvExceptionWorker() {
		cv::erode(mat, resultMat, kernel, anchor, iterations, borderType, cv::morphologyDefaultBorderValue());
		return "";
	}
};

NAN_METHOD(MatImgproc::Erode) {
	ErodeWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Erode", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::ErodeAsync) {
	ErodeWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::ErodeAsync", ErodeWorker, worker);
}


struct MatImgproc::DilateWorker : public MorphWorker {
	DilateWorker(cv::Mat mat) : MorphWorker(mat) {
	}

	std::string executeCatchCvExceptionWorker() {
		cv::dilate(mat, resultMat, kernel, anchor, iterations, borderType, cv::morphologyDefaultBorderValue());
		return "";
	}
};

NAN_METHOD(MatImgproc::Dilate) {
	DilateWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Dilate", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::DilateAsync) {
	DilateWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::DilateAsync", DilateWorker, worker);
}


struct MatImgproc::MorphologyExWorker : public MorphWorker {
public:
	MorphologyExWorker(cv::Mat mat) : MorphWorker(mat, true) {
	}

	std::string executeCatchCvExceptionWorker() {
		cv::morphologyEx(mat, resultMat, op, kernel, anchor, iterations, borderType, cv::morphologyDefaultBorderValue());
		return "";
	}
};

NAN_METHOD(MatImgproc::MorphologyEx) {
	MorphologyExWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::MorphologyEx", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::MorphologyExAsync) {
	MorphologyExWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::MorphologyExAsync", MorphologyExWorker, worker);
}

struct MatImgproc::DistanceTransformWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	DistanceTransformWorker(cv::Mat self) {
		this->self = self;
	}

	int distanceType;
	int maskSize;
	int dstType = CV_32F;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		cv::distanceTransform(self, dst, distanceType, maskSize, dstType);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &distanceType, info) ||
			IntConverter::arg(1, &maskSize, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(2, &dstType, info)
		);
	}
};

NAN_METHOD(MatImgproc::DistanceTransform) {
	DistanceTransformWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DistanceTransform", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::DistanceTransformAsync) {
	DistanceTransformWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::DistanceTransformAsync", DistanceTransformWorker, worker);
}

struct MatImgproc::DistanceTransformWithLabelsWorker : public DistanceTransformWorker {
	DistanceTransformWithLabelsWorker(cv::Mat self) : DistanceTransformWorker(self) {
	}

	int labelType = cv::DIST_LABEL_CCOMP;
	cv::Mat labels;

	std::string executeCatchCvExceptionWorker() {
		cv::distanceTransform(self, dst, labels, distanceType, maskSize, labelType);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("dst").ToLocalChecked(), Mat::Converter::wrap(dst));
		Nan::Set(ret, Nan::New("labels").ToLocalChecked(), Mat::Converter::wrap(labels));
		return ret;
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(2, &labelType, info)
		);
	}
};

NAN_METHOD(MatImgproc::DistanceTransformWithLabels) {
	DistanceTransformWithLabelsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DistanceTransformWithLabels", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::DistanceTransformWithLabelsAsync) {
	DistanceTransformWithLabelsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::DistanceTransformWithLabelsAsync", DistanceTransformWithLabelsWorker, worker);
}


struct MatImgproc::BlurWorker: public CatchCvExceptionWorker {
public:
	cv::Mat mat;

	BlurWorker(cv::Mat mat) {
		this->mat = mat;
	}

	cv::Size2d kSize;
	cv::Point2d anchor = cv::Point2d(-1, -1);
	int borderType = cv::BORDER_CONSTANT;

	cv::Mat blurMat;

	std::string executeCatchCvExceptionWorker() {
		cv::blur(mat, blurMat, kSize, anchor, borderType);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(blurMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Size::Converter::arg(0, &kSize, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Point2::Converter::optArg(1, &anchor, info) ||
			IntConverter::optArg(2, &borderType, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1) && !Point2::Converter::hasInstance(info[1]->ToObject());
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[1]->ToObject();
		return (
			Point2::Converter::optProp(&anchor, "anchor", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
		);
	}
};

NAN_METHOD(MatImgproc::Blur) {
	BlurWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Blur", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::BlurAsync) {
	BlurWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::BlurAsync", BlurWorker, worker);
}


struct MatImgproc::GaussianBlurWorker: public CatchCvExceptionWorker {
public:
	cv::Mat mat;

	GaussianBlurWorker(cv::Mat mat) {
		this->mat = mat;
	}

	cv::Size2d kSize;
	double sigmaX;
	double sigmaY = 0;
	int borderType = cv::BORDER_CONSTANT;

	cv::Mat blurMat;

	std::string executeCatchCvExceptionWorker() {
		cv::GaussianBlur(mat, blurMat, kSize, sigmaX, sigmaY, borderType);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(blurMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Size::Converter::arg(0, &kSize, info) ||
			DoubleConverter::arg(1, &sigmaX, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(2, &sigmaY, info) ||
			IntConverter::optArg(3, &borderType, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(2);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[2]->ToObject();
		return (
			DoubleConverter::optProp(&sigmaY, "sigmaY", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
		);
	}
};

NAN_METHOD(MatImgproc::GaussianBlur) {
	GaussianBlurWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::GaussianBlur", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::GaussianBlurAsync) {
	GaussianBlurWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::GaussianBlurAsync", GaussianBlurWorker, worker);
}


struct MatImgproc::MedianBlurWorker : public CatchCvExceptionWorker {
public:
	cv::Mat mat;

	MedianBlurWorker(cv::Mat mat) {
		this->mat = mat;
	}

	int kSize;

	cv::Mat blurMat;

	std::string executeCatchCvExceptionWorker() {
		cv::medianBlur(mat, blurMat, kSize);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(blurMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return IntConverter::arg(0, &kSize, info);
	}
};

NAN_METHOD(MatImgproc::MedianBlur) {
	MedianBlurWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::MedianBlur", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::MedianBlurAsync) {
	MedianBlurWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::MedianBlurAsync", MedianBlurWorker, worker);
}


struct MatImgproc::ConnectedComponentsWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	ConnectedComponentsWorker(cv::Mat self) {
		this->self = self;
	}

	int connectivity = 8;
	int ltype = CV_32S;

	cv::Mat labels;

	std::string executeCatchCvExceptionWorker() {
		cv::connectedComponents(self, labels, connectivity, ltype);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(labels);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(0, &connectivity, info) ||
			IntConverter::optArg(1, &ltype, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(0);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[0]->ToObject();
		return (
			IntConverter::optProp(&connectivity, "connectivity", opts) ||
			IntConverter::optProp(&ltype, "ltype", opts)
		);
	}
};

NAN_METHOD(MatImgproc::ConnectedComponents) {
	ConnectedComponentsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::ConnectedComponents", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::ConnectedComponentsAsync) {
	ConnectedComponentsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::ConnectedComponentsAsync", ConnectedComponentsWorker, worker);
}


struct MatImgproc::ConnectedComponentsWithStatsWorker : public ConnectedComponentsWorker {
	ConnectedComponentsWithStatsWorker(cv::Mat self) : ConnectedComponentsWorker(self) {
	}

	cv::Mat stats;
	cv::Mat centroids;

	std::string executeCatchCvExceptionWorker() {
		cv::connectedComponentsWithStats(self, labels, stats, centroids, connectivity, ltype);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("labels").ToLocalChecked(), Mat::Converter::wrap(labels));
		Nan::Set(ret, Nan::New("stats").ToLocalChecked(), Mat::Converter::wrap(stats));
		Nan::Set(ret, Nan::New("centroids").ToLocalChecked(), Mat::Converter::wrap(centroids));
		return ret;
	}
};

NAN_METHOD(MatImgproc::ConnectedComponentsWithStats) {
	ConnectedComponentsWithStatsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::ConnectedComponentsWithStats", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::ConnectedComponentsWithStatsAsync) {
	ConnectedComponentsWithStatsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::ConnectedComponentsWithStatsAsync", ConnectedComponentsWithStatsWorker, worker);
}


struct MatImgproc::GrabCutWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	GrabCutWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat mask;
	cv::Rect2d rect;
	cv::Mat bgdModel;
	cv::Mat fgdModel;
	int iterCount;
	int mode = cv::GC_EVAL;


	std::string executeCatchCvExceptionWorker() {
		cv::grabCut(self, mask, rect, bgdModel, fgdModel, iterCount, mode);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(self);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &mask, info) ||
			Rect::Converter::arg(1, &rect, info) ||
			Mat::Converter::arg(2, &bgdModel, info) ||
			Mat::Converter::arg(3, &fgdModel, info) ||
			IntConverter::arg(4, &iterCount, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(5, &mode, info)
		);
	}
};

NAN_METHOD(MatImgproc::GrabCut) {
	GrabCutWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::GrabCut", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::GrabCutAsync) {
	GrabCutWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::GrabCutAsync", GrabCutWorker, worker);
}


struct MatImgproc::WatershedWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	WatershedWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat markers;

	std::string executeCatchCvExceptionWorker() {
		cv::watershed(self, markers);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(markers);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &markers, info)
		);
	}
};

NAN_METHOD(MatImgproc::Watershed) {
	WatershedWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Watershed", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::WatershedAsync) {
	WatershedWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::WatershedAsync", WatershedWorker, worker);
}

struct MatImgproc::MomentsWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	MomentsWorker(cv::Mat self) {
		this->self = self;
	}

	bool binaryImage = false;

	cv::Moments returnValue;

	std::string executeCatchCvExceptionWorker() {
		cv::moments(self, binaryImage);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Moments::Converter::wrap(returnValue);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			BoolConverter::optArg(0, &binaryImage, info)
		);
	}
};

NAN_METHOD(MatImgproc::_Moments) {
	MomentsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Moments", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::_MomentsAsync) {
	MomentsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::MomentsAsync", MomentsWorker, worker);
}

struct MatImgproc::FindContoursWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	FindContoursWorker(cv::Mat self) {
		this->self = self;
	}

	int mode;
	int method;
	cv::Point2d offset = cv::Point2d();

	std::vector<cv::Mat> contours;
	std::vector<cv::Vec4i> hierarchy;

	std::string executeCatchCvExceptionWorker() {
		cv::findContours(self, contours, hierarchy, mode, method, offset);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Array> ret = Nan::New<v8::Array>(contours.size());
		for (uint i = 0; i < ret->Length(); i++) {
			FF_OBJ jsContour = FF_NEW_INSTANCE(Contour::constructor);
			FF_UNWRAP(jsContour, Contour)->contour = contours.at(i);
			FF_UNWRAP(jsContour, Contour)->hierarchy = hierarchy.at(i);
			ret->Set(i, jsContour);
		}
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &mode, info) ||
			IntConverter::arg(1, &method, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Point2::Converter::optArg(2, &offset, info)
		);
	}
};

NAN_METHOD(MatImgproc::FindContours) {
	FindContoursWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::FindContours", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::FindContoursAsync) {
	FindContoursWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::FindContoursAsync", FindContoursWorker, worker);
}

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

struct MatImgproc::DrawWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	bool hasThickness;

	DrawWorker(cv::Mat self, bool hasThickness = true) {
		this->self = self;
		this->hasThickness = hasThickness;
	}

	cv::Vec3d color = cv::Vec3d(0, 0, 0);
	int thickness = 1;
	int lineType = cv::LINE_8;
	int shift = 0;

	virtual int getDrawParamsIndex() = 0;

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		return ret;
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		int idx = getDrawParamsIndex();
		int off = hasThickness ? 1 : 0;
		return (
			Vec3::Converter::optArg(idx, &color, info) ||
			(hasThickness && IntConverter::optArg(idx + 1, &thickness, info)) ||
			IntConverter::optArg(idx + off + 1, &lineType, info) ||
			IntConverter::optArg(idx + off + 2, &shift, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(getDrawParamsIndex())
			&& !Vec3::Converter::hasInstance(info[getDrawParamsIndex()]);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[getDrawParamsIndex()]->ToObject();
		return (
			Vec3::Converter::optProp(&color, "color", opts) ||
			(hasThickness && IntConverter::optProp(&thickness, "thickness", opts)) ||
			IntConverter::optProp(&lineType, "lineType", opts) ||
			IntConverter::optProp(&shift, "shift", opts)
		);
	}
};

struct MatImgproc::DrawLineWorker : public MatImgproc::DrawWorker {
	DrawLineWorker(cv::Mat self) : DrawWorker(self) {
	}

	cv::Point2d pt1;
	cv::Point2d pt2;

	std::string executeCatchCvExceptionWorker() {
		cv::line(self, pt1, pt2, color, thickness, lineType, shift);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Point2::Converter::arg(0, &pt1, info) ||
			Point2::Converter::arg(1, &pt2, info)
		);
	}

	int getDrawParamsIndex() {
		return 2;
	}
};

NAN_METHOD(MatImgproc::DrawLine) {
	DrawLineWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DrawLine", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

struct MatImgproc::DrawArrowedLineWorker : public MatImgproc::DrawWorker {
	DrawArrowedLineWorker(cv::Mat self) : DrawWorker(self) {
	}

	cv::Point2d pt1;
	cv::Point2d pt2;
	double tipLength = 0.1;

	std::string executeCatchCvExceptionWorker() {
		cv::line(self, pt1, pt2, color, thickness, lineType, shift);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Point2::Converter::arg(0, &pt1, info) ||
			Point2::Converter::arg(1, &pt2, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DrawWorker::unwrapOptionalArgs(info) ||
			DoubleConverter::optArg(6, &tipLength, info)
		);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DrawWorker::unwrapOptionalArgsFromOpts(info) ||
			DoubleConverter::optProp(&tipLength, "tipLength", info[getDrawParamsIndex()]->ToObject())
		);
	}

	int getDrawParamsIndex() {
		return 2;
	}
};

NAN_METHOD(MatImgproc::DrawArrowedLine) {
	DrawArrowedLineWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DrawArrowedLine", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

struct MatImgproc::DrawRectangleWorker : public MatImgproc::DrawWorker {
	DrawRectangleWorker(cv::Mat self) : DrawWorker(self) {
	}

	cv::Point2d pt1;
	cv::Point2d pt2;
	cv::Rect2d rect;

	bool isArgRect = false;

	std::string executeCatchCvExceptionWorker() {
		if (isArgRect) {
			cv::rectangle(self, rect, color, thickness, lineType, shift);
		}
		else {
			cv::rectangle(self, pt1, pt2, color, thickness, lineType, shift);
		}
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		isArgRect = Rect::Converter::hasInstance(info[0]);
		return (
			(
				!isArgRect && (
					Point2::Converter::arg(0, &pt1, info) ||
					Point2::Converter::arg(1, &pt2, info)
				)
			) || (isArgRect && Rect::Converter::arg(0, &rect, info))

		);
	}

	int getDrawParamsIndex() {
		return isArgRect ? 1 : 2;
	}
};

NAN_METHOD(MatImgproc::DrawRectangle) {
	DrawRectangleWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DrawRectangle", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

struct MatImgproc::DrawCircleWorker : public MatImgproc::DrawWorker {
	DrawCircleWorker(cv::Mat self) : DrawWorker(self) {
	}

	cv::Point2d center;
	double radius;

	std::string executeCatchCvExceptionWorker() {
		cv::circle(self, center, radius, color, thickness, lineType, shift);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Point2::Converter::arg(0, &center, info) ||
			DoubleConverter::arg(1, &radius, info)
		);
	}

	int getDrawParamsIndex() {
		return 2;
	}
};

NAN_METHOD(MatImgproc::DrawCircle) {
	DrawCircleWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DrawCircle", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

struct MatImgproc::DrawEllipseWorker : public MatImgproc::DrawWorker {
	DrawEllipseWorker(cv::Mat self) : DrawWorker(self) {
	}

	cv::RotatedRect box;

	cv::Point2d center;
	cv::Size2d axes;
	double angle;
	double startAngle;
	double endAngle;

	bool isArgBox = false;

	std::string executeCatchCvExceptionWorker() {
		if (isArgBox) {
			cv::ellipse(self, box, color, thickness, lineType);
		}
		else {
			cv::ellipse(self, center, axes, angle, startAngle, endAngle, color, thickness, lineType, shift);
		}
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		isArgBox = RotatedRect::Converter::hasInstance(info[0]);
		return (
			(
				!isArgBox && (
					Point2::Converter::arg(0, &center, info) ||
					Size::Converter::arg(1, &axes, info) ||
					DoubleConverter::arg(2, &angle, info) ||
					DoubleConverter::arg(3, &startAngle, info) ||
					DoubleConverter::arg(4, &endAngle, info)
				)
			) || (isArgBox && RotatedRect::Converter::arg(0, &box, info))
		);
	}

	int getDrawParamsIndex() {
		return isArgBox ? 1 : 5;
	}
};

NAN_METHOD(MatImgproc::DrawEllipse) {
	DrawEllipseWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DrawEllipse", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

struct MatImgproc::DrawPolylinesWorker : public MatImgproc::DrawWorker {
	DrawPolylinesWorker(cv::Mat self) : DrawWorker(self) {
	}

	std::vector<std::vector<cv::Point2i>> pts;
	bool isClosed;

	std::string executeCatchCvExceptionWorker() {
		cv::polylines(self, pts, isClosed, color, thickness, lineType, shift);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			ObjectArrayOfArraysConverter<Point2, cv::Point2d, cv::Point2i>::arg(0, &pts, info) ||
			BoolConverter::arg(1, &isClosed, info)
		);
	}

	int getDrawParamsIndex() {
		return 2;
	}
};

NAN_METHOD(MatImgproc::DrawPolylines) {
	DrawPolylinesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DrawPolylines", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

struct MatImgproc::DrawFillPolyWorker : public MatImgproc::DrawWorker {
	DrawFillPolyWorker(cv::Mat self) : DrawWorker(self, false) {
	}

	std::vector<std::vector<cv::Point2i>> pts;
	cv::Point2d offset = cv::Point2d();

	std::string executeCatchCvExceptionWorker() {
		cv::fillPoly(self, pts, color, lineType, shift, offset);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			ObjectArrayOfArraysConverter<Point2, cv::Point2d, cv::Point2i>::arg(0, &pts, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DrawWorker::unwrapOptionalArgs(info) ||
			Point2::Converter::optArg(4, &offset, info)
		);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DrawWorker::unwrapOptionalArgsFromOpts(info) ||
			Point2::Converter::optProp(&offset, "offset", info[getDrawParamsIndex()]->ToObject())
		);
	}

	int getDrawParamsIndex() {
		return 1;
	}
};

NAN_METHOD(MatImgproc::DrawFillPoly) {
	DrawFillPolyWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DrawFillPoly", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

struct MatImgproc::DrawFillConvexPolyWorker : public MatImgproc::DrawWorker {
	DrawFillConvexPolyWorker(cv::Mat self) : DrawWorker(self, false) {
	}

	std::vector<cv::Point2i> pts;

	std::string executeCatchCvExceptionWorker() {
		cv::fillConvexPoly(self, pts, color, lineType, shift);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2i>::arg(0, &pts, info)
		);
	}

	int getDrawParamsIndex() {
		return 1;
	}
};

NAN_METHOD(MatImgproc::DrawFillConvexPoly) {
	DrawFillConvexPolyWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DrawFillConvexPoly", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

struct MatImgproc::PutTextWorker : public MatImgproc::DrawWorker {
	PutTextWorker(cv::Mat self) : DrawWorker(self) {
	}

	std::string text;
	cv::Point2d org;
	int fontFace;
	double fontScale;
	bool bottomLeftOrigin = false;

	std::string executeCatchCvExceptionWorker() {
		cv::putText(self, text, org, fontFace, fontScale, color, thickness, lineType, bottomLeftOrigin);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			StringConverter::arg(0, &text, info) ||
			Point2::Converter::arg(1, &org, info) ||
			IntConverter::arg(2, &fontFace, info) ||
			DoubleConverter::arg(3, &fontScale, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DrawWorker::unwrapOptionalArgs(info) ||
			BoolConverter::optArg(8, &bottomLeftOrigin, info)
		);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DrawWorker::unwrapOptionalArgsFromOpts(info) ||
			BoolConverter::optProp(&bottomLeftOrigin, "bottomLeftOrigin", info[getDrawParamsIndex()]->ToObject())
		);
	}

	int getDrawParamsIndex() {
		return 4;
	}
};

NAN_METHOD(MatImgproc::PutText) {
	PutTextWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::PutText", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

struct MatImgproc::MatchTemplateWorker : CatchCvExceptionWorker {
public:
	cv::Mat mat;

	MatchTemplateWorker(cv::Mat mat) {
		this->mat = mat;
	}

	cv::Mat templ;
	int method;
	cv::Mat mask = cv::noArray().getMat();

	cv::Mat resultsMat;

	std::string executeCatchCvExceptionWorker() {
		cv::matchTemplate(mat, templ, resultsMat, method, mask);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(resultsMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &templ, info) ||
			IntConverter::arg(1, &method, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Mat::Converter::optArg(2, &mask, info);
	}
};

NAN_METHOD(MatImgproc::MatchTemplate) {
	MatchTemplateWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::MatchTemplate", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::MatchTemplateAsync) {
	MatchTemplateWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::MatchTemplateAsync", MatchTemplateWorker, worker);
}


struct MatImgproc::CannyWorker: public CatchCvExceptionWorker {
public:
	cv::Mat mat;

	CannyWorker(cv::Mat mat) {
		this->mat = mat;
	}

	double threshold1;
	double threshold2;
	int apertureSize = 3;
	bool L2gradient = false;

	cv::Mat cannyMat;

	std::string executeCatchCvExceptionWorker() {
		cv::Canny(mat, cannyMat, threshold1, threshold2, apertureSize, L2gradient);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(cannyMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::arg(0, &threshold1, info) ||
			DoubleConverter::arg(1, &threshold2, info)
			);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(2, &apertureSize, info) ||
			BoolConverter::optArg(3, &L2gradient, info)
			);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(2);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[2]->ToObject();
		return (
			IntConverter::optProp(&apertureSize, "apertureSize", opts) ||
			BoolConverter::optProp(&L2gradient, "L2gradient", opts)
		);
	}
};

NAN_METHOD(MatImgproc::Canny) {
	CannyWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Canny", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::CannyAsync) {
	CannyWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::CannyAsync", CannyWorker, worker);
}


struct MatImgproc::SobelScharrWorker: public CatchCvExceptionWorker {
public:
	cv::Mat mat;
	bool hasKsize;

	SobelScharrWorker(cv::Mat mat, bool hasKsize) {
		this->mat = mat;
		this->hasKsize = hasKsize;
	}

	int ddepth;
	int dx;
	int dy;
	int ksize = 3;
	double scale = 1.0;
	double delta = 0;
	int borderType = cv::BORDER_DEFAULT;

	cv::Mat resultMat;

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(resultMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &ddepth, info) ||
			IntConverter::arg(1, &dx, info) ||
			IntConverter::arg(2, &dy, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		int optArgIdx = hasKsize ? 3 : 2;
		return (
			(hasKsize && IntConverter::optArg(optArgIdx, &ksize, info)) ||
			DoubleConverter::optArg(optArgIdx + 1, &scale, info) ||
			DoubleConverter::optArg(optArgIdx + 2, &delta, info) ||
			IntConverter::optArg(optArgIdx + 3, &borderType, info)
			);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(3);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[3]->ToObject();
		return (
			(hasKsize && IntConverter::optProp(&ksize, "ksize", opts)) ||
			DoubleConverter::optProp(&scale, "scale", opts) ||
			DoubleConverter::optProp(&delta, "delta", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
			);
	}
};

struct MatImgproc::SobelWorker : SobelScharrWorker {
	SobelWorker(cv::Mat mat, bool hasKsize) : SobelScharrWorker(mat, hasKsize) {
	}

	std::string executeCatchCvExceptionWorker() {
		cv::Sobel(mat, resultMat, ddepth, dx, dy, ksize, scale, delta, borderType);
		return "";
	}
};

NAN_METHOD(MatImgproc::Sobel) {
	SobelWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_SYNC("Mat::Sobel", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::SobelAsync) {
	SobelWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_ASYNC("Mat::SobelAsync", SobelWorker, worker);
}

struct MatImgproc::ScharrWorker : SobelScharrWorker {
	ScharrWorker(cv::Mat mat, bool hasKsize) : SobelScharrWorker(mat, hasKsize) {
	}

	std::string executeCatchCvExceptionWorker() {
		cv::Scharr(mat, resultMat, ddepth, dx, dy, scale, delta, borderType);
		return "";
	}
};

NAN_METHOD(MatImgproc::Scharr) {
	ScharrWorker worker(Mat::Converter::unwrap(info.This()), false);
	FF_WORKER_SYNC("Mat::Scharr", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::ScharrAsync) {
	ScharrWorker worker(Mat::Converter::unwrap(info.This()), false);
	FF_WORKER_ASYNC("Mat::ScharrAsync", ScharrWorker, worker);
}


struct MatImgproc::LaplacianWorker: public CatchCvExceptionWorker {
public:
	cv::Mat mat;

	LaplacianWorker(cv::Mat mat) {
		this->mat = mat;
	}

	int ddepth;
	int ksize = 1;
	double scale = 1.0;
	double delta = 0;
	int borderType = cv::BORDER_DEFAULT;

	cv::Mat resultMat;

	std::string executeCatchCvExceptionWorker() {
		cv::Laplacian(mat, resultMat, ddepth, ksize, scale, delta, borderType);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(resultMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return IntConverter::arg(0, &ddepth, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(1, &ksize, info) ||
			DoubleConverter::optArg(2, &scale, info) ||
			DoubleConverter::optArg(3, &delta, info) ||
			IntConverter::optArg(4, &borderType, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[1]->ToObject();
		return (
			IntConverter::optProp(&ksize, "ksize", opts) ||
			DoubleConverter::optProp(&scale, "scale", opts) ||
			DoubleConverter::optProp(&delta, "delta", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
			);
	}
};


NAN_METHOD(MatImgproc::Laplacian) {
	LaplacianWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Laplacian", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::LaplacianAsync) {
	LaplacianWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::LaplacianAsync", LaplacianWorker, worker);
}


struct MatImgproc::PyrWorker: public CatchCvExceptionWorker {
public:
	cv::Mat mat;
	bool isUp;

	PyrWorker(cv::Mat mat, bool isUp = false) {
		this->mat = mat;
		this->isUp = isUp;
	}

	cv::Size2d size = cv::Size2d();
	int borderType = cv::BORDER_DEFAULT;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		if (isUp) {
			cv::pyrUp(mat, dst, size, borderType);
		}
		else {
			cv::pyrDown(mat, dst, size, borderType);
		}
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return false;
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Size::Converter::optArg(0, &size, info) ||
			IntConverter::optArg(1, &borderType, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(0);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[0]->ToObject();
		return (
			Size::Converter::optProp(&size, "size", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
		);
	}
};

NAN_METHOD(MatImgproc::PyrDown) {
	PyrWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::PyrDown", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::PyrDownAsync) {
	PyrWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::PyrDownAsync", PyrWorker, worker);
}

NAN_METHOD(MatImgproc::PyrUp) {
	PyrWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_SYNC("Mat::PyrUp", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::PyrUpAsync) {
	PyrWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_ASYNC("Mat::PyrUpAsync", PyrWorker, worker);
}

struct MatImgproc::BuildPyramidWorker : public CatchCvExceptionWorker {
public:
	cv::Mat mat;

	BuildPyramidWorker(cv::Mat mat) {
		this->mat = mat;
	}

	int maxlevel;
	int borderType = cv::BORDER_DEFAULT;

	std::vector<cv::Mat> dst;

	std::string executeCatchCvExceptionWorker() {
		cv::buildPyramid(mat, dst, maxlevel, borderType);
		return "";
	}

	FF_VAL getReturnValue() {
		return ObjectArrayConverter<Mat, cv::Mat>::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return IntConverter::arg(0, &maxlevel, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return IntConverter::optArg(1, &borderType, info);
	}
};

NAN_METHOD(MatImgproc::BuildPyramid) {
	BuildPyramidWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::BuildPyramid", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::BuildPyramidAsync) {
	BuildPyramidWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::BuildPyramidAsync", BuildPyramidWorker, worker);
}

struct MatImgproc::HoughLinesWorker: public CatchCvExceptionWorker {
public:
	cv::Mat mat;

	HoughLinesWorker(cv::Mat mat) {
		this->mat = mat;
	}

	double rho;
	double theta;
	int threshold;
	double srn = 0;
	double stn = 0;
	double min_theta = 0;
	double max_theta = CV_PI;

	std::vector<cv::Vec2f> lines;

	std::string executeCatchCvExceptionWorker() {
		cv::HoughLines(mat, lines, rho, theta, threshold, srn, stn, min_theta, max_theta);
		return "";
	}

	FF_VAL getReturnValue() {
		return ObjectArrayConverter<Vec2, cv::Vec2d, cv::Vec2f>::wrap(lines);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::arg(0, &rho, info) ||
			DoubleConverter::arg(1, &theta, info) ||
			IntConverter::arg(2, &threshold, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(3, &srn, info) ||
			DoubleConverter::optArg(4, &stn, info) ||
			DoubleConverter::optArg(5, &min_theta, info) ||
			DoubleConverter::optArg(6, &max_theta, info)
			);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(3);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[3]->ToObject();
		return (
			DoubleConverter::optProp(&srn, "srn", opts) ||
			DoubleConverter::optProp(&stn, "stn", opts) ||
			DoubleConverter::optProp(&min_theta, "min_theta", opts) ||
			DoubleConverter::optProp(&max_theta, "max_theta", opts)
		);
	}
};

NAN_METHOD(MatImgproc::HoughLines) {
	HoughLinesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::HoughLines", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::HoughLinesAsync) {
	HoughLinesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::HoughLinesAsync", HoughLinesWorker, worker);
}

struct MatImgproc::HoughLinesPWorker : public HoughLinesWorker {
public:
	HoughLinesPWorker(cv::Mat mat) : HoughLinesWorker(mat) {
	}

	double minLineLength = 0;
	double maxLineGap = 0;

	std::vector<cv::Vec4f> linesP;

	std::string executeCatchCvExceptionWorker() {
		cv::HoughLinesP(mat, linesP, rho, theta, threshold, minLineLength, maxLineGap);
		return "";
	}

	FF_VAL getReturnValue() {
		return ObjectArrayConverter<Vec4, cv::Vec4d, cv::Vec4f>::wrap(linesP);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(3, &minLineLength, info) ||
			DoubleConverter::optArg(4, &maxLineGap, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(3);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[3]->ToObject();
		return (
			DoubleConverter::optProp(&minLineLength, "minLineLength", opts) ||
			DoubleConverter::optProp(&maxLineGap, "maxLineGap", opts)
		);
	}
};

NAN_METHOD(MatImgproc::HoughLinesP) {
	HoughLinesPWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::HoughLinesP", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::HoughLinesPAsync) {
	HoughLinesPWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::HoughLinesPAsync", HoughLinesPWorker, worker);
}

struct MatImgproc::HoughCirclesWorker: public CatchCvExceptionWorker {
public:
	cv::Mat mat;

	HoughCirclesWorker(cv::Mat mat) {
		this->mat = mat;
	}

	int method;
	double dp;
	double minDist;
	double param1 = 100;
	double param2 = 100;
	int minRadius = 0;
	int maxRadius = 0;

	std::vector<cv::Vec3f> circles;

	std::string executeCatchCvExceptionWorker() {
		cv::HoughCircles(mat, circles, method, dp, minDist, param1, param2, minRadius, maxRadius);
		return "";
	}

	FF_VAL getReturnValue() {
		return ObjectArrayConverter<Vec3, cv::Vec3d, cv::Vec3f>::wrap(circles);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &method, info) ||
			DoubleConverter::arg(1, &dp, info) ||
			DoubleConverter::arg(2, &minDist, info)
			);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(3, &param1, info) ||
			DoubleConverter::optArg(4, &param2, info) ||
			IntConverter::optArg(5, &minRadius, info) ||
			IntConverter::optArg(6, &maxRadius, info)
			);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(3);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[3]->ToObject();
		return (
			DoubleConverter::optProp(&param1, "param1", opts) ||
			DoubleConverter::optProp(&param2, "param2", opts) ||
			IntConverter::optProp(&minRadius, "minRadius", opts) ||
			IntConverter::optProp(&maxRadius, "maxRadius", opts)
			);
	}
};

NAN_METHOD(MatImgproc::HoughCircles) {
	HoughCirclesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::HoughCircles", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::HoughCirclesAsync) {
	HoughCirclesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::HoughCirclesAsync", HoughCirclesWorker, worker);
}


struct MatImgproc::EqualizeHistWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	EqualizeHistWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		cv::equalizeHist(self, dst);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}
};

NAN_METHOD(MatImgproc::EqualizeHist) {
	EqualizeHistWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::EqualizeHist", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::EqualizeHistAsync) {
	EqualizeHistWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::EqualizeHistAsync", EqualizeHistWorker, worker);
}


struct MatImgproc::CompareHistWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	CompareHistWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat H2;
	int method;

	double returnValue;

	std::string executeCatchCvExceptionWorker() {
		returnValue = cv::compareHist(self, H2, method);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return DoubleConverter::wrap(returnValue);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &H2, info) ||
			IntConverter::arg(1, &method, info)
		);
	}
};

NAN_METHOD(MatImgproc::CompareHist) {
	CompareHistWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::CompareHist", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::CompareHistAsync) {
	CompareHistWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::CompareHistAsync", CompareHistWorker, worker);
}


struct MatImgproc::FloodFillWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	FloodFillWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Point2d seedPoint;
	double newVal1;
	cv::Vec3d newVal3 = cv::Vec3d();
	cv::Mat mask = cv::noArray().getMat();
	double loDiff1;
	cv::Vec3d loDiff3 = cv::Vec3d();
	double upDiff1;
	cv::Vec3d upDiff3 = cv::Vec3d();
	int flags = 4;

	int returnValue;
	cv::Rect rect;

	std::string executeCatchCvExceptionWorker() {
		switch (self.channels()) {
		case 1:
			returnValue = cv::floodFill(self, mask, seedPoint, newVal1, &rect, loDiff1, upDiff1, flags);
			break;
		case 3:
			returnValue = cv::floodFill(self, mask, seedPoint, newVal3, &rect, loDiff3, upDiff3, flags);
			break;
		default:
			return "expected single or 3 channel mat";
			break;
		}

		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), IntConverter::wrap(returnValue));
		Nan::Set(ret, Nan::New("rect").ToLocalChecked(), Rect::Converter::wrap(rect));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Point2::Converter::arg(0, &seedPoint, info) ||
			(self.channels() == 1 && DoubleConverter::optArg(1, &newVal1, info)) ||
			(self.channels() == 3 && Vec3::Converter::optArg(1, &newVal3, info))
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::optArg(2, &mask, info) ||
			(self.channels() == 1 && DoubleConverter::optArg(3, &loDiff1, info)) ||
			(self.channels() == 3 && Vec3::Converter::optArg(3, &loDiff3, info)) ||
			(self.channels() == 1 && DoubleConverter::optArg(4, &upDiff1, info)) ||
			(self.channels() == 3 && Vec3::Converter::optArg(4, &upDiff3, info)) ||
			IntConverter::optArg(5, &flags, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(2)
			&& !Mat::Converter::hasInstance(info[2]);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[2]->ToObject();
		return (
			Mat::Converter::optProp(&mask, "mask", opts) ||
			(self.channels() == 1 && DoubleConverter::optProp(&loDiff1, "loDiff", opts)) ||
			(self.channels() == 3 && Vec3::Converter::optProp(&loDiff3, "loDiff", opts)) ||
			(self.channels() == 1 && DoubleConverter::optProp(&upDiff1, "upDiff", opts)) ||
			(self.channels() == 3 && Vec3::Converter::optProp(&upDiff3, "upDiff", opts)) ||
			IntConverter::optProp(&flags, "flags", opts)
		);
	}
};

NAN_METHOD(MatImgproc::FloodFill) {
	FloodFillWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::FloodFill", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::FloodFillAsync) {
	FloodFillWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::FloodFillAsync", FloodFillWorker, worker);
}

struct MatImgproc::BilateralFilterWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	BilateralFilterWorker(cv::Mat self) {
		this->self = self;
	}

	int d;
	double sigmaColor;
	double sigmaSpace;
	int borderType = cv::BORDER_DEFAULT;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		cv::bilateralFilter(self, dst, d, sigmaColor, sigmaSpace, borderType);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &d, info) ||
			DoubleConverter::arg(1, &sigmaColor, info) ||
			DoubleConverter::arg(2, &sigmaSpace, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(3, &borderType, info)
		);
	}
};

NAN_METHOD(MatImgproc::BilateralFilter) {
	BilateralFilterWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::BilateralFilter", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::BilateralFilterAsync) {
	BilateralFilterWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::BilateralFilterAsync", BilateralFilterWorker, worker);
}

struct MatImgproc::BoxFilterWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	BoxFilterWorker(cv::Mat self) {
		this->self = self;
	}

	int ddepth;
	cv::Size2d ksize;
	cv::Point2d anchor = cv::Point2d(-1, -1);
	bool normalize = true;
	int borderType = cv::BORDER_DEFAULT;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		cv::boxFilter(self, dst, ddepth, ksize, anchor, normalize, borderType);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &ddepth, info) ||
			Size::Converter::arg(1, &ksize, info)
			);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Point2::Converter::optArg(2, &anchor, info) ||
			BoolConverter::optArg(3, &normalize, info) ||
			IntConverter::optArg(4, &borderType, info)
			);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(2);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[2]->ToObject();
		return (
			Point2::Converter::optProp(&anchor, "anchor", opts) ||
			BoolConverter::optProp(&normalize, "normalize", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
		);
	}
};

NAN_METHOD(MatImgproc::BoxFilter) {
	BoxFilterWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::BoxFilter", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::BoxFilterAsync) {
	BoxFilterWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::BoxFilterAsync", BoxFilterWorker, worker);
}

struct MatImgproc::SqrBoxFilterWorker : public BoxFilterWorker {
public:
	SqrBoxFilterWorker(cv::Mat self) : BoxFilterWorker(self) {
	}

	std::string executeCatchCvExceptionWorker() {
		cv::sqrBoxFilter(self, dst, ddepth, ksize, anchor, normalize, borderType);
		return "";
	}
};

NAN_METHOD(MatImgproc::SqrBoxFilter) {
	SqrBoxFilterWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::SqrBoxFilter", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::SqrBoxFilterAsync) {
	SqrBoxFilterWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::SqrBoxFilterAsync", SqrBoxFilterWorker, worker);
}


struct MatImgproc::Filter2DWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	Filter2DWorker(cv::Mat self) {
		this->self = self;
	}

	int ddepth;
	cv::Mat kernel;
	cv::Point2d anchor = cv::Point2d(-1, -1);
	double delta = 0;
	int borderType = cv::BORDER_DEFAULT;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		cv::filter2D(self, dst, ddepth, kernel, anchor, delta, borderType);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &ddepth, info) ||
			Mat::Converter::arg(1, &kernel, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Point2::Converter::optArg(2, &anchor, info) ||
			DoubleConverter::optArg(3, &delta, info) ||
			IntConverter::optArg(4, &borderType, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(2);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[2]->ToObject();
		return (
			Point2::Converter::optProp(&anchor, "anchor", opts) ||
			DoubleConverter::optProp(&delta, "delta", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
		);
	}
};

NAN_METHOD(MatImgproc::Filter2D) {
	Filter2DWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Filter2D", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::Filter2DAsync) {
	Filter2DWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::Filter2DAsync", Filter2DWorker, worker);
}

struct MatImgproc::SepFilter2DWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	SepFilter2DWorker(cv::Mat self) {
		this->self = self;
	}

	int ddepth;
	cv::Mat kernelX;
	cv::Mat kernelY;
	cv::Point2d anchor = cv::Point2d(-1, -1);
	double delta = 0;
	int borderType = cv::BORDER_DEFAULT;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		cv::sepFilter2D(self, dst, ddepth, kernelX, kernelY, anchor, delta, borderType);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &ddepth, info) ||
			Mat::Converter::arg(1, &kernelX, info) ||
			Mat::Converter::arg(2, &kernelY, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Point2::Converter::optArg(3, &anchor, info) ||
			DoubleConverter::optArg(4, &delta, info) ||
			IntConverter::optArg(5, &borderType, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(3);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[3]->ToObject();
		return (
			Point2::Converter::optProp(&anchor, "anchor", opts) ||
			DoubleConverter::optProp(&delta, "delta", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
		);
	}
};

NAN_METHOD(MatImgproc::SepFilter2D) {
	SepFilter2DWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::SepFilter2D", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::SepFilter2DAsync) {
	SepFilter2DWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::SepFilter2DAsync", SepFilter2DWorker, worker);
}

struct MatImgproc::CornerHarrisWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	CornerHarrisWorker(cv::Mat self) {
		this->self = self;
	}

	int blockSize;
	int ksize;
	double k;
	int borderType = cv::BORDER_DEFAULT;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		cv::cornerHarris(self, dst, blockSize, ksize, k, borderType);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &blockSize, info) ||
			IntConverter::arg(1, &ksize, info) ||
			DoubleConverter::arg(2, &k, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(3, &borderType, info)
		);
	}
};

NAN_METHOD(MatImgproc::CornerHarris) {
	CornerHarrisWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::CornerHarris", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::CornerHarrisAsync) {
	CornerHarrisWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::CornerHarrisAsync", CornerHarrisWorker, worker);
}

struct MatImgproc::CornerSubPixWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	CornerSubPixWorker(cv::Mat self) {
		this->self = self;
	}

	std::vector<cv::Point2f> corners;
	cv::Size2d winSize;
	cv::Size2d zeroZone;
	cv::TermCriteria criteria;


	std::string executeCatchCvExceptionWorker() {
		cv::cornerSubPix(self, corners, winSize, zeroZone, criteria);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::wrap(corners);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(0, &corners, info) ||
			Size::Converter::arg(1, &winSize, info) ||
			Size::Converter::arg(2, &zeroZone, info) ||
			TermCriteria::Converter::arg(3, &criteria, info)
		);
	}
};

NAN_METHOD(MatImgproc::CornerSubPix) {
	CornerSubPixWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::CornerSubPix", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::CornerSubPixAsync) {
	CornerSubPixWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::CornerSubPixAsync", CornerSubPixWorker, worker);
}

struct MatImgproc::BaseCornerEigenValWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	BaseCornerEigenValWorker(cv::Mat self) {
		this->self = self;
	}

	int blockSize;
	int ksize = 3;
	int borderType = cv::BORDER_DEFAULT;

	cv::Mat dst;

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &blockSize, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(1, &ksize, info) ||
			IntConverter::optArg(2, &borderType, info)
			);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[1]->ToObject();
		return (
			IntConverter::optProp(&ksize, "ksize", opts) ||
			IntConverter::optProp(&borderType, "borderType", opts)
		);
	}
};

struct MatImgproc::CornerMinEigenValWorker : public MatImgproc::BaseCornerEigenValWorker {
public:
	CornerMinEigenValWorker(cv::Mat self) : BaseCornerEigenValWorker(self) {
	}

	std::string executeCatchCvExceptionWorker() {
		cv::cornerMinEigenVal(self, dst, blockSize, ksize, borderType);
		return "";
	}
};

NAN_METHOD(MatImgproc::CornerMinEigenVal) {
	CornerMinEigenValWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::CornerMinEigenVal", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::CornerMinEigenValAsync) {
	CornerMinEigenValWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::CornerMinEigenValAsync", CornerMinEigenValWorker, worker);
}

struct MatImgproc::CornerEigenValsAndVecsWorker : public MatImgproc::BaseCornerEigenValWorker {
public:
	CornerEigenValsAndVecsWorker(cv::Mat self) : BaseCornerEigenValWorker(self) {
	}

	std::string executeCatchCvExceptionWorker() {
		cv::cornerEigenValsAndVecs(self, dst, blockSize, ksize, borderType);
		return "";
	}
};

NAN_METHOD(MatImgproc::CornerEigenValsAndVecs) {
	CornerEigenValsAndVecsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::CornerEigenValsAndVecs", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::CornerEigenValsAndVecsAsync) {
	CornerEigenValsAndVecsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::CornerEigenValsAndVecsAsync", CornerEigenValsAndVecsWorker, worker);
}

struct MatImgproc::IntegralWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	IntegralWorker(cv::Mat self) {
		this->self = self;
	}

	int sdepth = -1;
	int sqdepth = -1;

	cv::Mat sum;
	cv::Mat sqsum;
	cv::Mat tilted;

	std::string executeCatchCvExceptionWorker() {
		cv::integral(self, sum, sqsum, tilted, sdepth, sqdepth);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("sum").ToLocalChecked(), Mat::Converter::wrap(sum));
		Nan::Set(ret, Nan::New("sqsum").ToLocalChecked(), Mat::Converter::wrap(sqsum));
		Nan::Set(ret, Nan::New("tilted").ToLocalChecked(), Mat::Converter::wrap(tilted));
		return ret;
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(0, &sdepth, info) ||
			IntConverter::optArg(1, &sqdepth, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(0);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[0]->ToObject();
		return (
			IntConverter::optProp(&sdepth, "sdepth", opts) ||
			IntConverter::optProp(&sqdepth, "sqdepth", opts)
		);
	}
};

NAN_METHOD(MatImgproc::Integral) {
	IntegralWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Integral", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatImgproc::IntegralAsync) {
	IntegralWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::IntegralAsync", IntegralWorker, worker);
}