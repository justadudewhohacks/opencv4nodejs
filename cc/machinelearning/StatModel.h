#include "macros.h"
#include <opencv2/ml.hpp>

#ifndef __FF_STATMODEL_H__
#define __FF_STATMODEL_H__

class StatModel: public Nan::ObjectWrap {
public:
	cv::Ptr<cv::ml::SVM> svm;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif