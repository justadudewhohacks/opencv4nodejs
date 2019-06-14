#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerCSRTParams.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 1)

Nan::Persistent<v8::FunctionTemplate> TrackerCSRTParams::constructor;

NAN_MODULE_INIT(TrackerCSRTParams::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerCSRTParams::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerCSRTParams"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF::newString("admm_iterations"), admm_iterations_getter, admm_iterations_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("background_ratio"), background_ratio_getter, background_ratio_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("cheb_attenuation"), cheb_attenuation_getter, cheb_attenuation_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("filter_lr"), filter_lr_getter, filter_lr_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("gsl_sigma"), gsl_sigma_getter, gsl_sigma_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("histogram_bins"), histogram_bins_getter, histogram_bins_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("histogram_lr"), histogram_lr_getter, histogram_lr_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("hog_clip"), hog_clip_getter, hog_clip_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("hog_orientations"), hog_orientations_getter, hog_orientations_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("kaiser_alpha"), kaiser_alpha_getter, kaiser_alpha_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("num_hog_channels_used"), num_hog_channels_used_getter, num_hog_channels_used_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("number_of_scales"), number_of_scales_getter, number_of_scales_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("padding"), padding_getter, padding_setter);
#if CV_VERSION_GREATER_EQUAL(3, 4, 4)
	Nan::SetAccessor(instanceTemplate, FF::newString("psr_threshold"), psr_threshold_getter, psr_threshold_setter);
#endif
	Nan::SetAccessor(instanceTemplate, FF::newString("scale_lr"), scale_lr_getter, scale_lr_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("scale_model_max_area"), scale_model_max_area_getter, scale_model_max_area_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("scale_sigma_factor"), scale_sigma_factor_getter, scale_sigma_factor_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("scale_step"), scale_step_getter, scale_step_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("template_size"), template_size_getter, template_size_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("use_channel_weights"), use_channel_weights_getter, use_channel_weights_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("use_color_names"), use_color_names_getter, use_color_names_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("use_gray"), use_gray_getter, use_gray_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("use_hog"), use_hog_getter, use_hog_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("use_rgb"), use_rgb_getter, use_rgb_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("use_segmentation"), use_segmentation_getter, use_segmentation_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("weights_lr"), weights_lr_getter, weights_lr_setter);
	Nan::SetAccessor(instanceTemplate, FF::newString("window_function"), window_function_getter, window_function_setter);

	Nan::Set(target, FF::newString("TrackerCSRTParams"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerCSRTParams::New) {
	FF::TryCatch tryCatch("TrackerCSRTParams::New");
	FF_ASSERT_CONSTRUCT_CALL();
	TrackerCSRTParams* self = new TrackerCSRTParams();
	self->self = cv::TrackerCSRT::Params();
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
