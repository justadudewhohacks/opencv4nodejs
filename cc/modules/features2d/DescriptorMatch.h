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

	static FF_GETTER(DescriptorMatch, GetQueryIdx, self.queryIdx)
	static FF_GETTER(DescriptorMatch, GetTrainIdx, self.trainIdx)
	static FF_GETTER(DescriptorMatch, GetDistance, self.distance)
};

#endif