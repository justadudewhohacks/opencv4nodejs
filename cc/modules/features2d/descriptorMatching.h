#include "macros.h"
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
	static NAN_METHOD(MatchFlannBasedAsync);
	static NAN_METHOD(MatchBruteForceAsync);
	static NAN_METHOD(MatchBruteForceL1Async);
	static NAN_METHOD(MatchBruteForceHammingAsync);
	static NAN_METHOD(MatchBruteForceHammingLutAsync);
	static NAN_METHOD(MatchBruteForceSL2Async);
#if CV_VERSION_MINOR < 2
	static void match(Nan::NAN_METHOD_ARGS_TYPE info, std::string matcherType);
	static void matchAsync(Nan::NAN_METHOD_ARGS_TYPE info, std::string matcherType);
#else
	static void match(Nan::NAN_METHOD_ARGS_TYPE info, int matcherType);
	static void matchAsync(Nan::NAN_METHOD_ARGS_TYPE info, int matcherType);
#endif

	struct MatchContext {
	public:
		cv::Ptr<cv::DescriptorMatcher> matcher;
		cv::Mat descFrom;
		cv::Mat descTo;
		std::vector<cv::DMatch> dmatches;

		const char* execute() {
			matcher->match(descFrom, descTo, dmatches);
			return "";
		}

		FF_VAL getReturnValue() {
			FF_ARR jsMatches = FF_NEW_ARRAY(dmatches.size());
			uint i = 0;
			for (auto dmatch : dmatches) {
				FF_OBJ jsMatch = FF_NEW_INSTANCE(DescriptorMatch::constructor);
				FF_UNWRAP(jsMatch, DescriptorMatch)->dmatch = dmatch;
				jsMatches->Set(i++, jsMatch);
			}
			return jsMatches;
		}
	};
};

#endif