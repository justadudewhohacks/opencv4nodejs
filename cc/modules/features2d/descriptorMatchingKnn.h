#include "macros.h"
#include "NativeNodeUtils.h"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include "Mat.h"
#include "KeyPoint.h"
#include "DescriptorMatch.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_DESCRIPTORMATCHINGKNN_H__
#define __FF_DESCRIPTORMATCHINGKNN_H__

class DescriptorMatchingKnn : public Nan::ObjectWrap {
public:
	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(MatchKnnFlannBased);
	static NAN_METHOD(MatchKnnBruteForce);
	static NAN_METHOD(MatchKnnBruteForceL1);
	static NAN_METHOD(MatchKnnBruteForceHamming);
	static NAN_METHOD(MatchKnnBruteForceHammingLut);
	static NAN_METHOD(MatchKnnBruteForceSL2);
	static NAN_METHOD(MatchKnnFlannBasedAsync);
	static NAN_METHOD(MatchKnnBruteForceAsync);
	static NAN_METHOD(MatchKnnBruteForceL1Async);
	static NAN_METHOD(MatchKnnBruteForceHammingAsync);
	static NAN_METHOD(MatchKnnBruteForceHammingLutAsync);
	static NAN_METHOD(MatchKnnBruteForceSL2Async);
#if CV_VERSION_MINOR < 2
	static void matchKnn(Nan::NAN_METHOD_ARGS_TYPE info, std::string matcherType);
	static void matchKnnAsync(Nan::NAN_METHOD_ARGS_TYPE info, std::string matcherType);
#else
	static void matchKnn(Nan::NAN_METHOD_ARGS_TYPE info, int matcherType);
	static void matchKnnAsync(Nan::NAN_METHOD_ARGS_TYPE info, int matcherType);
#endif

	struct MatchKnnWorker;
};

#endif