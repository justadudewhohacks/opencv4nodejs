#include "descriptorMatchingKnn.h"
#include "Workers.h"

NAN_MODULE_INIT(DescriptorMatchingKnn::Init) {
	Nan::SetMethod(target, "matchKnnFlannBased", MatchKnnFlannBased);
	Nan::SetMethod(target, "matchKnnBruteForce", MatchKnnBruteForce);
	Nan::SetMethod(target, "matchKnnBruteForceL1", MatchKnnBruteForceL1);
	Nan::SetMethod(target, "matchKnnBruteForceHamming", MatchKnnBruteForceHamming);
	Nan::SetMethod(target, "matchKnnFlannBasedAsync", MatchKnnFlannBasedAsync);
	Nan::SetMethod(target, "matchKnnBruteForceAsync", MatchKnnBruteForceAsync);
	Nan::SetMethod(target, "matchKnnBruteForceL1Async", MatchKnnBruteForceL1Async);
	Nan::SetMethod(target, "matchKnnBruteForceHammingAsync", MatchKnnBruteForceHammingAsync);
#if 2 <= CV_VERSION_MINOR
	Nan::SetMethod(target, "matchKnnBruteForceHammingLut", MatchKnnBruteForceHammingLut);
	Nan::SetMethod(target, "matchKnnBruteForceSL2", MatchKnnBruteForceSL2);
	Nan::SetMethod(target, "matchKnnBruteForceHammingLutAsync", MatchKnnBruteForceHammingLutAsync);
	Nan::SetMethod(target, "matchKnnBruteForceSL2Async", MatchKnnBruteForceSL2Async);
#endif
};

#if CV_VERSION_MINOR < 2

NAN_METHOD(DescriptorMatchingKnn::MatchKnnFlannBased) {
	matchKnn(info, "FlannBased");
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForce) {
	matchKnn(info, "BruteForce");
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceL1) {
	matchKnn(info, "BruteForce-L1");
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceHamming) {
	matchKnn(info, "BruteForce-Hamming");
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnFlannBasedAsync) {
	matchKnnAsync(info, "FlannBased");
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceAsync) {
	matchKnnAsync(info, "BruteForce");
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceL1Async) {
	matchKnnAsync(info, "BruteForce-L1");
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceHammingAsync) {
	matchKnnAsync(info, "BruteForce-Hamming");
}

#else

NAN_METHOD(DescriptorMatchingKnn::MatchKnnFlannBased) {
	matchKnn(info, cv::DescriptorMatcher::FLANNBASED);
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForce) {
	matchKnn(info, cv::DescriptorMatcher::BRUTEFORCE);
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceL1) {
	matchKnn(info, cv::DescriptorMatcher::BRUTEFORCE_L1);
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceHamming) {
	matchKnn(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMING);
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceHammingLut) {
	matchKnn(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMINGLUT);
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceSL2) {
	matchKnn(info, cv::DescriptorMatcher::BRUTEFORCE_SL2);
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnFlannBasedAsync) {
	matchKnnAsync(info, cv::DescriptorMatcher::FLANNBASED);
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceAsync) {
	matchKnnAsync(info, cv::DescriptorMatcher::BRUTEFORCE);
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceL1Async) {
	matchKnnAsync(info, cv::DescriptorMatcher::BRUTEFORCE_L1);
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceHammingAsync) {
	matchKnnAsync(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMING);
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceHammingLutAsync) {
	matchKnnAsync(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMINGLUT);
}

NAN_METHOD(DescriptorMatchingKnn::MatchKnnBruteForceSL2Async) {
	matchKnnAsync(info, cv::DescriptorMatcher::BRUTEFORCE_SL2);
}

#endif

#if CV_VERSION_MINOR < 2
void DescriptorMatchingKnn::matchKnn(Nan::NAN_METHOD_ARGS_TYPE info, std::string matcherType) {
#else
void DescriptorMatchingKnn::matchKnn(Nan::NAN_METHOD_ARGS_TYPE info, int matcherType) {
#endif
	FF_METHOD_CONTEXT("matchKnn");

	FF_ARG_INSTANCE(0, cv::Mat descFrom, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Mat descTo, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INT(2, int k);

	std::vector<std::vector<cv::DMatch>> dmatches;
	cv::DescriptorMatcher::create(matcherType)->knnMatch(descFrom, descTo, dmatches, k);

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
	FF_RETURN(jsMatches);
}

#if CV_VERSION_MINOR < 2
void DescriptorMatchingKnn::matchKnnAsync(Nan::NAN_METHOD_ARGS_TYPE info, std::string matcherType) {
#else
void DescriptorMatchingKnn::matchKnnAsync(Nan::NAN_METHOD_ARGS_TYPE info, int matcherType) {
#endif
	FF_METHOD_CONTEXT("matchKnnAsync");

	MatchContext ctx;
	ctx.matcher = cv::DescriptorMatcher::create(matcherType);
	FF_ARG_INSTANCE(0, ctx.descFrom, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(1, ctx.descTo, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INT(2, ctx.k);
	FF_ARG_FUNC(3, v8::Local<v8::Function> cbFunc);

	Nan::AsyncQueueWorker(new GenericAsyncWorker<MatchContext>(
		new Nan::Callback(cbFunc),
		ctx
	));
}