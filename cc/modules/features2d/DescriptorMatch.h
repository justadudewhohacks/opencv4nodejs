#include "macros.h"
#include "NativeNodeUtils.h"
#include <opencv2/features2d.hpp>

#ifndef __FF_DESCRIPTORMATCH_H__
#define __FF_DESCRIPTORMATCH_H__

class DescriptorMatch : public FF::ObjectWrap<DescriptorMatch, cv::DMatch> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "DescriptorMatch";
	}

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	FF_ACCESSORS(queryIdx, FF::IntConverter);
	FF_ACCESSORS(trainIdx, FF::IntConverter);
	FF_ACCESSORS(distance, FF::FloatConverter);
};

#endif