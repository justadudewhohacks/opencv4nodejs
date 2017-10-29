const cv = global.dut;
const {
  assertPropsWithValue
} = global.utils;

module.exports = () => {
  describe('TrackerParams', () => {
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

    (cv.version.minor > 0 ? it : it.skip)('TrackerKCFParams', () => {
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
        desc_pca: cv.trackerKCFModes.GRAY,
        desc_npca: cv.trackerKCFModes.CN

      };

      const trackerParams = new cv.TrackerKCFParams();
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
  });
};
