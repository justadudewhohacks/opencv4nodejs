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

	v8::Local<v8::Object> distanceTypes = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(distanceTypes, DIST_USER);
	FF_SET_CV_CONSTANT(distanceTypes, DIST_L1);
	FF_SET_CV_CONSTANT(distanceTypes, DIST_L2);
	FF_SET_CV_CONSTANT(distanceTypes, DIST_C);
	FF_SET_CV_CONSTANT(distanceTypes, DIST_L12);
	FF_SET_CV_CONSTANT(distanceTypes, DIST_FAIR);
	FF_SET_CV_CONSTANT(distanceTypes, DIST_WELSCH);
	FF_SET_CV_CONSTANT(distanceTypes, DIST_HUBER);
	cvTypes->Set(FF_V8STRING("distanceTypes"), distanceTypes);

	v8::Local<v8::Object> distanceTransformMasks = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(distanceTransformMasks, DIST_MASK_3);
	FF_SET_CV_CONSTANT(distanceTransformMasks, DIST_MASK_5);
	FF_SET_CV_CONSTANT(distanceTransformMasks, DIST_MASK_PRECISE);
	cvTypes->Set(FF_V8STRING("distanceTransformMasks"), distanceTransformMasks);

	v8::Local<v8::Object> retrievalModes = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(retrievalModes, RETR_EXTERNAL);
	FF_SET_CV_CONSTANT(retrievalModes, RETR_LIST);
	FF_SET_CV_CONSTANT(retrievalModes, RETR_CCOMP);
	FF_SET_CV_CONSTANT(retrievalModes, RETR_TREE);
	FF_SET_CV_CONSTANT(retrievalModes, RETR_FLOODFILL);
	cvTypes->Set(FF_V8STRING("retrievalModes"), retrievalModes);

	v8::Local<v8::Object> shapeMatchModes = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(shapeMatchModes, CV_CONTOURS_MATCH_I1);
	FF_SET_CV_CONSTANT(shapeMatchModes, CV_CONTOURS_MATCH_I2);
	FF_SET_CV_CONSTANT(shapeMatchModes, CV_CONTOURS_MATCH_I3);
	cvTypes->Set(FF_V8STRING("shapeMatchModes"), shapeMatchModes);
	
	v8::Local<v8::Object> hersheyFonts = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(hersheyFonts, FONT_HERSHEY_SIMPLEX);
	FF_SET_CV_CONSTANT(hersheyFonts, FONT_HERSHEY_PLAIN);
	FF_SET_CV_CONSTANT(hersheyFonts, FONT_HERSHEY_DUPLEX);
	FF_SET_CV_CONSTANT(hersheyFonts, FONT_HERSHEY_COMPLEX);
	FF_SET_CV_CONSTANT(hersheyFonts, FONT_HERSHEY_TRIPLEX);
	FF_SET_CV_CONSTANT(hersheyFonts, FONT_HERSHEY_COMPLEX_SMALL);
	FF_SET_CV_CONSTANT(hersheyFonts, FONT_HERSHEY_SCRIPT_SIMPLEX);
	FF_SET_CV_CONSTANT(hersheyFonts, FONT_HERSHEY_SCRIPT_COMPLEX);
	FF_SET_CV_CONSTANT(hersheyFonts, FONT_ITALIC);
	cvTypes->Set(FF_V8STRING("hersheyFonts"), hersheyFonts);

	v8::Local<v8::Object> haarCascades = Nan::New<v8::Object>();
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_EYE, FF_V8STRING("./haarcascade_eye.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_EYE_TREE_EYEGLASSES, FF_V8STRING("./haarcascade_eye_tree_eyeglasses.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FRONTALCATFACE, FF_V8STRING("./haarcascade_frontalcatface.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FRONTALCATFACE_EXTENDED, FF_V8STRING("./haarcascade_frontalcatface_extended.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FRONTALFACE_ALT, FF_V8STRING("./haarcascade_frontalface_alt.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FRONTALFACE_ALT2, FF_V8STRING("./haarcascade_frontalface_alt2.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FRONTALFACE_ALT_TREE, FF_V8STRING("./haarcascade_frontalface_alt_tree.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FRONTALFACE_DEFAULT, FF_V8STRING("./haarcascade_frontalface_default.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FULLBODY, FF_V8STRING("./haarcascade_fullbody.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_LEFTEYE_2SPLITS, FF_V8STRING("./haarcascade_lefteye_2splits.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_LICENCE_PLATE_RUS_16STAGES, FF_V8STRING("./haarcascade_licence_plate_rus_16stages.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_LOWERBODY, FF_V8STRING("./haarcascade_lowerbody.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_PROFILEFACE, FF_V8STRING("./haarcascade_profileface.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_RIGHTEYE_2SPLITS, FF_V8STRING("./haarcascade_righteye_2splits.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_RUSSIAN_PLATE_NUMBER, FF_V8STRING("./haarcascade_russian_plate_number.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_SMILE, FF_V8STRING("./haarcascade_smile.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_UPPERBODY, FF_V8STRING("./haarcascade_upperbody.xml"));
	cvTypes->Set(FF_V8STRING("haarCascades"), haarCascades);

	target->Set(FF_V8STRING("cvTypes"), cvTypes);
}