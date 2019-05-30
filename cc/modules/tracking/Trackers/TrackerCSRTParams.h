#include "macros.h"
#include <opencv2/tracking.hpp>

#if CV_MINOR_VERSION > 4 || (CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION > 0)

#ifndef __FF_TRACKERCSRTPARAMS_H__
#define __FF_TRACKERCSRTPARAMS_H__

class TrackerCSRTParams : public Nan::ObjectWrap {
public:
	cv::TrackerCSRT::Params params;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER(TrackerCSRTParams, admm_iterationsGet, params.admm_iterations);
	static FF_SETTER_INT(TrackerCSRTParams, admm_iterations, params.admm_iterations);
	static FF_GETTER(TrackerCSRTParams, background_ratioGet, params.background_ratio);
	static FF_SETTER_INT(TrackerCSRTParams, background_ratio, params.background_ratio);
	static FF_GETTER(TrackerCSRTParams, cheb_attenuationGet, params.cheb_attenuation);
	static FF_SETTER_NUMBER(TrackerCSRTParams, cheb_attenuation, params.cheb_attenuation);
	static FF_GETTER(TrackerCSRTParams, filter_lrGet, params.filter_lr);
	static FF_SETTER_NUMBER(TrackerCSRTParams, filter_lr, params.filter_lr);
	static FF_GETTER(TrackerCSRTParams, gsl_sigmaGet, params.gsl_sigma);
	static FF_SETTER_NUMBER(TrackerCSRTParams, gsl_sigma, params.gsl_sigma);
	static FF_GETTER(TrackerCSRTParams, histogram_binsGet, params.histogram_bins);
	static FF_SETTER_INT(TrackerCSRTParams, histogram_bins, params.histogram_bins);
	static FF_GETTER(TrackerCSRTParams, histogram_lrGet, params.histogram_lr);
	static FF_SETTER_NUMBER(TrackerCSRTParams, histogram_lr, params.histogram_lr);
	static FF_GETTER(TrackerCSRTParams, hog_clipGet, params.hog_clip);
	static FF_SETTER_NUMBER(TrackerCSRTParams, hog_clip, params.hog_clip);
	static FF_GETTER(TrackerCSRTParams, hog_orientationsGet, params.hog_orientations);
	static FF_SETTER_NUMBER(TrackerCSRTParams, hog_orientations, params.hog_orientations);
	static FF_GETTER(TrackerCSRTParams, kaiser_alphaGet, params.kaiser_alpha);
	static FF_SETTER_NUMBER(TrackerCSRTParams, kaiser_alpha, params.kaiser_alpha);
	static FF_GETTER(TrackerCSRTParams, num_hog_channels_usedGet, params.num_hog_channels_used);
	static FF_SETTER_INT(TrackerCSRTParams, num_hog_channels_used, params.num_hog_channels_used);
	static FF_GETTER(TrackerCSRTParams, number_of_scalesGet, params.number_of_scales);
	static FF_SETTER_INT(TrackerCSRTParams, number_of_scales, params.number_of_scales);
	static FF_GETTER(TrackerCSRTParams, paddingGet, params.padding);
	static FF_SETTER_NUMBER(TrackerCSRTParams, padding, params.padding);
	
#if CV_MINOR_VERSION > 4 || (CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION > 3)
	static FF_GETTER(TrackerCSRTParams, psr_thresholdGet, params.psr_threshold);
	static FF_SETTER_NUMBER(TrackerCSRTParams, psr_threshold, params.psr_threshold);
#endif

	static FF_GETTER(TrackerCSRTParams, scale_lrGet, params.scale_lr);
	static FF_SETTER_NUMBER(TrackerCSRTParams, scale_lr, params.scale_lr);
	static FF_GETTER(TrackerCSRTParams, scale_model_max_areaGet, params.scale_model_max_area);
	static FF_SETTER_NUMBER(TrackerCSRTParams, scale_model_max_area, params.scale_model_max_area);
	static FF_GETTER(TrackerCSRTParams, scale_sigma_factorGet, params.scale_sigma_factor);
	static FF_SETTER_NUMBER(TrackerCSRTParams, scale_sigma_factor, params.scale_sigma_factor);
	static FF_GETTER(TrackerCSRTParams, scale_stepGet, params.scale_step);
	static FF_SETTER_NUMBER(TrackerCSRTParams, scale_step, params.scale_step);
	static FF_GETTER(TrackerCSRTParams, template_sizeGet, params.template_size);
	static FF_SETTER_NUMBER(TrackerCSRTParams, template_size, params.template_size);
	static FF_GETTER(TrackerCSRTParams, use_channel_weightsGet, params.use_channel_weights);
	static FF_SETTER_BOOL(TrackerCSRTParams, use_channel_weights, params.use_channel_weights);
	static FF_GETTER(TrackerCSRTParams, use_color_namesGet, params.use_color_names);
	static FF_SETTER_BOOL(TrackerCSRTParams, use_color_names, params.use_color_names);
	static FF_GETTER(TrackerCSRTParams, use_grayGet, params.use_gray);
	static FF_SETTER_BOOL(TrackerCSRTParams, use_gray, params.use_gray);
	static FF_GETTER(TrackerCSRTParams, use_hogGet, params.use_hog);
	static FF_SETTER_BOOL(TrackerCSRTParams, use_hog, params.use_hog);
	static FF_GETTER(TrackerCSRTParams, use_rgbGet, params.use_rgb);
	static FF_SETTER_BOOL(TrackerCSRTParams, use_rgb, params.use_rgb);
	static FF_GETTER(TrackerCSRTParams, use_segmentationGet, params.use_segmentation);
	static FF_SETTER_BOOL(TrackerCSRTParams, use_segmentation, params.use_segmentation);
	static FF_GETTER(TrackerCSRTParams, weights_lrGet, params.weights_lr);
	static FF_SETTER_NUMBER(TrackerCSRTParams, weights_lr, params.weights_lr);	
	static FF_GETTER_SIMPLE(TrackerCSRTParams, window_functionGet, params.window_function, FF::StringConverter);
	static FF_SETTER_STRING(TrackerCSRTParams, window_function, params.window_function);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::TrackerCSRT::Params* getNativeObjectPtr() { return &params; }
	cv::TrackerCSRT::Params getNativeObject() { return params; }

	typedef InstanceConverter<TrackerCSRTParams, cv::TrackerCSRT::Params> Converter;

	static const char* getClassName() {
		return "TrackerCSRTParams";
	}
};

#define FF_UNWRAP_TRACKERCSRTPARAMS(obj) FF_UNWRAP(obj, TrackerCSRTParams)
#define FF_UNWRAP_TRACKERCSRTPARAMS_AND_GET(obj) FF_UNWRAP_TRACKERCSRTPARAMS(obj)->params

#endif

#endif