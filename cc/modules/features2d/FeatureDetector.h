#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include "KeyPoint.h"
#include "Mat.h"

#ifndef FF_FEATUREDETECTOR_H_
#define FF_FEATUREDETECTOR_H_

class FeatureDetector : public Nan::ObjectWrap {
public:
	virtual cv::Ptr<cv::FeatureDetector> getDetector() = 0;

	static void Init(v8::Local<v8::FunctionTemplate>);
	static NAN_METHOD(Detect);
	static NAN_METHOD(Compute);

	static NAN_METHOD(DetectAsync);
	static NAN_METHOD(ComputeAsync);

	struct DetectContext {
	public:
		cv::Ptr<cv::FeatureDetector> det;
		cv::Mat img;
		std::vector<cv::KeyPoint> kps;

		const char* execute() {
			det->detect(img, kps);
			return "";
		}

		FF_VAL getReturnValue() {
			FF_PACK_KEYPOINT_ARRAY(jsKps, kps);
			return jsKps;
		}
	};

	struct ComputeContext {
	public:
		cv::Ptr<cv::FeatureDetector> det;
		cv::Mat img;
		std::vector<cv::KeyPoint> kps;
		cv::Mat desc;

		const char* execute() {
			det->compute(img, kps, desc);
			return "";
		}

		FF_VAL getReturnValue() {
			FF_OBJ jsDesc = FF_NEW_INSTANCE(Mat::constructor);
			FF_UNWRAP_MAT_AND_GET(jsDesc) = desc;
			return jsDesc;
		}
	};
};

#endif