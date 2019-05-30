#include <opencv2/core.hpp>
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_TERMCRITERIA_H__
#define __FF_TERMCRITERIA_H__

class TermCriteria : public FF::ObjectWrap<TermCriteria> {
public:
	typedef cv::TermCriteria Type;

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "TermCriteria";
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static FF_GETTER(TermCriteria, GetType, self.type);
	static FF_GETTER(TermCriteria, GetMaxCount, self.maxCount);
	static FF_GETTER(TermCriteria, GetEpsilon, self.epsilon);
};

#endif