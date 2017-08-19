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

	target->Set(FF_V8STRING("cvTypes"), cvTypes);
}