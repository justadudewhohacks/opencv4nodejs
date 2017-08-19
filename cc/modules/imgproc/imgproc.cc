#include "imgproc.h"
#include "Point2.h"
#include "Size.h"
#include "Mat.h"

NAN_MODULE_INIT(Imgproc::Init) {
	Nan::SetMethod(target, "getStructuringElement", GetStructuringElement);
	Nan::SetMethod(target, "calcHist", CalcHist);
	Nan::SetMethod(target, "plot1DHist", Plot1DHist);
};

NAN_METHOD(Imgproc::GetStructuringElement) {
	FF_REQUIRE_ARGS_OBJ("GetStructuringElement");
	int shape;
	v8::Local<v8::Object> jsSize;
	cv::Point2i anchor = cv::Point2i(-1, -1);
	FF_DESTRUCTURE_JSPROP_REQUIRED(args, shape, Int32Value);
	FF_GET_JSPROP_REQUIRED(args, jsSize, size, ToObject);
	if (FF_HAS_JS_PROP(args, anchor)) {
		anchor = Nan::ObjectWrap::Unwrap<Point2>(FF_GET_JSPROP(args, anchor)->ToObject())->pt;
	}
	v8::Local<v8::Object> jsKernel = FF_NEW(Mat::constructor);
	FF_UNWRAP_MAT(jsKernel)->setNativeProps(
		cv::getStructuringElement(shape, FF_UNWRAP_SIZE_AND_GET(jsSize), anchor)
	);
	info.GetReturnValue().Set(jsKernel);
}

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


NAN_METHOD(Imgproc::CalcHist) { 
	FF_REQUIRE_ARGS_OBJ("CalcHist");

	cv::Mat img;
	FF_DESTRUCTURE_JSOBJ_REQUIRED(args, img, Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat);

	cv::Mat mask = cv::noArray().getMat();
	if (FF_HAS_JS_PROP(args, mask)) {
		/* with mask*/
		v8::Local<v8::Object> jsMask = FF_GET_JSPROP(args, mask)->ToObject();
		FF_REQUIRE_INSTANCE(Mat::constructor, jsMask, "mask", "Mat");
		mask = FF_UNWRAP_MAT_AND_GET(jsMask);
	}

	v8::Local<v8::Array> histAxes;
	FF_GET_JSARR_REQUIRED(args, histAxes, histAxes);

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
		hist = calcHist1(img, mask, channels, histSize, ranges);
	}
	else if (dims == 2) {
		hist = calcHist2(img, mask, channels, histSize, ranges);
	}
	else if (dims == 3) {
		hist = calcHist3(img, mask, channels, histSize, ranges);
	}
	else if (dims == 4) {
		hist = calcHist4(img, mask, channels, histSize, ranges);
	}

	for (int i = 0; i < dims; ++i) {
		delete[] ranges.at(i);
	}
	delete[] channels;
	delete[] histSize;

	v8::Local<v8::Object> jsMat = FF_NEW(Mat::constructor);
	int type = FF::reassignMatTypeIfFloat(info[1]->Int32Value());
	if (hist.type() != type) {
		hist.convertTo(hist, type);
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
	if (FF_HAS_JS_PROP(args, plotTo)) {
		FF_DESTRUCTURE_JSOBJ_REQUIRED(args, plot, Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat);
	}
	else {
		if (!FF_HAS_JS_PROP(args, height) || !FF_HAS_JS_PROP(args, width)) {
			return Nan::ThrowError("Plot1DHist - expected either plotTo of type Mat or height and width of the plot");
		}
		int height, width; 
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, height, IsUint32, Uint32Value);
		FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(args, width, IsUint32, Uint32Value);
		plot = cv::Mat(height, width, CV_8UC3, cv::Scalar(255, 255, 255));
	}

	cv::Vec3d drawColor = cv::Vec3d(0, 0, 0);
	if (FF_HAS_JS_PROP(args, drawColor)) {
		FF_DESTRUCTURE_JSOBJ_REQUIRED(args, drawColor, Vec3::constructor, FF_UNWRAP_VEC3_AND_GET, Vec3);
	}




	double binWidth = ((double)plot.cols / (double)hist.rows);
	int plotHeight = cv::max(256, plot.rows - 20);
	cv::Mat normHist = hist;
	if (hist.type() != CV_64F) {
		cv::cvtColor(hist, normHist, CV_64F);
	}
	cv::normalize(normHist, normHist, 0, 256, cv::NORM_MINMAX);

	for (int i = 1; i < hist.rows; i++) {
		std::cout << std::to_string(binWidth*i + binWidth) << std::endl;
		cv::line(
			plot, 
			cv::Point(binWidth*(i - 1), plotHeight - normHist.at<double>(i - 1)),
			cv::Point(binWidth*i, plotHeight - normHist.at<double>(i)),
			cv::Vec3d(255, 0, 0), 
			2, 
			8, 
			0
		);
	}

	v8::Local<v8::Object> jsMat = FF_NEW(Mat::constructor);
	FF_UNWRAP_MAT(jsMat)->setNativeProps(plot);
	info.GetReturnValue().Set(jsMat);
}