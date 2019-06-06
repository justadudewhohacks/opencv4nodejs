#include <opencv2/core.hpp>
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_TERMCRITERIA_H__
#define __FF_TERMCRITERIA_H__

class TermCriteria : public FF::ObjectWrap<TermCriteria, cv::TermCriteria> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "TermCriteria";
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	int type; //!< the type of termination criteria: COUNT, EPS or COUNT + EPS
	int maxCount; //!< the maximum number of iterations/elements
	double epsilon;

	FF_ACCESSORS(type, FF::IntConverter);
	FF_ACCESSORS(maxCount, FF::IntConverter);
	FF_ACCESSORS(epsilon, FF::DoubleConverter);
};

#endif