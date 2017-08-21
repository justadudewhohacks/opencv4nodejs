#include "cvTypes.h"
#include "matTypes.h"
#include "imgprocConstants.h"

using namespace cv;

void CvTypes::Init(v8::Local<v8::Object> target) {
	v8::Local<v8::Object> cvTypes = Nan::New<v8::Object>();
	initMatTypes(cvTypes);
	ImgprocConstants::Init(cvTypes);

	v8::Local<v8::Object> normTypes = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(normTypes, NORM_INF);
	FF_SET_CV_CONSTANT(normTypes, NORM_L1);
	FF_SET_CV_CONSTANT(normTypes, NORM_L2);
	FF_SET_CV_CONSTANT(normTypes, NORM_L2SQR);
	FF_SET_CV_CONSTANT(normTypes, NORM_HAMMING);
	FF_SET_CV_CONSTANT(normTypes, NORM_HAMMING2);
	FF_SET_CV_CONSTANT(normTypes, NORM_TYPE_MASK);
	FF_SET_CV_CONSTANT(normTypes, NORM_RELATIVE);
	FF_SET_CV_CONSTANT(normTypes, NORM_MINMAX);
	cvTypes->Set(FF_V8STRING("normTypes"), normTypes);

	v8::Local<v8::Object> connectedComponentsTypes = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(connectedComponentsTypes, CC_STAT_LEFT);
	FF_SET_CV_CONSTANT(connectedComponentsTypes, CC_STAT_TOP);
	FF_SET_CV_CONSTANT(connectedComponentsTypes, CC_STAT_WIDTH);
	FF_SET_CV_CONSTANT(connectedComponentsTypes, CC_STAT_HEIGHT);
	FF_SET_CV_CONSTANT(connectedComponentsTypes, CC_STAT_AREA);
	FF_SET_CV_CONSTANT(connectedComponentsTypes, CC_STAT_MAX);
	cvTypes->Set(FF_V8STRING("connectedComponentsTypes"), connectedComponentsTypes);

	v8::Local<v8::Object> contourApproximationModes = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(contourApproximationModes, CHAIN_APPROX_NONE);
	FF_SET_CV_CONSTANT(contourApproximationModes, CHAIN_APPROX_SIMPLE);
	FF_SET_CV_CONSTANT(contourApproximationModes, CHAIN_APPROX_TC89_L1);
	FF_SET_CV_CONSTANT(contourApproximationModes, CHAIN_APPROX_TC89_KCOS);
	cvTypes->Set(FF_V8STRING("contourApproximationModes"), contourApproximationModes);

	v8::Local<v8::Object> retrievalModes = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(retrievalModes, RETR_EXTERNAL);
	FF_SET_CV_CONSTANT(retrievalModes, RETR_LIST);
	FF_SET_CV_CONSTANT(retrievalModes, RETR_CCOMP);
	FF_SET_CV_CONSTANT(retrievalModes, RETR_TREE);
	FF_SET_CV_CONSTANT(retrievalModes, RETR_FLOODFILL);
	cvTypes->Set(FF_V8STRING("retrievalModes"), retrievalModes);

	target->Set(FF_V8STRING("cvTypes"), cvTypes);
}