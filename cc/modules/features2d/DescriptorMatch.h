#include <nan.h>
#include "macros.h"

#ifndef __FF_DESCRIPTORMATCH_H__
#define __FF_DESCRIPTORMATCH_H__

class DescriptorMatch : public Nan::ObjectWrap {
public:
	int queryIdx;
	int trainIdx; 
  float distance;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static FF_GETTER(DescriptorMatch, GetQueryIdx, queryIdx)
	static FF_GETTER(DescriptorMatch, GetTrainIdx, trainIdx)
	static FF_GETTER(DescriptorMatch, GetDistance, distance)

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	void setNativeProps(cv::DMatch dmatch);
};

#endif