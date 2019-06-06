#include "macros.h"
#include <opencv2/tracking.hpp>

#if CV_VERSION_GREATER_EQUAL(3, 4, 1)

#ifndef __FF_TRACKERCSRTPARAMS_H__
#define __FF_TRACKERCSRTPARAMS_H__

class TrackerCSRTParams : public FF::ObjectWrap<TrackerCSRTParams, cv::TrackerCSRT::Params> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "TrackerBoostingParams";
	}

	FF_ACCESSORS(admm_iterations, FF::IntConverter);
	FF_ACCESSORS(background_ratio, FF::IntConverter);
	FF_ACCESSORS(histogram_bins, FF::IntConverter);
	FF_ACCESSORS(histogram_lr, FF::FloatConverter);
	FF_ACCESSORS(number_of_scales, FF::IntConverter);
	FF_ACCESSORS(scale_sigma_factor, FF::FloatConverter);
	FF_ACCESSORS(scale_model_max_area, FF::FloatConverter);
	FF_ACCESSORS(scale_lr, FF::FloatConverter);
	FF_ACCESSORS(cheb_attenuation, FF::FloatConverter);
	FF_ACCESSORS(kaiser_alpha, FF::FloatConverter);
	FF_ACCESSORS(filter_lr, FF::FloatConverter);
	FF_ACCESSORS(gsl_sigma, FF::FloatConverter);
	FF_ACCESSORS(hog_clip, FF::FloatConverter);
	FF_ACCESSORS(hog_orientations, FF::FloatConverter);
	FF_ACCESSORS(padding, FF::FloatConverter);
	FF_ACCESSORS(num_hog_channels_used, FF::IntConverter);
	FF_ACCESSORS(scale_step, FF::FloatConverter);
	FF_ACCESSORS(template_size, FF::FloatConverter);
	FF_ACCESSORS(use_channel_weights, FF::BoolConverter);
	FF_ACCESSORS(use_color_names, FF::BoolConverter);
	FF_ACCESSORS(use_gray, FF::BoolConverter);
	FF_ACCESSORS(use_hog, FF::BoolConverter);
	FF_ACCESSORS(use_rgb, FF::BoolConverter);
	FF_ACCESSORS(use_segmentation, FF::BoolConverter);
	FF_ACCESSORS(weights_lr, FF::FloatConverter);
	FF_ACCESSORS(window_function, FF::StringConverter);
	
#if CV_VERSION_GREATER_EQUAL(3, 4, 4)
	FF_ACCESSORS(psr_threshold, FF::FloatConverter);
#endif

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);
};

#endif

#endif