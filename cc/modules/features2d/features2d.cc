#include "features2d.h"
#include "KeyPoint.h"
#include "KeyPointMatch.h"
#include "DescriptorMatch.h"
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
	FASTDetector::Init(target);
	GFTTDetector::Init(target);
	KAZEDetector::Init(target);
	MSERDetector::Init(target);
	ORBDetector::Init(target);
	SimpleBlobDetector::Init(target);

	FF_OBJ agastTypes = FF_NEW_OBJ();
	FF_SET_JS_PROP(agastTypes, AGAST_5_8, Nan::New<v8::Integer>(cv::AgastFeatureDetector::AGAST_5_8));
	FF_SET_JS_PROP(agastTypes, AGAST_7_12d, Nan::New<v8::Integer>(cv::AgastFeatureDetector::AGAST_7_12d));
	FF_SET_JS_PROP(agastTypes, AGAST_7_12s, Nan::New<v8::Integer>(cv::AgastFeatureDetector::AGAST_7_12s));
	FF_SET_JS_PROP(agastTypes, OAST_9_16, Nan::New<v8::Integer>(cv::AgastFeatureDetector::OAST_9_16));
	FF_SET_JS_PROP(agastTypes, THRESHOLD, Nan::New<v8::Integer>(cv::AgastFeatureDetector::THRESHOLD));
	FF_SET_JS_PROP(agastTypes, NONMAX_SUPPRESSION, Nan::New<v8::Integer>(cv::AgastFeatureDetector::NONMAX_SUPPRESSION));
	FF_SET_JS_PROP(target, "AGAST", agastTypes);

	FF_OBJ akazeTypes = FF_NEW_OBJ();
	FF_SET_JS_PROP(akazeTypes, DESCRIPTOR_KAZE, Nan::New<v8::Integer>(cv::AKAZE::DESCRIPTOR_KAZE));
	FF_SET_JS_PROP(akazeTypes, DESCRIPTOR_KAZE, Nan::New<v8::Integer>(cv::AKAZE::DESCRIPTOR_KAZE));
	FF_SET_JS_PROP(akazeTypes, DESCRIPTOR_MLDB_UPRIGHT, Nan::New<v8::Integer>(cv::AKAZE::DESCRIPTOR_MLDB_UPRIGHT));
	FF_SET_JS_PROP(akazeTypes, DESCRIPTOR_MLDB, Nan::New<v8::Integer>(cv::AKAZE::DESCRIPTOR_MLDB));
	FF_SET_JS_PROP(target, "AKAZE", akazeTypes);

	FF_OBJ kazeTypes = FF_NEW_OBJ();
	FF_SET_JS_PROP(kazeTypes, DIFF_PM_G1, Nan::New<v8::Integer>(cv::KAZE::DIFF_PM_G1));
	FF_SET_JS_PROP(kazeTypes, DIFF_PM_G2, Nan::New<v8::Integer>(cv::KAZE::DIFF_PM_G2));
	FF_SET_JS_PROP(kazeTypes, DIFF_WEICKERT, Nan::New<v8::Integer>(cv::KAZE::DIFF_WEICKERT));
	FF_SET_JS_PROP(kazeTypes, DIFF_CHARBONNIER, Nan::New<v8::Integer>(cv::KAZE::DIFF_CHARBONNIER));
	FF_SET_JS_PROP(target, "KAZE", kazeTypes);

	FF_OBJ fastTypes = FF_NEW_OBJ();
	FF_SET_JS_PROP(fastTypes, TYPE_5_8, Nan::New<v8::Integer>(cv::FastFeatureDetector::TYPE_5_8));
	FF_SET_JS_PROP(fastTypes, TYPE_7_12, Nan::New<v8::Integer>(cv::FastFeatureDetector::TYPE_7_12));
	FF_SET_JS_PROP(fastTypes, TYPE_9_16, Nan::New<v8::Integer>(cv::FastFeatureDetector::TYPE_9_16));
	FF_SET_JS_PROP(fastTypes, THRESHOLD, Nan::New<v8::Integer>(cv::FastFeatureDetector::THRESHOLD));
	FF_SET_JS_PROP(fastTypes, NONMAX_SUPPRESSION, Nan::New<v8::Integer>(cv::FastFeatureDetector::NONMAX_SUPPRESSION));
	FF_SET_JS_PROP(target, "FAST", fastTypes);

	FF_OBJ orbTypes = FF_NEW_OBJ();
	FF_SET_JS_PROP(orbTypes, HARRIS_SCORE, Nan::New<v8::Integer>(cv::ORB::HARRIS_SCORE));
	FF_SET_JS_PROP(orbTypes, FAST_SCORE, Nan::New<v8::Integer>(cv::ORB::FAST_SCORE));
	FF_SET_JS_PROP(orbTypes, kBytes, Nan::New<v8::Integer>(cv::ORB::kBytes));
	FF_SET_JS_PROP(target, "ORB", orbTypes);

	Nan::SetMethod(target, "drawKeyPoints", DrawKeyPoints);
	Nan::SetMethod(target, "drawMatches", DrawMatches);
};

NAN_METHOD(Features2d::DrawKeyPoints) {
	FF_METHOD_CONTEXT("DrawKeyPoints");

	FF_ARG_INSTANCE(0, cv::Mat img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_ARRAY(1, FF_ARR jsKps);
	FF_UNPACK_KEYPOINT_ARRAY(kps, jsKps);

	FF_OBJ jsMat = FF_NEW_INSTANCE(Mat::constructor);
	cv::drawKeypoints(img, kps, FF_UNWRAP_MAT_AND_GET(jsMat));
	FF_RETURN(jsMat);
}

NAN_METHOD(Features2d::DrawMatches) {
	FF_METHOD_CONTEXT("DrawMatches");

	FF_ARG_INSTANCE(0, cv::Mat img1, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Mat img2, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_ARRAY(2, FF_ARR jsKps1);
	FF_ARG_ARRAY(3, FF_ARR jsKps2);
	FF_ARG_ARRAY(4, FF_ARR jsMatches);
	FF_UNPACK_KEYPOINT_ARRAY(kps1, jsKps1);
	FF_UNPACK_KEYPOINT_ARRAY(kps2, jsKps2);
	std::vector<cv::DMatch> dMatches;
	for (int i = 0; i < jsMatches->Length(); i++) {
		DescriptorMatch* match = FF_UNWRAP(FF_CAST_OBJ(jsMatches->Get(i)), DescriptorMatch);
		dMatches.push_back(match->dmatch);
	}

	FF_OBJ jsMat = FF_NEW_INSTANCE(Mat::constructor);
	cv::drawMatches(img1, kps1, img2, kps2, dMatches, FF_UNWRAP_MAT_AND_GET(jsMat));
	FF_RETURN(jsMat);
}