#include "macros.h"
#include <opencv2/tracking.hpp>

#if CV_MINOR_VERSION > 4 || (CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION > 0)

#ifndef __FF_TRACKERCSRTPARAMS_H__
#define __FF_TRACKERCSRTPARAMS_H__

class TrackerCSRTParams : public FF::ObjectWrap<TrackerCSRTParams, cv::TrackerCSRT::Params> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "TrackerBoostingParams";
	}

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

	static FF_GETTER(TrackerCSRTParams, admm_iterationsGet, self.admm_iterations);
	static FF_SETTER_INT(TrackerCSRTParams, admm_iterations, self.admm_iterations);
	static FF_GETTER(TrackerCSRTParams, background_ratioGet, self.background_ratio);
	static FF_SETTER_INT(TrackerCSRTParams, background_ratio, self.background_ratio);
	static FF_GETTER(TrackerCSRTParams, cheb_attenuationGet, self.cheb_attenuation);
	static FF_SETTER_NUMBER(TrackerCSRTParams, cheb_attenuation, self.cheb_attenuation);
	static FF_GETTER(TrackerCSRTParams, filter_lrGet, self.filter_lr);
	static FF_SETTER_NUMBER(TrackerCSRTParams, filter_lr, self.filter_lr);
	static FF_GETTER(TrackerCSRTParams, gsl_sigmaGet, self.gsl_sigma);
	static FF_SETTER_NUMBER(TrackerCSRTParams, gsl_sigma, self.gsl_sigma);
	static FF_GETTER(TrackerCSRTParams, histogram_binsGet, self.histogram_bins);
	static FF_SETTER_INT(TrackerCSRTParams, histogram_bins, self.histogram_bins);
	static FF_GETTER(TrackerCSRTParams, histogram_lrGet, self.histogram_lr);
	static FF_SETTER_NUMBER(TrackerCSRTParams, histogram_lr, self.histogram_lr);
	static FF_GETTER(TrackerCSRTParams, hog_clipGet, self.hog_clip);
	static FF_SETTER_NUMBER(TrackerCSRTParams, hog_clip, self.hog_clip);
	static FF_GETTER(TrackerCSRTParams, hog_orientationsGet, self.hog_orientations);
	static FF_SETTER_NUMBER(TrackerCSRTParams, hog_orientations, self.hog_orientations);
	static FF_GETTER(TrackerCSRTParams, kaiser_alphaGet, self.kaiser_alpha);
	static FF_SETTER_NUMBER(TrackerCSRTParams, kaiser_alpha, self.kaiser_alpha);
	static FF_GETTER(TrackerCSRTParams, num_hog_channels_usedGet, self.num_hog_channels_used);
	static FF_SETTER_INT(TrackerCSRTParams, num_hog_channels_used, self.num_hog_channels_used);
	static FF_GETTER(TrackerCSRTParams, number_of_scalesGet, self.number_of_scales);
	static FF_SETTER_INT(TrackerCSRTParams, number_of_scales, self.number_of_scales);
	static FF_GETTER(TrackerCSRTParams, paddingGet, self.padding);
	static FF_SETTER_NUMBER(TrackerCSRTParams, padding, self.padding);
	
#if CV_MINOR_VERSION > 4 || (CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION > 3)
	static FF_GETTER(TrackerCSRTParams, psr_thresholdGet, self.psr_threshold);
	static FF_SETTER_NUMBER(TrackerCSRTParams, psr_threshold, self.psr_threshold);
#endif

	static FF_GETTER(TrackerCSRTParams, scale_lrGet, self.scale_lr);
	static FF_SETTER_NUMBER(TrackerCSRTParams, scale_lr, self.scale_lr);
	static FF_GETTER(TrackerCSRTParams, scale_model_max_areaGet, self.scale_model_max_area);
	static FF_SETTER_NUMBER(TrackerCSRTParams, scale_model_max_area, self.scale_model_max_area);
	static FF_GETTER(TrackerCSRTParams, scale_sigma_factorGet, self.scale_sigma_factor);
	static FF_SETTER_NUMBER(TrackerCSRTParams, scale_sigma_factor, self.scale_sigma_factor);
	static FF_GETTER(TrackerCSRTParams, scale_stepGet, self.scale_step);
	static FF_SETTER_NUMBER(TrackerCSRTParams, scale_step, self.scale_step);
	static FF_GETTER(TrackerCSRTParams, template_sizeGet, self.template_size);
	static FF_SETTER_NUMBER(TrackerCSRTParams, template_size, self.template_size);
	static FF_GETTER(TrackerCSRTParams, use_channel_weightsGet, self.use_channel_weights);
	static FF_SETTER_BOOL(TrackerCSRTParams, use_channel_weights, self.use_channel_weights);
	static FF_GETTER(TrackerCSRTParams, use_color_namesGet, self.use_color_names);
	static FF_SETTER_BOOL(TrackerCSRTParams, use_color_names, self.use_color_names);
	static FF_GETTER(TrackerCSRTParams, use_grayGet, self.use_gray);
	static FF_SETTER_BOOL(TrackerCSRTParams, use_gray, self.use_gray);
	static FF_GETTER(TrackerCSRTParams, use_hogGet, self.use_hog);
	static FF_SETTER_BOOL(TrackerCSRTParams, use_hog, self.use_hog);
	static FF_GETTER(TrackerCSRTParams, use_rgbGet, self.use_rgb);
	static FF_SETTER_BOOL(TrackerCSRTParams, use_rgb, self.use_rgb);
	static FF_GETTER(TrackerCSRTParams, use_segmentationGet, self.use_segmentation);
	static FF_SETTER_BOOL(TrackerCSRTParams, use_segmentation, self.use_segmentation);
	static FF_GETTER(TrackerCSRTParams, weights_lrGet, self.weights_lr);
	static FF_SETTER_NUMBER(TrackerCSRTParams, weights_lr, self.weights_lr);	
	static FF_GETTER_SIMPLE(TrackerCSRTParams, window_functionGet, self.window_function, FF::StringConverter);
	static FF_SETTER_STRING(TrackerCSRTParams, window_function, self.window_function);
};

#endif

#endif