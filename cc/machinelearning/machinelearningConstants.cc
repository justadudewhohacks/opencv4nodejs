#include "opencv_modules.h"

#ifdef HAVE_OPENCV_ML

#include "machinelearningConstants.h"

using namespace cv;

void MachineLearningConstants::Init(v8::Local<v8::Object> target) {
	v8::Local<v8::Object> svmConstants = Nan::New<v8::Object>();
	FF_SET_JS_PROP(svmConstants, CUSTOM, Nan::New<v8::Integer>(ml::SVM::KernelTypes::CUSTOM));
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
	Nan::Set(mlConstants, FF::newString("SVM"), svmConstants);
	Nan::Set(target, FF::newString("ml"), mlConstants);

	v8::Local<v8::Object> statModelCostants = Nan::New<v8::Object>();
	FF_SET_JS_PROP(statModelCostants, COMPRESSED_INPUT, Nan::New<v8::Integer>(ml::StatModel::Flags::COMPRESSED_INPUT));
	FF_SET_JS_PROP(statModelCostants, PREPROCESSED_INPUT, Nan::New<v8::Integer>(ml::StatModel::Flags::PREPROCESSED_INPUT));
	FF_SET_JS_PROP(statModelCostants, RAW_OUTPUT, Nan::New<v8::Integer>(ml::StatModel::Flags::RAW_OUTPUT));
	FF_SET_JS_PROP(statModelCostants, UPDATE_MODEL, Nan::New<v8::Integer>(ml::StatModel::Flags::UPDATE_MODEL));
	Nan::Set(target, FF::newString("statModel"), statModelCostants);
}

#endif
