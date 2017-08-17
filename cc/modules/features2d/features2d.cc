#include "features2d.h"
#include "KeyPoint.h"
#include "KeyPointMatch.h"
#include "DescriptorMatch.h"
#include "descriptorMatching.h"
#include "detectors/AGASTDetector.h"
#include "detectors/AKAZEDetector.h"
#include "detectors/BRISKDetector.h"
#include "detectors/FASTDetector.h"
#include "detectors/GFTTDetector.h"
#include "detectors/KAZEDetector.h"
#include "detectors/MSERDetector.h"
#include "detectors/ORBDetector.h"

NAN_MODULE_INIT(Features2d::Init) {
	KeyPoint::Init(target);
	KeyPointMatch::Init(target);
	DescriptorMatch::Init(target);
	DescriptorMatching::Init(target);
	AGASTDetector::Init(target);
	AKAZEDetector::Init(target);
	BRISKDetector::Init(target);
	FASTDetector::Init(target);
	GFTTDetector::Init(target);
	KAZEDetector::Init(target);
	MSERDetector::Init(target);
	ORBDetector::Init(target);
	Nan::SetMethod(target, "drawKeyPoints", DrawKeyPoints);
	Nan::SetMethod(target, "drawMatches", DrawMatches);
};

NAN_METHOD(Features2d::DrawKeyPoints) {
	FF_REQUIRE_ARGS_OBJ("DrawKeyPoints");
	cv::Mat img;
	std::vector<cv::KeyPoint> kps;
	FF_GET_JSOBJ_REQUIRED(args, img, image, Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat);
	v8::Local<v8::Value> keypoints = FF_GET_JSPROP(args, keypoints);
	if (!keypoints->IsArray()) {
		return Nan::ThrowError("DrawKeyPoints - expected keypoints to be an Array of Keypoints");
	}
	FF_UNWRAP_KEYPOINT_ARRAY(FF_CAST_ARRAY(keypoints), kps);

	v8::Local<v8::Object> jsMat = FF_NEW(Mat::constructor);
	cv::drawKeypoints(img, kps, Nan::ObjectWrap::Unwrap<Mat>(jsMat)->mat);
	info.GetReturnValue().Set(jsMat);
}

NAN_METHOD(Features2d::DrawMatches) {
	FF_REQUIRE_ARGS_OBJ("DrawMatches");
	cv::Mat imgFrom, imgTo;
	v8::Local<v8::Value> keypoints1 = FF_GET_JSPROP(args, keypoints1);
	v8::Local<v8::Value> keypoints2 = FF_GET_JSPROP(args, keypoints2);
	std::vector<cv::KeyPoint> kpsFrom, kpsTo;
	v8::Local<v8::Value> jsMatches = FF_GET_JSPROP(args, matches1to2);

	FF_GET_JSOBJ_REQUIRED(args, imgFrom, img1, Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat);
	FF_GET_JSOBJ_REQUIRED(args, imgTo, img2, Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat);
	if (!keypoints1->IsArray()) {
		return Nan::ThrowError("DrawMatches - expected keypoints1 to be an Array of Keypoints");
	}
	if (!keypoints2->IsArray()) {
		return Nan::ThrowError("DrawMatches - expected keypoints2 to be an Array of Keypoints");
	}
	if (!jsMatches->IsArray()) {
		return Nan::ThrowError("DrawMatches - expected matches1to2 to be an Array of DescriptorMatches");
	}
	FF_UNWRAP_KEYPOINT_ARRAY(FF_CAST_ARRAY(keypoints1), kpsFrom);
	FF_UNWRAP_KEYPOINT_ARRAY(FF_CAST_ARRAY(keypoints2), kpsTo);

	v8::Local<v8::Array> jsMatchesArray = FF_CAST_ARRAY(jsMatches);
	std::vector<cv::DMatch> dMatches;
	for (uint i = 0; i < jsMatchesArray->Length(); i++) {
		DescriptorMatch* match = FF_UNWRAP(FF_CAST_OBJ(jsMatchesArray->Get(i)), DescriptorMatch);
		dMatches.push_back(cv::DMatch(match->queryIdx, match->trainIdx, match->distance));
	}

	v8::Local<v8::Object> jsMat = FF_NEW(Mat::constructor);
	cv::drawMatches(imgFrom, kpsFrom, imgTo, kpsTo, dMatches, Nan::ObjectWrap::Unwrap<Mat>(jsMat)->mat);
	info.GetReturnValue().Set(jsMat);
}