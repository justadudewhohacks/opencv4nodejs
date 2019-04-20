export class TrackerKCFParams {
	readonly admm_iterations: number;
	readonly background_ratio: number;
	readonly cheb_attenuation: number;
	readonly filter_lr: number;
	readonly gsl_sigma: number;
	readonly histogram_bins: number;
	readonly histogram_lr: number;
	readonly hog_clip: number;
	readonly hog_orientations: number;
	readonly kaiser_alpha: number;
	readonly num_hog_channels_used: number;
	readonly number_of_scales: number;
	readonly padding: number;
	//readonly psr_threshold: number;
	readonly scale_lr: number;
	readonly scale_model_max_area: number;
	readonly scale_sigma_factor: number;
	readonly scale_step: number;
	readonly template_size: number;
	readonly use_channel_weights: bool;
	readonly use_color_names: bool;
	readonly use_gray: bool;
	readonly use_hog: bool;
	readonly use_rgb: bool;
	readonly use_segmentation: bool;
	readonly weights_lr: number;
	readonly window_function: string;

  constructor();
}
