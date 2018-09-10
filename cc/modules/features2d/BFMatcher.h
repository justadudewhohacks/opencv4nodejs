#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include "KeyPoint.h"
#include "Mat.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_BFMATCHER_H__
#define __FF_BFMATCHER_H__

class BFMatcher : public Nan::ObjectWrap {
public:
    cv::BFMatcher bfmatcher;

	int normType;
	bool crossCheck;

	static FF_GETTER(BFMatcher, GetNormType, normType)
	static FF_GETTER(BFMatcher, GetCrossCheck, crossCheck)

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::BFMatcher* getNativeObjectPtr() { return &bfmatcher; }
	cv::BFMatcher getNativeObject() { return bfmatcher; }

	typedef InstanceConverter<BFMatcher, cv::BFMatcher> Converter;

	static NAN_MODULE_INIT(Init);

    static NAN_METHOD(New);
    static NAN_METHOD(match);
    static NAN_METHOD(matchAsync);

    static const char* getClassName() {
        return "BFMatcher";
    }
};

#endif
