#include "MatImgproc.h"
#include "imgproc/Moments.h"
#include "imgproc/Contour.h"

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
	Nan::SetPrototypeMethod(ctor, "moments", _Moments);
	Nan::SetPrototypeMethod(ctor, "momentsAsync", _MomentsAsync);
	Nan::SetPrototypeMethod(ctor, "findContours", FindContours);
	Nan::SetPrototypeMethod(ctor, "findContoursAsync", FindContoursAsync);
	Nan::SetPrototypeMethod(ctor, "drawContours", DrawContours);
	Nan::SetPrototypeMethod(ctor, "drawLine", DrawLine);
	Nan::SetPrototypeMethod(ctor, "drawCircle", DrawCircle);
	Nan::SetPrototypeMethod(ctor, "drawRectangle", DrawRectangle);
	Nan::SetPrototypeMethod(ctor, "drawEllipse", DrawEllipse);
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
};

struct MatImgproc::BaseResizeWorker : public SimpleWorker {
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

	const char* execute() {
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

	const char* execute() {
		cv::resize(self, dst, cv::Size(rows, cols));
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &rows, info) ||
			IntConverter::arg(0, &cols, info)
		);
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

	const char* execute() {
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

struct MatImgproc::ThresholdWorker : SimpleWorker {
public:
	cv::Mat mat;

	ThresholdWorker(cv::Mat mat) {
		this->mat = mat;
	}

	double thresh;
	double maxVal;
	uint type;

	cv::Mat thresholdMat;

	const char* execute() {
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

struct MatImgproc::AdaptiveThresholdWorker : SimpleWorker {
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

	const char* execute() {
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

struct MatImgproc::InRangeWorker : SimpleWorker {
public:
	cv::Mat mat;

	InRangeWorker(cv::Mat mat) {
		this->mat = mat;
	}

	cv::Vec3d lower;
	cv::Vec3d upper;

	cv::Mat inRangeMat;

	const char* execute() {
		cv::inRange(mat, lower, upper, inRangeMat);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(inRangeMat);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Vec3::Converter::arg(0, &lower, info) ||
			Vec3::Converter::arg(1, &upper, info)
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


struct MatImgproc::CvtColorWorker : public SimpleWorker {
public:
	cv::Mat self;
	CvtColorWorker(cv::Mat self) {
		this->self = self;
	}

	int code;
	int dstCn = 0;

	cv::Mat dst;

	const char* execute() {
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


struct MatImgproc::BgrToGrayWorker : public SimpleWorker {
public:
	cv::Mat self;
	BgrToGrayWorker(cv::Mat self) {
		this->self = self;
	}

	int code;

	cv::Mat dst;

	const char* execute() {
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

struct MatImgproc::WarpWorker {
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

	const char* execute() {
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

	const char* execute() {
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


struct MatImgproc::MorphWorker {
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

	const char* execute() {
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

	const char* execute() {
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

	const char* execute() {
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

struct MatImgproc::DistanceTransformWorker : public SimpleWorker {
public:
	cv::Mat self;
	DistanceTransformWorker(cv::Mat self) {
		this->self = self;
	}

	int distanceType;
	int maskSize;
	int dstType = CV_32F;

	cv::Mat dst;

	const char* execute() {
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

	const char* execute() {
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


struct MatImgproc::BlurWorker {
public:
	cv::Mat mat;

	BlurWorker(cv::Mat mat) {
		this->mat = mat;
	}

	cv::Size2d kSize;
	cv::Point2d anchor = cv::Point2d(-1, -1);
	int borderType = cv::BORDER_CONSTANT;

	cv::Mat blurMat;

	const char* execute() {
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


struct MatImgproc::GaussianBlurWorker {
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

	const char* execute() {
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


struct MatImgproc::MedianBlurWorker : public SimpleWorker {
public:
	cv::Mat mat;

	MedianBlurWorker(cv::Mat mat) {
		this->mat = mat;
	}

	int kSize;

	cv::Mat blurMat;

	const char* execute() {
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


struct MatImgproc::ConnectedComponentsWorker : public SimpleWorker {
public:
	cv::Mat self;
	ConnectedComponentsWorker(cv::Mat self) {
		this->self = self;
	}

	int connectivity = 8;
	int ltype = CV_32S;

	cv::Mat labels;

	const char* execute() {
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

	const char* execute() {
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


struct MatImgproc::GrabCutWorker : public SimpleWorker {
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


	const char* execute() {
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

struct MatImgproc::MomentsWorker : public SimpleWorker {
public:
	cv::Mat self;
	MomentsWorker(cv::Mat self) {
		this->self = self;
	}

	bool binaryImage = false;

	cv::Moments returnValue;

	const char* execute() {
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

struct MatImgproc::FindContoursWorker : public SimpleWorker {
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

	const char* execute() {
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
	FF_GET_UINT_IFDEF(optArgs, uint contourIdx, "contourIdx", 0);
	FF_GET_INT_IFDEF(optArgs, int maxLevel, "maxLevel", INT_MAX);
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Point2d offset, "offset", Point2::constructor, FF_UNWRAP_PT2_AND_GET, Point2, cv::Point2d());
	FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
	FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 1);
	if (!hasOptArgsObj) {
		FF_ARG_UINT_IFDEF(2, contourIdx, contourIdx);
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
		(int)contourIdx,
		color,
		thickness,
		lineType,
		hierarchy,
		(int)maxLevel,
		offset
	);
	FF_RETURN(info.This());
}

NAN_METHOD(MatImgproc::DrawLine) {
	FF_METHOD_CONTEXT("Mat::DrawLine");

	FF_ARG_INSTANCE(0, cv::Point2d pt1, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	FF_ARG_INSTANCE(1, cv::Point2d pt2, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	FF_ARG_INSTANCE(2, cv::Vec3d color, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(3) && info[3]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[3]->ToObject() : FF_NEW_OBJ();
	FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
	FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 1);
	FF_GET_INT_IFDEF(optArgs, int shift, "shift", 0);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(3, lineType, lineType);
		FF_ARG_INT_IFDEF(4, thickness, thickness);
		FF_ARG_INT_IFDEF(5, shift, shift);
	}

	cv::line(FF_UNWRAP_MAT_AND_GET(info.This()), pt1, pt2, color, thickness, lineType, shift);
	FF_RETURN(info.This());
}

NAN_METHOD(MatImgproc::DrawCircle) {
	FF_METHOD_CONTEXT("Mat::DrawCircle");

	FF_ARG_INSTANCE(0, cv::Point2d center, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	FF_ARG_UINT(1, uint radius);
	FF_ARG_INSTANCE(2, cv::Vec3d color, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(3) && info[3]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[3]->ToObject() : FF_NEW_OBJ();
	FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
	FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 1);
	FF_GET_INT_IFDEF(optArgs, int shift, "shift", 0);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(3, lineType, lineType);
		FF_ARG_INT_IFDEF(4, thickness, thickness);
		FF_ARG_INT_IFDEF(5, shift, shift);
	}

	cv::circle(FF_UNWRAP_MAT_AND_GET(info.This()), center, (int)radius, color, thickness, lineType, shift);
	FF_RETURN(info.This());
}

NAN_METHOD(MatImgproc::DrawRectangle) {
	FF_METHOD_CONTEXT("Mat::DrawRectangle");

	FF_ARG_INSTANCE(0, cv::Point2d pt1, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	FF_ARG_INSTANCE(1, cv::Point2d pt2, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	FF_ARG_INSTANCE(2, cv::Vec3d color, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(3) && info[3]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[3]->ToObject() : FF_NEW_OBJ();
	FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
	FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 1);
	FF_GET_INT_IFDEF(optArgs, int shift, "shift", 0);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(3, lineType, lineType);
		FF_ARG_INT_IFDEF(4, thickness, thickness);
		FF_ARG_INT_IFDEF(5, shift, shift);
	}

	cv::rectangle(FF_UNWRAP_MAT_AND_GET(info.This()), pt1, pt2, color, thickness, lineType, shift);
	FF_RETURN(info.This());
}

NAN_METHOD(MatImgproc::DrawEllipse) {
	FF_METHOD_CONTEXT("Mat::DrawEllipse");

	FF_ARG_INSTANCE(0, cv::RotatedRect box, RotatedRect::constructor, FF_UNWRAP_ROTATEDRECT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Vec3d color, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(2) && info[2]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[2]->ToObject() : FF_NEW_OBJ();
	FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
	FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 1);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(2, lineType, lineType);
		FF_ARG_INT_IFDEF(3, thickness, thickness);
	}

	cv::ellipse(FF_UNWRAP_MAT_AND_GET(info.This()), box, color, thickness, lineType);
	FF_RETURN(info.This());
}

NAN_METHOD(MatImgproc::PutText) {
	FF_METHOD_CONTEXT("Mat::PutText");

	FF_ARG_STRING(0, std::string text);
	FF_ARG_INSTANCE(1, cv::Point2d org, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	FF_ARG_UINT(2, uint fontFace);
	FF_ARG_NUMBER(3, double fontScale);
	FF_ARG_INSTANCE(4, cv::Vec3d color, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(5) && info[5]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[5]->ToObject() : FF_NEW_OBJ();
	FF_GET_INT_IFDEF(optArgs, int lineType, "lineType", cv::LINE_8);
	FF_GET_INT_IFDEF(optArgs, int thickness, "thickness", 1);
	FF_GET_BOOL_IFDEF(optArgs, bool bottomLeftOrigin, "bottomLeftOrigin", false);
	if (!hasOptArgsObj) {
		FF_ARG_INT_IFDEF(5, lineType, lineType);
		FF_ARG_INT_IFDEF(6, thickness, thickness);
		FF_ARG_INT_IFDEF(7, bottomLeftOrigin, bottomLeftOrigin);
	}

	cv::putText(
		FF_UNWRAP_MAT_AND_GET(info.This()),
		text,
		org,
		(int)fontFace,
		fontScale,
		color,
		thickness,
		lineType,
		bottomLeftOrigin
	);
	FF_RETURN(info.This());
}


struct MatImgproc::MatchTemplateWorker : SimpleWorker {
public:
	cv::Mat mat;

	MatchTemplateWorker(cv::Mat mat) {
		this->mat = mat;
	}

	cv::Mat templ;
	int method;
	cv::Mat mask = cv::noArray().getMat();

	cv::Mat resultsMat;

	const char* execute() {
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


struct MatImgproc::CannyWorker {
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

	const char* execute() {
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


struct MatImgproc::SobelScharrWorker {
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

	const char* execute() {
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

	const char* execute() {
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


struct MatImgproc::LaplacianWorker {
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

	const char* execute() {
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


struct MatImgproc::PyrWorker {
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

	const char* execute() {
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

struct MatImgproc::BuildPyramidWorker : public SimpleWorker {
public:
	cv::Mat mat;

	BuildPyramidWorker(cv::Mat mat) {
		this->mat = mat;
	}

	int maxlevel;
	int borderType = cv::BORDER_DEFAULT;

	std::vector<cv::Mat> dst;

	const char* execute() {
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

struct MatImgproc::HoughLinesWorker {
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

	const char* execute() {
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

	const char* execute() {
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

struct MatImgproc::HoughCirclesWorker {
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

	const char* execute() {
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


struct MatImgproc::EqualizeHistWorker : public SimpleWorker {
public:
	cv::Mat self;
	EqualizeHistWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat dst;

	const char* execute() {
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


struct MatImgproc::CompareHistWorker : public SimpleWorker {
public:
	cv::Mat self;
	CompareHistWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat H2;
	int method;

	double returnValue;

	const char* execute() {
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