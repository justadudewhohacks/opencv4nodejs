#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "descriptorMatchingKnn.h"

NAN_MODULE_INIT(DescriptorMatchingKnn::Init) {
	Nan::SetMethod(target, "matchKnnFlannBased", MatchKnnFlannBased);
	Nan::SetMethod(target, "matchKnnBruteForce", MatchKnnBruteForce);
	Nan::SetMethod(target, "matchKnnBruteForceL1", MatchKnnBruteForceL1);
	Nan::SetMethod(target, "matchKnnBruteForceHamming", MatchKnnBruteForceHamming);
	Nan::SetMethod(target, "matchKnnFlannBasedAsync", MatchKnnFlannBasedAsync);
	Nan::SetMethod(target, "matchKnnBruteForceAsync", MatchKnnBruteForceAsync);
	Nan::SetMethod(target, "matchKnnBruteForceL1Async", MatchKnnBruteForceL1Async);
	Nan::SetMethod(target, "matchKnnBruteForceHammingAsync", MatchKnnBruteForceHammingAsync);
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
	Nan::SetMethod(target, "matchKnnBruteForceHammingLut", MatchKnnBruteForceHammingLut);
	Nan::SetMethod(target, "matchKnnBruteForceSL2", MatchKnnBruteForceSL2);
	Nan::SetMethod(target, "matchKnnBruteForceHammingLutAsync", MatchKnnBruteForceHammingLutAsync);
	Nan::SetMethod(target, "matchKnnBruteForceSL2Async", MatchKnnBruteForceSL2Async);
#endif
};

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)

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

#else

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

#endif

struct DescriptorMatchingKnn::MatchKnnWorker : public CatchCvExceptionWorker {
public:
	cv::Ptr<cv::DescriptorMatcher> matcher;
	MatchKnnWorker(cv::Ptr<cv::DescriptorMatcher> _matcher) {
		this->matcher = _matcher;
	}

	cv::Mat descFrom;
	cv::Mat descTo;
	int k;
	std::vector<std::vector<cv::DMatch>> dmatches;

	std::string executeCatchCvExceptionWorker() {
		matcher->knnMatch(descFrom, descTo, dmatches, k);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Mat::Converter::arg(0, &descFrom, info)
			|| Mat::Converter::arg(1, &descTo, info)
			|| FF::IntConverter::arg(2, &k, info);
	}

	v8::Local<v8::Value> getReturnValue() {
		return DescriptorMatch::ArrayOfArraysConverter::wrap(dmatches);
	}
};

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
void DescriptorMatchingKnn::matchKnn(Nan::NAN_METHOD_ARGS_TYPE info, cv::DescriptorMatcher::MatcherType matcherType) {
#elif CV_VERSION_GREATER_EQUAL(3, 2, 0)
void DescriptorMatchingKnn::matchKnn(Nan::NAN_METHOD_ARGS_TYPE info, int matcherType) {
#else
void DescriptorMatchingKnn::matchKnn(Nan::NAN_METHOD_ARGS_TYPE info, std::string matcherType) {
#endif
	FF::executeSyncBinding(
		std::make_shared<MatchKnnWorker>(cv::DescriptorMatcher::create(matcherType)),
		"MSERDetector::MatchKnn",
		info
	);
}

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
void DescriptorMatchingKnn::matchKnnAsync(Nan::NAN_METHOD_ARGS_TYPE info, cv::DescriptorMatcher::MatcherType matcherType) {
#elif CV_VERSION_GREATER_EQUAL(3, 2, 0)
void DescriptorMatchingKnn::matchKnnAsync(Nan::NAN_METHOD_ARGS_TYPE info, int matcherType) {
#else
void DescriptorMatchingKnn::matchKnnAsync(Nan::NAN_METHOD_ARGS_TYPE info, std::string matcherType) {
#endif
	FF::executeAsyncBinding(
		std::make_shared<MatchKnnWorker>(cv::DescriptorMatcher::create(matcherType)),
		"MSERDetector::MatchKnnAsync",
		info
	);
}

#endif
