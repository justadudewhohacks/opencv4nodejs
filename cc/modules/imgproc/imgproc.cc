#include "imgproc.h"
#include "Point2.h"
#include "Size.h"
#include "Mat.h"
#include "Contour.h"

#define FF_DEFINE_CALC_HIST(name, n, constRangesArray)																												\
	cv::MatND name(cv::Mat img, cv::Mat mask, int channels[], int histSize[], std::vector<float*> rangesVec) {	\
		const float* ranges[] = constRangesArray;																																	\
		cv::MatND hist;																																														\
		cv::calcHist(&img, 1, channels, mask, hist, n, histSize, ranges, true, false);														\
		return hist;																																															\
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
	Nan::SetMethod(target, "canny", Canny);
	Contour::Init();
};

NAN_METHOD(Imgproc::GetStructuringElement) {
	FF_REQUIRE_ARGS_OBJ("GetStructuringElement");
	int shape;
	v8::Local<v8::Object> jsSize;
	cv::Point2i anchor = cv::Point2i(-1, -1);
	FF_DESTRUCTURE_JSPROP_REQUIRED(args, shape, Int32Value);
	FF_GET_JSPROP_REQUIRED(args, jsSize, size, ToObject);
	if (FF_HAS(args, "anchor")) {
		anchor = Nan::ObjectWrap::Unwrap<Point2>(FF_GET_JSPROP(args, anchor)->ToObject())->pt;
	}
	v8::Local<v8::Object> jsKernel = FF_NEW_INSTANCE(Mat::constructor);
	FF_UNWRAP_MAT(jsKernel)->setNativeProps(
		cv::getStructuringElement(shape, FF_UNWRAP_SIZE_AND_GET(jsSize), anchor)
	);
	info.GetReturnValue().Set(jsKernel);
}

NAN_METHOD(Imgproc::GetRotationMatrix2D) {
	FF_METHOD_CONTEXT("GetRotationMatrix2D");

	FF_ARG_INSTANCE(0, cv::Point2i center, Point2::constructor, FF_UNWRAP_PT2_AND_GET);
	FF_ARG_NUMBER(1, double angle);

	FF_ARG_NUMBER_IFDEF(2, double scale, 1.0);

	FF_OBJ jsRotationMat = FF_NEW_INSTANCE(Mat::constructor);
	FF_UNWRAP_MAT_AND_GET(jsRotationMat) = cv::getRotationMatrix2D(center, angle, scale);
	info.GetReturnValue().Set(jsRotationMat);
}


NAN_METHOD(Imgproc::CalcHist) {
	FF_METHOD_CONTEXT("CalcHist");
	FF_REQUIRE_ARGS_OBJ("CalcHist");

	cv::Mat img;
	FF_DESTRUCTURE_JSOBJ_REQUIRED(args, img, Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat);
	cv::Mat inputImg = img;
	int inputType = CV_MAKETYPE(CV_32F, img.channels());
	if (inputType != img.type()) {
		img.convertTo(inputImg, inputType);
	}

	cv::Mat mask = cv::noArray().getMat();
	if (FF_HAS(args, "mask")) {
		/* with mask*/
		v8::Local<v8::Object> jsMask = FF_GET_JSPROP(args, mask)->ToObject();
		FF_REQUIRE_INSTANCE(Mat::constructor, jsMask, "expected mask to be an instance of Mat");
		mask = FF_UNWRAP_MAT_AND_GET(jsMask);
	}

	v8::Local<v8::Array> histAxes;
	FF_GET_ARRAY_REQUIRED(args, histAxes, "histAxes");

	int dims = histAxes->Length();
	int* channels = new int[dims];
	int* histSize = new int[dims];
	std::vector<float*> ranges;
	for (int i = 0; i < dims; ++i) {
		ranges.push_back(new float[dims]);
		v8::Local<v8::Object> jsAxis = FF_CAST_OBJ(histAxes->Get(i));
		v8::Local<v8::Array> jsRanges;
		FF_GET_JSARR_REQUIRED_WITH_LENGTH(jsAxis, jsRanges, ranges, 2);
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

	v8::Local<v8::Object> jsMat = FF_NEW_INSTANCE(Mat::constructor);
	int outputType = CV_MAKETYPE(CV_64F, img.channels());
	if (outputType != hist.type()) {
		hist.convertTo(hist, outputType);
	}

	FF_UNWRAP_MAT(jsMat)->setNativeProps(hist);
	info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Imgproc::Plot1DHist) {
	FF_REQUIRE_ARGS_OBJ("Plot1DHist");

	cv::Mat hist;
	v8::Local<v8::Array> ranges;
	FF_DESTRUCTURE_JSOBJ_REQUIRED(args, hist, Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat);
	FF_ASSERT_EQUALS(1, hist.cols, "Plot1DHist - hist rows", "");
	if (hist.channels() != 1) {
		return Nan::ThrowError("Plot1DHist - expected hist to be single channeled");
	}

	cv::Mat plot;
	if (FF_HAS(args, "plotTo")) {
		FF_GET_JSOBJ_REQUIRED(args, plot, plotTo, Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat);
	}
	else {
		if (!FF_HAS(args, "height") || !FF_HAS(args, "width")) {
			return Nan::ThrowError("Plot1DHist - expected either plotTo of type Mat or height and width of the plot");
		}
		int height, width; 
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, height, IsUint32, Uint32Value);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, width, IsUint32, Uint32Value);
		plot = cv::Mat(height, width, CV_8UC3, cv::Scalar(255, 255, 255));
	}

	cv::Vec3d lineColor = cv::Vec3d(0, 0, 0);
	if (FF_HAS(args, "lineColor")) {
		FF_DESTRUCTURE_JSOBJ_REQUIRED(args, lineColor, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET, Vec3);
	}

	double binWidth = ((double)plot.cols / (double)hist.rows);
	int plotHeight = cv::max(256, plot.rows - 20);
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
			lineColor,
			2, 
			8, 
			0
		);
	}

	v8::Local<v8::Object> jsMat = FF_NEW_INSTANCE(Mat::constructor);
	FF_UNWRAP_MAT(jsMat)->setNativeProps(plot);
	info.GetReturnValue().Set(jsMat);
}


NAN_METHOD(Imgproc::Canny) {
	FF_REQUIRE_ARGS_OBJ("Canny");

	double threshold1, threshold2;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, threshold1, IsNumber, NumberValue);
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, threshold2, IsNumber, NumberValue);

	bool L2gradient = false;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(args, L2gradient, IsBoolean, BooleanValue);

	v8::Local<v8::Object> jsMat = FF_NEW_INSTANCE(Mat::constructor);

#if CV_VERSION_MINOR < 2
	cv::Mat image;
	FF_GET_JSOBJ_REQUIRED(args, image, image, Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat);
	int apertureSize = 3;
	FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, apertureSize, IsUint32, Uint32Value);
	cv::Canny(image, FF_UNWRAP_MAT_AND_GET(jsMat), threshold1, threshold2, apertureSize, L2gradient);
#else
	cv::Mat dx, dy;
	FF_GET_JSOBJ_REQUIRED(args, dx, dx, Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat);
	FF_GET_JSOBJ_REQUIRED(args, dy, dy, Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat);
	cv::Canny(dx, dy, FF_UNWRAP_MAT_AND_GET(jsMat), threshold1, threshold2, L2gradient);
#endif

	info.GetReturnValue().Set(jsMat);
}