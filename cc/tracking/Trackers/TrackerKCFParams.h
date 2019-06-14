#include "macros.h"
#include <opencv2/tracking.hpp>

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

#ifndef __FF_TRACKERKCFPARAMS_H__
#define __FF_TRACKERKCFPARAMS_H__

class TrackerKCFParams : public FF::ObjectWrap<TrackerKCFParams, cv::TrackerKCF::Params> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "TrackerKCFParams";
	}

	FF_ACCESSORS(sigma, FF::FloatConverter);
	FF_ACCESSORS(lambda, FF::FloatConverter);
	FF_ACCESSORS(interp_factor, FF::FloatConverter);
	FF_ACCESSORS(output_sigma_factor, FF::FloatConverter);
	FF_ACCESSORS(pca_learning_rate, FF::FloatConverter);
	FF_ACCESSORS(resize, FF::BoolConverter);
	FF_ACCESSORS(split_coeff, FF::BoolConverter);
	FF_ACCESSORS(wrap_kernel, FF::BoolConverter);
	FF_ACCESSORS(compress_feature, FF::BoolConverter);
	FF_ACCESSORS(max_patch_size, FF::IntConverter);
	FF_ACCESSORS(compressed_size, FF::IntConverter);
	FF_ACCESSORS(desc_pca, FF::UintConverter);
	FF_ACCESSORS(desc_npca, FF::UintConverter);

#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
	FF_ACCESSORS(detect_thresh, FF::FloatConverter);
#endif

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);
};

#endif

#endif