#include <opencv2/core.hpp>
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_TERMCRITERIA_H__
#define __FF_TERMCRITERIA_H__

class TermCriteria : public Nan::ObjectWrap {
public:
	cv::TermCriteria termCriteria;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER(TermCriteria, GetType, termCriteria.type);
	static FF_GETTER(TermCriteria, GetMaxCount, termCriteria.maxCount);
	static FF_GETTER(TermCriteria, GetEpsilon, termCriteria.epsilon);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::TermCriteria* getNativeObjectPtr() { return &termCriteria; }
	cv::TermCriteria getNativeObject() { return termCriteria; }

	typedef InstanceConverter<TermCriteria, cv::TermCriteria> Converter;

	static const char* getClassName() {
		return "TermCriteria";
	}
};

#endif