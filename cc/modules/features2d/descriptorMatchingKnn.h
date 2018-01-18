#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include "Mat.h"
#include "KeyPoint.h"
#include "DescriptorMatch.h"

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

	struct MatchContext {
	public:
		cv::Ptr<cv::DescriptorMatcher> matcher;
		cv::Mat descFrom;
		cv::Mat descTo;
		int k;
		std::vector<std::vector<cv::DMatch>> dmatches;

		const char* execute() {
			matcher->knnMatch(descFrom, descTo, dmatches, k);
			return "";
		}

		FF_VAL getReturnValue() {
			FF_ARR jsMatches = FF_NEW_ARRAY(dmatches.size());
			uint i = 0;
			for (auto dmatch : dmatches) {
				FF_ARR jsMatchesKnn = FF_NEW_ARRAY(dmatch.size());
				uint j = 0;
				for (auto dmatchKnn : dmatch) {
					FF_OBJ jsMatchKnn = FF_NEW_INSTANCE(DescriptorMatch::constructor);
					FF_UNWRAP(jsMatchKnn, DescriptorMatch)->dmatch = dmatchKnn;
					jsMatchesKnn->Set(j++, jsMatchKnn);
				}
				jsMatches->Set(i++, jsMatchesKnn);
			}
			return jsMatches;
		}
	};
};

#endif