const opencv = global.dut;
const { readTestImage } = global.utils;
const detectorTests = require('./detectorTests');

describe('xfeatures2d', () => {
  if (!opencv.xmodules.xfeatures2d) {
    it('compiled without xfeatures2d');
    return;
  }

  let testImg;
  before(() => {
    testImg = readTestImage().resizeToMax(250);
  });

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
    const Detector = opencv.SIFTDetector;
    detectorTests(() => testImg, defaults, customProps, Detector);
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
    const Detector = opencv.SURFDetector;
    detectorTests(() => testImg, defaults, customProps, Detector);
  });
});
