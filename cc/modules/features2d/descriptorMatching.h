#include <nan.h>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include "Mat.h"
#include "KeyPoint.h"
#include "DescriptorMatch.h"

#ifndef __FF_DESCRIPTORMATCHING_H__
#define __FF_DESCRIPTORMATCHING_H__

class DescriptorMatching : public Nan::ObjectWrap {
public:
	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(MatchFlannBased);
	static NAN_METHOD(MatchBruteForce);
	static NAN_METHOD(MatchBruteForceL1);
	static NAN_METHOD(MatchBruteForceHamming);
	static NAN_METHOD(MatchBruteForceHammingLut);
	static NAN_METHOD(MatchBruteForceSL2);

	static void match(Nan::NAN_METHOD_ARGS_TYPE info, int matcherType);
};

#endif