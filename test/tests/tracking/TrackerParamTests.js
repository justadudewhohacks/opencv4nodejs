module.exports = ({ cv, utils }) => {

  const {
    assertPropsWithValue,
    cvVersionGreaterEqual
  } = utils;

  it('TrackerBoostingParams', () => {
    const params = {
      numClassifiers: 100,
      samplerOverlap: 1.5,
      samplerSearchFactor: 0.5,
      iterationInit: 10,
      featureSetNumFeatures: 5
    };

    const trackerParams = new cv.TrackerBoostingParams();
    Object.keys(params).forEach((param) => { trackerParams[param] = params[param]; });
    assertPropsWithValue(trackerParams)(params);
  });

  (cvVersionGreaterEqual(3, 1, 0) ? it : it.skip)('TrackerKCFParams', () => {
    const params = {
      sigma: 0.9,
      lambda: 0.8,
      interp_factor: 0.7,
      output_sigma_factor: 0.6,
      pca_learning_rate: 0.5,
      resize: true,
      split_coeff: false,
      wrap_kernel: true,
      compress_feature: false,
      max_patch_size: 64,
      compressed_size: 32,
      detect_thresh: 0.5,
      desc_pca: cv.trackerKCFModes.GRAY,
      desc_npca: cv.trackerKCFModes.CN
    };

    const trackerParams = new cv.TrackerKCFParams();
    Object.keys(params).forEach(param => { trackerParams[param] = params[param]; });

    const floatSafe = true;
    assertPropsWithValue(trackerParams)(params, floatSafe);
  });

  (cvVersionGreaterEqual(3, 4, 1) ? it : it.skip)('TrackerCSRTParams', () => {
    const params = {
      admm_iterations: 22,
      background_ratio: 3,
      cheb_attenuation: 43,
      filter_lr: 0.03,
      gsl_sigma: 1.2,
      histogram_bins: 20,
      histogram_lr: 0.4,
      hog_clip: 0.3,
      hog_orientations: 11,
      kaiser_alpha: 3.2,
      num_hog_channels_used: 22,
      number_of_scales: 30,
      padding: 4.2,
      scale_lr: 0.2,
      scale_model_max_area: 256.2,
      scale_sigma_factor: 0.3,
      scale_step: 1.03,
      template_size: 300,
      use_channel_weights: false,
      use_color_names: false,
      use_gray: false,
      use_hog: false,
      use_rgb: true,
      use_segmentation: false,
      weights_lr: 0.03,
      window_function: "kaiser"
    };
    if(cvVersionGreaterEqual(3, 4, 4)){
      params.psr_threshold = 0.4;
    }

    const trackerParams = new cv.TrackerCSRTParams();
    Object.keys(params).forEach((param) => { trackerParams[param] = params[param]; });

    const floatSafe = true;
    assertPropsWithValue(trackerParams)(params, floatSafe);
  });
  it('TrackerMILParams', () => {
    const params = {
      samplerInitInRadius: 2.5,
      samplerSearchWinSize: 1.5,
      samplerTrackInRadius: 0.5,
      samplerInitMaxNegNum: 64,
      samplerTrackMaxPosNum: 32,
      samplerTrackMaxNegNum: 16,
      featureSetNumFeatures: 8
    };

    const trackerParams = new cv.TrackerMILParams();
    Object.keys(params).forEach((param) => { trackerParams[param] = params[param]; });
    assertPropsWithValue(trackerParams)(params);
  });

};
