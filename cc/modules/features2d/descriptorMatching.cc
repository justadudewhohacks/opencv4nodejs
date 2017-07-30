#include "descriptorMatching.h"

NAN_MODULE_INIT(DescriptorMatching::Init) {
	Nan::SetMethod(target, "matchFlannBased", MatchFlannBased);
	Nan::SetMethod(target, "matchBruteForce", MatchBruteForce);
	Nan::SetMethod(target, "matchBruteForceL1", MatchBruteForceL1);
	Nan::SetMethod(target, "matchBruteForceHamming", MatchBruteForceHamming);
	Nan::SetMethod(target, "matchBruteForceHammingLut", MatchBruteForceHammingLut);
	Nan::SetMethod(target, "matchBruteForceSL2", MatchBruteForceSL2);
};

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

void DescriptorMatching::match(Nan::NAN_METHOD_ARGS_TYPE info, int matcherType) {
	if (!info[0]->IsObject() || !info[1]->IsObject()) {
		return Nan::ThrowError("required argument descriptorsFrom, descriptorsTo");
	}

	cv::Mat descFrom = Nan::ObjectWrap::Unwrap<Mat>(info[0]->ToObject())->mat;
	cv::Mat descTo = Nan::ObjectWrap::Unwrap<Mat>(info[1]->ToObject())->mat;

	std::vector<cv::DMatch> dmatches;
	FF_TRY(cv::DescriptorMatcher::create(matcherType)->match(descFrom, descTo, dmatches););

	v8::Local<v8::Array> jsMatches = Nan::New<v8::Array>(dmatches.size());
	uint i = 0;
	for (auto dmatch : dmatches) {
		v8::Local<v8::Object> jsMatch = Nan::NewInstance(Nan::New(DescriptorMatch::constructor)->GetFunction()).ToLocalChecked();
		Nan::ObjectWrap::Unwrap<DescriptorMatch>(jsMatch)->setNativeProps(dmatch);
		jsMatches->Set(i++, jsMatch);
	}
	info.GetReturnValue().Set(jsMatches);
}