#include "photo.h"
#include "Mat.h"
#include <opencv2/highgui.hpp>
#include <opencv2/videostab.hpp>

NAN_MODULE_INIT(Photo::Init) {
  Nan::SetMethod(target, "fastNlMeansDenoisingColored", FastNlMeansDenoisingColored);
  Nan::SetMethod(target, "inpaint", Inpaint);
  Nan::SetMethod(target, "inpaintAsync", InpaintAsync);
};

NAN_METHOD(Photo::FastNlMeansDenoisingColored) {
	FF_METHOD_CONTEXT("Photo::FastNlMeansDenoisingColored");

	FF_ARG_INSTANCE(0, cv::Mat src, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(1) && info[1]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[1]->ToObject() : FF_NEW_OBJ();

	FF_GET_NUMBER_IFDEF(optArgs, double h, "h", 3.0);
	FF_GET_NUMBER_IFDEF(optArgs, double hColor, "hColor", 3.0);
	FF_GET_UINT_IFDEF(optArgs, uint templateWindowSize, "templateWindowSize", 7);
	FF_GET_UINT_IFDEF(optArgs, uint searchWindowSize, "searchWindowSize", 21);
	if (!hasOptArgsObj) {
		FF_ARG_NUMBER_IFDEF(1, h, h);
		FF_ARG_NUMBER_IFDEF(2, hColor, hColor);
		FF_ARG_UINT_IFDEF(3, templateWindowSize, templateWindowSize);
		FF_ARG_UINT_IFDEF(4, searchWindowSize, searchWindowSize);
	}

	FF_OBJ jsDst = FF_NEW_INSTANCE(Mat::constructor);
	cv::fastNlMeansDenoisingColored(src, FF_UNWRAP_MAT_AND_GET(jsDst), h, hColor, templateWindowSize, searchWindowSize);
  FF_RETURN(jsDst);
}

struct Photo::InpaintWorker : public SimpleWorker {
public:
	cv::Mat src;
	InpaintWorker(cv::Mat self) {
		this->src = self;
	}

	// required function arguments
	cv::Mat inpaintMask;
	double inpaintRadius;
	int flags;

	// function return value
	cv::Mat dst;

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
				Mat::Converter::arg(1, &inpaintMask, info) ||
				DoubleConverter::arg(2, &inpaintRadius, info) ||
				IntConverter::arg(3, &flags, info)
		);
	}

	const char* execute() {
		cv::inpaint(
				src, inpaintMask, dst,
				inpaintRadius, flags
		);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(dst);
	}
};

NAN_METHOD(Photo::Inpaint) {
		FF_METHOD_CONTEXT("Photo::Inpaint");

		FF_ARG_INSTANCE(0, cv::Mat src, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

		InpaintWorker worker(src);
		FF_WORKER_SYNC("Photo::Inpaint", worker);
		info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Photo::InpaintAsync) {
		FF_METHOD_CONTEXT("Photo::InpaintAsync");

		FF_ARG_INSTANCE(0, cv::Mat src, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

		InpaintWorker worker(src);
		FF_WORKER_ASYNC("Photo::InpaintAsync", InpaintWorker, worker);
}