const detectorTestsFactory = require('../features2d/detectorTests');

module.exports = function ({ cv, utils, getTestImg }) {
  const detectorTests = detectorTestsFactory({ cv, utils, getTestImg: () => getTestImg().resizeToMax(250) })
  describe('SIFTDetector', () => {
    const defaults = {
      sigma: 1.6,
      edgeThreshold: 10,
      contrastThreshold: 0.04,
      nOctaveLayers: 3,
      nFeatures: 0
    };
    const customProps = {
      args: ['nFeatures', 'nOctaveLayers', 'contrastThreshold', 'edgeThreshold', 'sigma'],
      values: [500, 6, 0.16, 20, 3.2]
    };
    const Detector = cv.SIFTDetector;
    detectorTests(defaults, customProps, Detector);
  });

  describe('SURFDetector', () => {
    const defaults = {
      upright: false,
      extended: false,
      nOctaveLayers: 3,
      nOctaves: 4,
      hessianThreshold: 100
    };
    const customProps = {
      args: ['hessianThreshold', 'nOctaves', 'nOctaveLayers', 'extended', 'upright'],
      values: [1000, 8, 6, true, true]
    };
    const Detector = cv.SURFDetector;
    detectorTests(defaults, customProps, Detector);
  });

};
