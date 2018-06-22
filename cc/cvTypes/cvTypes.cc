#include "cvTypes.h"
#include "matTypes.h"
#include "imgprocConstants.h"
#include "photoConstants.h"
#include "videoCaptureProps.h"

using namespace cv;

void CvTypes::Init(v8::Local<v8::Object> target) {
	initMatTypes(target);
	ImgprocConstants::Init(target);
	PhotoConstants::Init(target);
	VideoCaptureProps::Init(target);

	FF_SET_CV_CONSTANT(target, NORM_INF);
	FF_SET_CV_CONSTANT(target, NORM_L1);
	FF_SET_CV_CONSTANT(target, NORM_L2);
	FF_SET_CV_CONSTANT(target, NORM_L2SQR);
	FF_SET_CV_CONSTANT(target, NORM_HAMMING);
	FF_SET_CV_CONSTANT(target, NORM_HAMMING2);
	FF_SET_CV_CONSTANT(target, NORM_TYPE_MASK);
	FF_SET_CV_CONSTANT(target, NORM_RELATIVE);
	FF_SET_CV_CONSTANT(target, NORM_MINMAX);

	FF_SET_CV_CONSTANT(target, CC_STAT_LEFT);
	FF_SET_CV_CONSTANT(target, CC_STAT_TOP);
	FF_SET_CV_CONSTANT(target, CC_STAT_WIDTH);
	FF_SET_CV_CONSTANT(target, CC_STAT_HEIGHT);
	FF_SET_CV_CONSTANT(target, CC_STAT_AREA);
	FF_SET_CV_CONSTANT(target, CC_STAT_MAX);

	FF_SET_CV_CONSTANT(target, CHAIN_APPROX_NONE);
	FF_SET_CV_CONSTANT(target, CHAIN_APPROX_SIMPLE);
	FF_SET_CV_CONSTANT(target, CHAIN_APPROX_TC89_L1);
	FF_SET_CV_CONSTANT(target, CHAIN_APPROX_TC89_KCOS);

	FF_SET_CV_CONSTANT(target, DIST_USER);
	FF_SET_CV_CONSTANT(target, DIST_L1);
	FF_SET_CV_CONSTANT(target, DIST_L2);
	FF_SET_CV_CONSTANT(target, DIST_C);
	FF_SET_CV_CONSTANT(target, DIST_L12);
	FF_SET_CV_CONSTANT(target, DIST_FAIR);
	FF_SET_CV_CONSTANT(target, DIST_WELSCH);
	FF_SET_CV_CONSTANT(target, DIST_HUBER);

	FF_SET_CV_CONSTANT(target, DIST_MASK_3);
	FF_SET_CV_CONSTANT(target, DIST_MASK_5);
	FF_SET_CV_CONSTANT(target, DIST_MASK_PRECISE);

	FF_SET_CV_CONSTANT(target, DIST_LABEL_CCOMP);
	FF_SET_CV_CONSTANT(target, DIST_LABEL_PIXEL);

	FF_SET_CV_CONSTANT(target, RETR_EXTERNAL);
	FF_SET_CV_CONSTANT(target, RETR_LIST);
	FF_SET_CV_CONSTANT(target, RETR_CCOMP);
	FF_SET_CV_CONSTANT(target, RETR_TREE);
	FF_SET_CV_CONSTANT(target, RETR_FLOODFILL);

	FF_SET_CV_CONSTANT(target, CV_CONTOURS_MATCH_I1);
	FF_SET_CV_CONSTANT(target, CV_CONTOURS_MATCH_I2);
	FF_SET_CV_CONSTANT(target, CV_CONTOURS_MATCH_I3);

	FF_SET_CV_CONSTANT(target, FONT_HERSHEY_SIMPLEX);
	FF_SET_CV_CONSTANT(target, FONT_HERSHEY_PLAIN);
	FF_SET_CV_CONSTANT(target, FONT_HERSHEY_DUPLEX);
	FF_SET_CV_CONSTANT(target, FONT_HERSHEY_COMPLEX);
	FF_SET_CV_CONSTANT(target, FONT_HERSHEY_TRIPLEX);
	FF_SET_CV_CONSTANT(target, FONT_HERSHEY_COMPLEX_SMALL);
	FF_SET_CV_CONSTANT(target, FONT_HERSHEY_SCRIPT_SIMPLEX);
	FF_SET_CV_CONSTANT(target, FONT_HERSHEY_SCRIPT_COMPLEX);
	FF_SET_CV_CONSTANT(target, FONT_ITALIC);

	FF_SET_CV_CONSTANT(target, FILLED);
	FF_SET_CV_CONSTANT(target, LINE_4);
	FF_SET_CV_CONSTANT(target, LINE_8);
	FF_SET_CV_CONSTANT(target, LINE_AA);

	FF_SET_CV_CONSTANT(target, KMEANS_RANDOM_CENTERS);
	FF_SET_CV_CONSTANT(target, KMEANS_PP_CENTERS);
	FF_SET_CV_CONSTANT(target, KMEANS_USE_INITIAL_LABELS);

	v8::Local<v8::Object> termCriteriaTypes = Nan::New<v8::Object>();
	FF_SET_JS_PROP(termCriteriaTypes, COUNT, Nan::New<v8::Integer>(cv::TermCriteria::COUNT));
	FF_SET_JS_PROP(termCriteriaTypes, MAX_ITER, Nan::New<v8::Integer>(cv::TermCriteria::MAX_ITER));
	FF_SET_JS_PROP(termCriteriaTypes, EPS, Nan::New<v8::Integer>(cv::TermCriteria::EPS));
	target->Set(FF_NEW_STRING("termCriteria"), termCriteriaTypes);

	v8::Local<v8::Object> svmConstants = Nan::New<v8::Object>();
	FF_SET_JS_PROP(svmConstants, CUSTOM, Nan::New<v8::Integer>(ml::SVM::KernelTypes:: CUSTOM));
	FF_SET_JS_PROP(svmConstants, LINEAR, Nan::New<v8::Integer>(ml::SVM::KernelTypes::LINEAR));
	FF_SET_JS_PROP(svmConstants, POLY, Nan::New<v8::Integer>(ml::SVM::KernelTypes::POLY));
	FF_SET_JS_PROP(svmConstants, RBF, Nan::New<v8::Integer>(ml::SVM::KernelTypes::RBF));
	FF_SET_JS_PROP(svmConstants, SIGMOID, Nan::New<v8::Integer>(ml::SVM::KernelTypes::SIGMOID));
	FF_SET_JS_PROP(svmConstants, CHI2, Nan::New<v8::Integer>(ml::SVM::KernelTypes::CHI2));
	FF_SET_JS_PROP(svmConstants, INTER, Nan::New<v8::Integer>(ml::SVM::KernelTypes::INTER));

	FF_SET_JS_PROP(svmConstants, C, Nan::New<v8::Integer>(ml::SVM::ParamTypes::C));
	FF_SET_JS_PROP(svmConstants, COEF, Nan::New<v8::Integer>(ml::SVM::ParamTypes::COEF));
	FF_SET_JS_PROP(svmConstants, DEGREE, Nan::New<v8::Integer>(ml::SVM::ParamTypes::DEGREE));
	FF_SET_JS_PROP(svmConstants, GAMMA, Nan::New<v8::Integer>(ml::SVM::ParamTypes::GAMMA));
	FF_SET_JS_PROP(svmConstants, NU, Nan::New<v8::Integer>(ml::SVM::ParamTypes::NU));
	FF_SET_JS_PROP(svmConstants, P, Nan::New<v8::Integer>(ml::SVM::ParamTypes::P));

	v8::Local<v8::Object> mlConstants = Nan::New<v8::Object>();
	FF_SET_JS_PROP(mlConstants, COL_SAMPLE, Nan::New<v8::Integer>(ml::SampleTypes::COL_SAMPLE));
	FF_SET_JS_PROP(mlConstants, ROW_SAMPLE, Nan::New<v8::Integer>(ml::SampleTypes::ROW_SAMPLE));

	FF_SET_JS_PROP(mlConstants, VAR_CATEGORICAL, Nan::New<v8::Integer>(ml::VariableTypes::VAR_CATEGORICAL));
	FF_SET_JS_PROP(mlConstants, VAR_NUMERICAL, Nan::New<v8::Integer>(ml::VariableTypes::VAR_NUMERICAL));
	FF_SET_JS_PROP(mlConstants, VAR_ORDERED, Nan::New<v8::Integer>(ml::VariableTypes::VAR_ORDERED));
	mlConstants->Set(FF_NEW_STRING("SVM"), svmConstants);
	target->Set(FF_NEW_STRING("ml"), mlConstants);

	v8::Local<v8::Object> statModelCostants = Nan::New<v8::Object>();
	FF_SET_JS_PROP(statModelCostants, COMPRESSED_INPUT, Nan::New<v8::Integer>(ml::StatModel::Flags::COMPRESSED_INPUT));
	FF_SET_JS_PROP(statModelCostants, PREPROCESSED_INPUT, Nan::New<v8::Integer>(ml::StatModel::Flags::PREPROCESSED_INPUT));
	FF_SET_JS_PROP(statModelCostants, RAW_OUTPUT, Nan::New<v8::Integer>(ml::StatModel::Flags::RAW_OUTPUT));
	FF_SET_JS_PROP(statModelCostants, UPDATE_MODEL, Nan::New<v8::Integer>(ml::StatModel::Flags::UPDATE_MODEL));
	target->Set(FF_NEW_STRING("statModel"), statModelCostants);

	v8::Local<v8::Object> haarCascades = Nan::New<v8::Object>();
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_EYE, FF_NEW_STRING("./haarcascade_eye.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_EYE_TREE_EYEGLASSES, FF_NEW_STRING("./haarcascade_eye_tree_eyeglasses.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FRONTALCATFACE, FF_NEW_STRING("./haarcascade_frontalcatface.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FRONTALCATFACE_EXTENDED, FF_NEW_STRING("./haarcascade_frontalcatface_extended.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FRONTALFACE_ALT, FF_NEW_STRING("./haarcascade_frontalface_alt.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FRONTALFACE_ALT2, FF_NEW_STRING("./haarcascade_frontalface_alt2.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FRONTALFACE_ALT_TREE, FF_NEW_STRING("./haarcascade_frontalface_alt_tree.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FRONTALFACE_DEFAULT, FF_NEW_STRING("./haarcascade_frontalface_default.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_FULLBODY, FF_NEW_STRING("./haarcascade_fullbody.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_LEFTEYE_2SPLITS, FF_NEW_STRING("./haarcascade_lefteye_2splits.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_LICENCE_PLATE_RUS_16STAGES, FF_NEW_STRING("./haarcascade_licence_plate_rus_16stages.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_LOWERBODY, FF_NEW_STRING("./haarcascade_lowerbody.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_PROFILEFACE, FF_NEW_STRING("./haarcascade_profileface.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_RIGHTEYE_2SPLITS, FF_NEW_STRING("./haarcascade_righteye_2splits.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_RUSSIAN_PLATE_NUMBER, FF_NEW_STRING("./haarcascade_russian_plate_number.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_SMILE, FF_NEW_STRING("./haarcascade_smile.xml"));
	FF_SET_CONST_WITH_VALUE(haarCascades, HAAR_UPPERBODY, FF_NEW_STRING("./haarcascade_upperbody.xml"));
	target->Set(FF_NEW_STRING("haarCascades"), haarCascades);

	v8::Local<v8::Object> lbpCascades = Nan::New<v8::Object>();
	FF_SET_CONST_WITH_VALUE(lbpCascades, LBP_FRONTALCATFACE, FF_NEW_STRING("./lbpcascade_frontalcatface.xml"));
	FF_SET_CONST_WITH_VALUE(lbpCascades, LBP_FRONTALFACE, FF_NEW_STRING("./lbpcascade_frontalface.xml"));
	FF_SET_CONST_WITH_VALUE(lbpCascades, LBP_FRONTALFACE_IMPROVED, FF_NEW_STRING("./lbpcascade_frontalface_improved.xml"));
	FF_SET_CONST_WITH_VALUE(lbpCascades, LBP_PROFILEFACE, FF_NEW_STRING("./lbpcascade_profileface.xml"));
	FF_SET_CONST_WITH_VALUE(lbpCascades, LBP_SILVERWARE, FF_NEW_STRING("./lbpcascade_silverware.xml"));
	target->Set(FF_NEW_STRING("lbpCascades"), lbpCascades);

	FF_SET_JS_PROP(target, REGULAR, Nan::New<v8::Integer>(0));
	FF_SET_CV_CONSTANT(target, LMEDS);
	FF_SET_CV_CONSTANT(target, RANSAC);
	FF_SET_CV_CONSTANT(target, RHO);

	FF_SET_CV_CONSTANT(target, SOLVEPNP_ITERATIVE);
	FF_SET_CV_CONSTANT(target, SOLVEPNP_EPNP);
	FF_SET_CV_CONSTANT(target, SOLVEPNP_P3P);
	FF_SET_CV_CONSTANT(target, SOLVEPNP_DLS);
	FF_SET_CV_CONSTANT(target, SOLVEPNP_UPNP);

	FF_SET_CV_CONSTANT(target, CALIB_CB_ADAPTIVE_THRESH);
	FF_SET_CV_CONSTANT(target, CALIB_CB_NORMALIZE_IMAGE);
	FF_SET_CV_CONSTANT(target, CALIB_CB_FILTER_QUADS);
	FF_SET_CV_CONSTANT(target, CALIB_CB_FAST_CHECK);

	FF_SET_CV_CONSTANT(target, CALIB_CB_SYMMETRIC_GRID);
	FF_SET_CV_CONSTANT(target, CALIB_CB_ASYMMETRIC_GRID);
	FF_SET_CV_CONSTANT(target, CALIB_CB_CLUSTERING);

	FF_SET_CV_CONSTANT(target, CALIB_USE_INTRINSIC_GUESS);
	FF_SET_CV_CONSTANT(target, CALIB_FIX_ASPECT_RATIO);
	FF_SET_CV_CONSTANT(target, CALIB_FIX_PRINCIPAL_POINT);
	FF_SET_CV_CONSTANT(target, CALIB_ZERO_TANGENT_DIST);
	FF_SET_CV_CONSTANT(target, CALIB_FIX_FOCAL_LENGTH);
	FF_SET_CV_CONSTANT(target, CALIB_FIX_K1);
	FF_SET_CV_CONSTANT(target, CALIB_FIX_K2);
	FF_SET_CV_CONSTANT(target, CALIB_FIX_K3);
	FF_SET_CV_CONSTANT(target, CALIB_FIX_K4);
	FF_SET_CV_CONSTANT(target, CALIB_FIX_K5);
	FF_SET_CV_CONSTANT(target, CALIB_FIX_K6);
	FF_SET_CV_CONSTANT(target, CALIB_RATIONAL_MODEL);
	FF_SET_CV_CONSTANT(target, CALIB_THIN_PRISM_MODEL);
	FF_SET_CV_CONSTANT(target, CALIB_FIX_S1_S2_S3_S4);
	FF_SET_CV_CONSTANT(target, CALIB_FIX_INTRINSIC);
	FF_SET_CV_CONSTANT(target, CALIB_SAME_FOCAL_LENGTH);
	FF_SET_CV_CONSTANT(target, CALIB_ZERO_DISPARITY);
	FF_SET_CV_CONSTANT(target, REDUCE_SUM);
	FF_SET_CV_CONSTANT(target, REDUCE_AVG);
	FF_SET_CV_CONSTANT(target, REDUCE_MAX);
	FF_SET_CV_CONSTANT(target, REDUCE_MIN);
#if CV_VERSION_MINOR > 0
	FF_SET_CV_CONSTANT(target, CALIB_TILTED_MODEL);
	FF_SET_CV_CONSTANT(target, CALIB_FIX_TAUX_TAUY);
	FF_SET_CV_CONSTANT(target, CALIB_USE_LU);
#endif
#if CV_VERSION_MINOR > 1
	FF_SET_CV_CONSTANT(target, CALIB_USE_QR);
#endif
#if CV_VERSION_MINOR > 2
	FF_SET_CV_CONSTANT(target, SOLVEPNP_AP3P);
	FF_SET_CV_CONSTANT(target, SOLVEPNP_MAX_COUNT);
	FF_SET_CV_CONSTANT(target, CALIB_FIX_TANGENT_DIST);
#endif
	FF_SET_CV_CONSTANT(target, FM_7POINT);
	FF_SET_CV_CONSTANT(target, FM_8POINT);
	FF_SET_CV_CONSTANT(target, FM_LMEDS);
	FF_SET_CV_CONSTANT(target, FM_RANSAC);
#if CV_VERSION_MINOR > 1
	FF_SET_CV_CONSTANT(target, ROTATE_90_CLOCKWISE);
	FF_SET_CV_CONSTANT(target, ROTATE_180);
	FF_SET_CV_CONSTANT(target, ROTATE_90_COUNTERCLOCKWISE);
#endif
}
