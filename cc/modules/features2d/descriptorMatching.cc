#include "descriptorMatching.h"

NAN_MODULE_INIT(DescriptorMatching::Init) {
	Nan::SetMethod(target, "matchFlannBased", MatchFlannBased);
	Nan::SetMethod(target, "matchBruteForce", MatchBruteForce);
	Nan::SetMethod(target, "matchBruteForceL1", MatchBruteForceL1);
	Nan::SetMethod(target, "matchBruteForceHamming", MatchBruteForceHamming);
	Nan::SetMethod(target, "matchFlannBasedAsync", MatchFlannBasedAsync);
	Nan::SetMethod(target, "matchBruteForceAsync", MatchBruteForceAsync);
	Nan::SetMethod(target, "matchBruteForceL1Async", MatchBruteForceL1Async);
	Nan::SetMethod(target, "matchBruteForceHammingAsync", MatchBruteForceHammingAsync);
#if 2 <= CV_VERSION_MINOR
	Nan::SetMethod(target, "matchBruteForceHammingLut", MatchBruteForceHammingLut);
	Nan::SetMethod(target, "matchBruteForceSL2", MatchBruteForceSL2);
	Nan::SetMethod(target, "matchBruteForceHammingLutAsync", MatchBruteForceHammingLutAsync);
	Nan::SetMethod(target, "matchBruteForceSL2Async", MatchBruteForceSL2Async);
#endif
};

#if CV_VERSION_MINOR < 2

NAN_METHOD(DescriptorMatching::MatchFlannBased) {
	match(info, "FlannBased");
}

NAN_METHOD(DescriptorMatching::MatchBruteForce) {
	match(info, "BruteForce");
}

NAN_METHOD(DescriptorMatching::MatchBruteForceL1) {
	match(info, "BruteForce-L1");
}

NAN_METHOD(DescriptorMatching::MatchBruteForceHamming) {
	match(info, "BruteForce-Hamming");
}

NAN_METHOD(DescriptorMatching::MatchFlannBasedAsync) {
	matchAsync(info, "FlannBased");
}

NAN_METHOD(DescriptorMatching::MatchBruteForceAsync) {
	matchAsync(info, "BruteForce");
}

NAN_METHOD(DescriptorMatching::MatchBruteForceL1Async) {
	matchAsync(info, "BruteForce-L1");
}

NAN_METHOD(DescriptorMatching::MatchBruteForceHammingAsync) {
	matchAsync(info, "BruteForce-Hamming");
}

#else

NAN_METHOD(DescriptorMatching::MatchFlannBased) {
	match(info, cv::DescriptorMatcher::FLANNBASED);
}

NAN_METHOD(DescriptorMatching::MatchBruteForce) {
	match(info, cv::DescriptorMatcher::BRUTEFORCE);
}

NAN_METHOD(DescriptorMatching::MatchBruteForceL1) {
	match(info, cv::DescriptorMatcher::BRUTEFORCE_L1);
}

NAN_METHOD(DescriptorMatching::MatchBruteForceHamming) {
	match(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMING);
}

NAN_METHOD(DescriptorMatching::MatchBruteForceHammingLut) {
	match(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMINGLUT);
}

NAN_METHOD(DescriptorMatching::MatchBruteForceSL2) {
	match(info, cv::DescriptorMatcher::BRUTEFORCE_SL2);
}

NAN_METHOD(DescriptorMatching::MatchFlannBasedAsync) {
	matchAsync(info, cv::DescriptorMatcher::FLANNBASED);
}

NAN_METHOD(DescriptorMatching::MatchBruteForceAsync) {
	matchAsync(info, cv::DescriptorMatcher::BRUTEFORCE);
}

NAN_METHOD(DescriptorMatching::MatchBruteForceL1Async) {
	matchAsync(info, cv::DescriptorMatcher::BRUTEFORCE_L1);
}

NAN_METHOD(DescriptorMatching::MatchBruteForceHammingAsync) {
	matchAsync(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMING);
}

NAN_METHOD(DescriptorMatching::MatchBruteForceHammingLutAsync) {
	matchAsync(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMINGLUT);
}

NAN_METHOD(DescriptorMatching::MatchBruteForceSL2Async) {
	matchAsync(info, cv::DescriptorMatcher::BRUTEFORCE_SL2);
}

#endif

#if CV_VERSION_MINOR < 2
void DescriptorMatching::match(Nan::NAN_METHOD_ARGS_TYPE info, std::string matcherType) {
#else
void DescriptorMatching::match(Nan::NAN_METHOD_ARGS_TYPE info, int matcherType) {
#endif
	FF_METHOD_CONTEXT("match");
	
	FF_ARG_INSTANCE(0, cv::Mat descFrom, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Mat descTo, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

	std::vector<cv::DMatch> dmatches;
	cv::DescriptorMatcher::create(matcherType)->match(descFrom, descTo, dmatches);

	FF_ARR jsMatches = FF_NEW_ARRAY(dmatches.size());
	uint i = 0;
	for (auto dmatch : dmatches) {
		FF_OBJ jsMatch = FF_NEW_INSTANCE(DescriptorMatch::constructor);
		FF_UNWRAP(jsMatch, DescriptorMatch)->dmatch = dmatch;
		jsMatches->Set(i++, jsMatch);
	}
	FF_RETURN(jsMatches);
}

class AsyncMatchWorker : public Nan::AsyncWorker {
public:
	cv::Ptr<cv::DescriptorMatcher> matcher;
	cv::Mat descFrom;
	cv::Mat descTo;
	std::vector<cv::DMatch> dmatches;

	AsyncMatchWorker(
		Nan::Callback *callback,
		cv::Ptr<cv::DescriptorMatcher> matcher,
		cv::Mat descFrom,
		cv::Mat descTo
	) : Nan::AsyncWorker(callback), matcher(matcher), descFrom(descFrom), descTo(descTo) {}
	~AsyncMatchWorker() {}

	void Execute() {
		matcher->match(descFrom, descTo, dmatches);
	}

	void HandleOKCallback() {
		Nan::HandleScope scope;

		FF_ARR jsMatches = FF_NEW_ARRAY(dmatches.size());
		uint i = 0;
		for (auto dmatch : dmatches) {
			FF_OBJ jsMatch = FF_NEW_INSTANCE(DescriptorMatch::constructor);
			FF_UNWRAP(jsMatch, DescriptorMatch)->dmatch = dmatch;
			jsMatches->Set(i++, jsMatch);
		}

		FF_VAL argv[] = { Nan::Null(), jsMatches };
		callback->Call(2, argv);
	}
};

#if CV_VERSION_MINOR < 2
void DescriptorMatching::matchAsync(Nan::NAN_METHOD_ARGS_TYPE info, std::string matcherType) {
#else
void DescriptorMatching::matchAsync(Nan::NAN_METHOD_ARGS_TYPE info, int matcherType) {
#endif
	FF_METHOD_CONTEXT("matchAsync");

	FF_ARG_INSTANCE(0, cv::Mat descFrom, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_INSTANCE(1, cv::Mat descTo, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
	FF_ARG_FUNC(2, v8::Local<v8::Function> cbFunc);

	Nan::AsyncQueueWorker(new AsyncMatchWorker(
		new Nan::Callback(cbFunc),
		cv::DescriptorMatcher::create(matcherType),
		descFrom,
		descTo
	));
}