#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "features2d.h"
#include "KeyPoint.h"
#include "KeyPointMatch.h"
#include "DescriptorMatch.h"
#include "BFMatcher.h"
#include "descriptorMatching.h"
#include "descriptorMatchingKnn.h"
#include "detectors/AGASTDetector.h"
#include "detectors/AKAZEDetector.h"
#include "detectors/BRISKDetector.h"
#include "detectors/FASTDetector.h"
#include "detectors/GFTTDetector.h"
#include "detectors/KAZEDetector.h"
#include "detectors/MSERDetector.h"
#include "detectors/ORBDetector.h"
#include "detectors/SimpleBlobDetector.h"

NAN_MODULE_INIT(Features2d::Init) {
	KeyPoint::Init(target);
	KeyPointMatch::Init(target);
	DescriptorMatch::Init(target);
	DescriptorMatching::Init(target);
	DescriptorMatchingKnn::Init(target);
	AGASTDetector::Init(target);
	AKAZEDetector::Init(target);
	BRISKDetector::Init(target);
	BFMatcher::Init(target);
	FASTDetector::Init(target);
	GFTTDetector::Init(target);
	KAZEDetector::Init(target);
	MSERDetector::Init(target);
	ORBDetector::Init(target);
	SimpleBlobDetector::Init(target);

	v8::Local<v8::Object> agastTypes = Nan::New<v8::Object>();
	FF_SET_JS_PROP(agastTypes, AGAST_5_8, Nan::New<v8::Integer>(cv::AgastFeatureDetector::AGAST_5_8));
	FF_SET_JS_PROP(agastTypes, AGAST_7_12d, Nan::New<v8::Integer>(cv::AgastFeatureDetector::AGAST_7_12d));
	FF_SET_JS_PROP(agastTypes, AGAST_7_12s, Nan::New<v8::Integer>(cv::AgastFeatureDetector::AGAST_7_12s));
	FF_SET_JS_PROP(agastTypes, OAST_9_16, Nan::New<v8::Integer>(cv::AgastFeatureDetector::OAST_9_16));
	FF_SET_JS_PROP(agastTypes, THRESHOLD, Nan::New<v8::Integer>(cv::AgastFeatureDetector::THRESHOLD));
	FF_SET_JS_PROP(agastTypes, NONMAX_SUPPRESSION, Nan::New<v8::Integer>(cv::AgastFeatureDetector::NONMAX_SUPPRESSION));
	FF_SET_JS_PROP(target, "AGAST", agastTypes);

	v8::Local<v8::Object> akazeTypes = Nan::New<v8::Object>();
	FF_SET_JS_PROP(akazeTypes, DESCRIPTOR_KAZE, Nan::New<v8::Integer>(cv::AKAZE::DESCRIPTOR_KAZE));
	FF_SET_JS_PROP(akazeTypes, DESCRIPTOR_KAZE, Nan::New<v8::Integer>(cv::AKAZE::DESCRIPTOR_KAZE));
	FF_SET_JS_PROP(akazeTypes, DESCRIPTOR_MLDB_UPRIGHT, Nan::New<v8::Integer>(cv::AKAZE::DESCRIPTOR_MLDB_UPRIGHT));
	FF_SET_JS_PROP(akazeTypes, DESCRIPTOR_MLDB, Nan::New<v8::Integer>(cv::AKAZE::DESCRIPTOR_MLDB));
	FF_SET_JS_PROP(target, "AKAZE", akazeTypes);

	v8::Local<v8::Object> kazeTypes = Nan::New<v8::Object>();
	FF_SET_JS_PROP(kazeTypes, DIFF_PM_G1, Nan::New<v8::Integer>(cv::KAZE::DIFF_PM_G1));
	FF_SET_JS_PROP(kazeTypes, DIFF_PM_G2, Nan::New<v8::Integer>(cv::KAZE::DIFF_PM_G2));
	FF_SET_JS_PROP(kazeTypes, DIFF_WEICKERT, Nan::New<v8::Integer>(cv::KAZE::DIFF_WEICKERT));
	FF_SET_JS_PROP(kazeTypes, DIFF_CHARBONNIER, Nan::New<v8::Integer>(cv::KAZE::DIFF_CHARBONNIER));
	FF_SET_JS_PROP(target, "KAZE", kazeTypes);

	v8::Local<v8::Object> fastTypes = Nan::New<v8::Object>();
	FF_SET_JS_PROP(fastTypes, TYPE_5_8, Nan::New<v8::Integer>(cv::FastFeatureDetector::TYPE_5_8));
	FF_SET_JS_PROP(fastTypes, TYPE_7_12, Nan::New<v8::Integer>(cv::FastFeatureDetector::TYPE_7_12));
	FF_SET_JS_PROP(fastTypes, TYPE_9_16, Nan::New<v8::Integer>(cv::FastFeatureDetector::TYPE_9_16));
	FF_SET_JS_PROP(fastTypes, THRESHOLD, Nan::New<v8::Integer>(cv::FastFeatureDetector::THRESHOLD));
	FF_SET_JS_PROP(fastTypes, NONMAX_SUPPRESSION, Nan::New<v8::Integer>(cv::FastFeatureDetector::NONMAX_SUPPRESSION));
	FF_SET_JS_PROP(target, "FAST", fastTypes);

	v8::Local<v8::Object> orbTypes = Nan::New<v8::Object>();
	FF_SET_JS_PROP(orbTypes, HARRIS_SCORE, Nan::New<v8::Integer>(cv::ORB::HARRIS_SCORE));
	FF_SET_JS_PROP(orbTypes, FAST_SCORE, Nan::New<v8::Integer>(cv::ORB::FAST_SCORE));
	FF_SET_JS_PROP(orbTypes, kBytes, Nan::New<v8::Integer>(cv::ORB::kBytes));
	FF_SET_JS_PROP(target, "ORB", orbTypes);

	Nan::SetMethod(target, "drawKeyPoints", DrawKeyPoints);
	Nan::SetMethod(target, "drawMatches", DrawMatches);
};

NAN_METHOD(Features2d::DrawKeyPoints) {
	FF::TryCatch tryCatch("Features2d::DrawKeyPoints");

	cv::Mat img;
	std::vector<cv::KeyPoint> kps;
	if (
		Mat::Converter::arg(0, &img, info) ||
		KeyPoint::ArrayConverter::arg(1, &kps, info)
	) {
		return tryCatch.reThrow();
	}

	cv::Mat drawMat;
	cv::drawKeypoints(img, kps, drawMat);
	info.GetReturnValue().Set(Mat::Converter::wrap(drawMat));
}

NAN_METHOD(Features2d::DrawMatches) {
	FF::TryCatch tryCatch("Features2d::DrawMatches");

	cv::Mat img1, img2;
	std::vector<cv::KeyPoint> kps1, kps2;
	std::vector<cv::DMatch> dMatches;
	if (
		Mat::Converter::arg(0, &img1, info) ||
		Mat::Converter::arg(1, &img2, info) ||
		KeyPoint::ArrayConverter::arg(2, &kps1, info) ||
		KeyPoint::ArrayConverter::arg(3, &kps2, info) ||
		DescriptorMatch::ArrayConverter::arg(4, &dMatches, info)
		) {
		return tryCatch.reThrow();
	}

	cv::Mat drawMat;
	cv::drawMatches(img1, kps1, img2, kps2, dMatches, drawMat);
	info.GetReturnValue().Set(Mat::Converter::wrap(drawMat));
}

#endif
