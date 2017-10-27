#include "macros.h"
#include <opencv2/tracking.hpp>

#if CV_MINOR_VERSION > 0

#ifndef __FF_TRACKERKCFPARAMS_H__
#define __FF_TRACKERKCFPARAMS_H__

class TrackerKCFParams : public Nan::ObjectWrap {
public:
	cv::TrackerKCF::Params params;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER(TrackerKCFParams, sigmaGet, params.sigma);
	static FF_SETTER_NUMBER(TrackerKCFParams, sigma, params.sigma);
	static FF_GETTER(TrackerKCFParams, lambdaGet, params.lambda);
	static FF_SETTER_NUMBER(TrackerKCFParams, lambda, params.lambda);
	static FF_GETTER(TrackerKCFParams, interp_factorGet, params.interp_factor);
	static FF_SETTER_NUMBER(TrackerKCFParams, interp_factor, params.interp_factor);
	static FF_GETTER(TrackerKCFParams, output_sigma_factorGet, params.output_sigma_factor);
	static FF_SETTER_NUMBER(TrackerKCFParams, output_sigma_factor, params.output_sigma_factor);
	static FF_GETTER(TrackerKCFParams, pca_learning_rateGet, params.pca_learning_rate);
	static FF_SETTER_NUMBER(TrackerKCFParams, pca_learning_rate, params.pca_learning_rate);
	static FF_GETTER(TrackerKCFParams, resizeGet, params.resize);
	static FF_SETTER_BOOL(TrackerKCFParams, resize, params.resize);
	static FF_GETTER(TrackerKCFParams, split_coeffGet, params.split_coeff);
	static FF_SETTER_BOOL(TrackerKCFParams, split_coeff, params.split_coeff);
	static FF_GETTER(TrackerKCFParams, wrap_kernelGet, params.wrap_kernel);
	static FF_SETTER_BOOL(TrackerKCFParams, wrap_kernel, params.wrap_kernel);
	static FF_GETTER(TrackerKCFParams, compress_featureGet, params.compress_feature);
	static FF_SETTER_BOOL(TrackerKCFParams, compress_feature, params.compress_feature);
	static FF_GETTER(TrackerKCFParams, max_patch_sizeGet, params.max_patch_size);
	static FF_SETTER_INT(TrackerKCFParams, max_patch_size, params.max_patch_size);
	static FF_GETTER(TrackerKCFParams, compressed_sizeGet, params.compressed_size);
	static FF_SETTER_INT(TrackerKCFParams, compressed_size, params.compressed_size);
	static FF_GETTER(TrackerKCFParams, desc_pcaGet, params.desc_pca);
	static FF_SETTER_UINT(TrackerKCFParams, desc_pca, params.desc_pca);
	static FF_GETTER(TrackerKCFParams, desc_npcaGet, params.desc_npca);
	static FF_SETTER_UINT(TrackerKCFParams, desc_npca, params.desc_npca);

	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#define FF_UNWRAP_TRACKERKCFPARAMS(obj) FF_UNWRAP(obj, TrackerKCFParams)
#define FF_UNWRAP_TRACKERKCFPARAMS_AND_GET(obj) FF_UNWRAP_TRACKERKCFPARAMS(obj)->params

#endif

#endif