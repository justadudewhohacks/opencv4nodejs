#include "macros.h"
#include <opencv2/tracking.hpp>

#if CV_MINOR_VERSION > 0

#ifndef __FF_TRACKERKCFPARAMS_H__
#define __FF_TRACKERKCFPARAMS_H__

class TrackerKCFParams : public FF::ObjectWrap<TrackerKCFParams, cv::TrackerKCF::Params> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "TrackerKCFParams";
	}

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER(TrackerKCFParams, sigmaGet, self.sigma);
	static FF_SETTER_NUMBER(TrackerKCFParams, sigma, self.sigma);
	static FF_GETTER(TrackerKCFParams, lambdaGet, self.lambda);
	static FF_SETTER_NUMBER(TrackerKCFParams, lambda, self.lambda);
	static FF_GETTER(TrackerKCFParams, interp_factorGet, self.interp_factor);
	static FF_SETTER_NUMBER(TrackerKCFParams, interp_factor, self.interp_factor);
	static FF_GETTER(TrackerKCFParams, output_sigma_factorGet, self.output_sigma_factor);
	static FF_SETTER_NUMBER(TrackerKCFParams, output_sigma_factor, self.output_sigma_factor);
	static FF_GETTER(TrackerKCFParams, pca_learning_rateGet, self.pca_learning_rate);
	static FF_SETTER_NUMBER(TrackerKCFParams, pca_learning_rate, self.pca_learning_rate);

	static FF_GETTER(TrackerKCFParams, resizeGet, self.resize);
	static FF_SETTER_BOOL(TrackerKCFParams, resize, self.resize);
	static FF_GETTER(TrackerKCFParams, split_coeffGet, self.split_coeff);
	static FF_SETTER_BOOL(TrackerKCFParams, split_coeff, self.split_coeff);
	static FF_GETTER(TrackerKCFParams, wrap_kernelGet, self.wrap_kernel);
	static FF_SETTER_BOOL(TrackerKCFParams, wrap_kernel, self.wrap_kernel);
	static FF_GETTER(TrackerKCFParams, compress_featureGet, self.compress_feature);
	static FF_SETTER_BOOL(TrackerKCFParams, compress_feature, self.compress_feature);
	static FF_GETTER(TrackerKCFParams, max_patch_sizeGet, self.max_patch_size);
	static FF_SETTER_INT(TrackerKCFParams, max_patch_size, self.max_patch_size);
	static FF_GETTER(TrackerKCFParams, compressed_sizeGet, self.compressed_size);
	static FF_SETTER_INT(TrackerKCFParams, compressed_size, self.compressed_size);
	static FF_GETTER(TrackerKCFParams, desc_pcaGet, self.desc_pca);
	static FF_SETTER_UINT(TrackerKCFParams, desc_pca, self.desc_pca);
	static FF_GETTER(TrackerKCFParams, desc_npcaGet, self.desc_npca);
	static FF_SETTER_UINT(TrackerKCFParams, desc_npca, self.desc_npca);
	
#if CV_MINOR_VERSION > 2
	static FF_GETTER(TrackerKCFParams, detect_threshGet, self.detect_thresh);
	static FF_SETTER_NUMBER(TrackerKCFParams, detect_thresh, self.detect_thresh);
#endif
};

#endif

#endif