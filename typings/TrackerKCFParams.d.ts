export class TrackerKCFParams {
  readonly sigma: number;
  readonly lambda: number;
  readonly interp_factor: number;
  readonly output_sigma_factor: number;
  readonly pca_learning_rate: number;
  readonly resize: boolean;
  readonly split_coeff: boolean;
  readonly wrap_kernel: boolean;
  readonly compress_feature: boolean;
  readonly max_patch_size: number;
  readonly compressed_size: number;
  readonly desc_pca: number;
  readonly desc_npca: number;
  readonly detect_thresh: number;
  constructor();
}
