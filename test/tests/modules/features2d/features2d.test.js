const cv = global.dut;
const { assertMetaData, isZeroMat, readTestImage } = global.utils;
const { assert, expect } = require('chai');
const detectorTests = require('./detectorTests');
const KeyPointTests = require('./KeyPointTests');
const DescriptorMatchTests = require('./DescriptorMatchTests');
const descriptorMatchingTests = require('./descriptorMatchingTests');

describe('features2d', () => {
  let testImg;
  before(() => {
    testImg = readTestImage().resizeToMax(250);
  });

  KeyPointTests();
  DescriptorMatchTests();
  descriptorMatchingTests(() => testImg);

  describe('AGASTDetector', () => {
    const defaults = {
      type: 3,
      nonmaxSuppression: true,
      threshold: 10
    };
    const customProps = {
      args: ['threshold', 'nonmaxSuppression', 'type'],
      values: [1, false, 50]
    };
    const Detector = cv.AGASTDetector;
    detectorTests(() => testImg, defaults, customProps, Detector, false);
  });

  describe('AKAZEDetector', () => {
    const defaults = {
      diffusivity: 1,
      nOctaveLayers: 4,
      nOctaves: 4,
      threshold: 0.0010000000474974513,
      descriptorChannels: 3,
      descriptorSize: 0,
      descriptorType: 5
    };
    const customProps = {
      args: ['descriptorType', 'descriptorSize', 'descriptorChannels', 'threshold', 'nOctaves', 'nOctaveLayers', 'diffusivity'],
      values: [2, 8, 8, 2 * 0.0010000000474974513, 6, 1, 1]
    };
    const Detector = cv.AKAZEDetector;
    detectorTests(() => testImg, defaults, customProps, Detector);
  });

  describe('BRISKDetector', () => {
    const defaults = {
      patternScale: 1.0,
      octaves: 3,
      thresh: 30
    };
    const customProps = {
      args: ['thresh', 'octaves', 'patternScale'],
      values: [50, 6, 2.4]
    };
    const Detector = cv.BRISKDetector;
    detectorTests(() => testImg, defaults, customProps, Detector);
  });

  describe('FASTDetector', () => {
    const defaults = {
      type: 2,
      nonmaxSuppression: true,
      threshold: 10
    };
    const customProps = {
      args: ['threshold', 'nonmaxSuppression', 'type'],
      values: [1, false, 20]
    };
    const Detector = cv.FASTDetector;
    detectorTests(() => testImg, defaults, customProps, Detector, false);
  });

  describe('GFTTDetector', () => {
    const defaults = {
      k: 0.04,
      useHarrisDetector: false,
      blockSize: 3,
      minDistance: 1,
      qualityLevel: 0.01,
      maxCorners: 1000
    };
    const customProps = {
      args: ['maxCorners', 'qualityLevel', 'minDistance', 'blockSize', 'useHarrisDetector', 'k'],
      values: [2000, 0.04, 2, 6, true, 0.16]
    };
    const Detector = cv.GFTTDetector;
    detectorTests(() => testImg, defaults, customProps, Detector, false);
  });

  describe('KAZEDetector', () => {
    const defaults = {
      diffusivity: 1,
      nOctaveLayers: 4,
      nOctaves: 4,
      threshold: 0.0010000000474974513,
      upright: false,
      extended: false
    };
    const customProps = {
      args: ['extended', 'upright', 'threshold', 'nOctaves', 'nOctaveLayers', 'diffusivity'],
      values: [true, true, 0.0020000000949949026, 8, 8, 2]
    };
    const Detector = cv.KAZEDetector;
    detectorTests(() => testImg, defaults, customProps, Detector);
  });

  describe('MSERDetector', () => {
    const defaults = {
      edgeBlurSize: 5,
      minMargin: 0.003,
      areaThreshold: 1.01,
      maxEvolution: 200,
      minDiversity: 0.2,
      maxVariation: 0.25,
      maxArea: 14400,
      minArea: 60,
      delta: 5
    };
    const customProps = {
      args: ['delta', 'minArea', 'maxArea', 'maxVariation', 'minDiversity', 'maxEvolution', 'areaThreshold', 'minMargin', 'edgeBlurSize'],
      values: [10, 120, 28800, 0.75, 0.4, 400, 2.02, 0.006, 10]
    };
    const Detector = cv.MSERDetector;
    detectorTests(() => testImg, defaults, customProps, Detector, false);
  });

  describe('ORBDetector', () => {
    const defaults = {
      fastThreshold: 20,
      patchSize: 31,
      scoreType: 0,
      WTA_K: 2,
      firstLevel: 0,
      edgeThreshold: 31,
      nlevels: 8,
      scaleFactor: 1.2000000476837158,
      nfeatures: 500
    };
    const customProps = {
      args: ['nfeatures', 'scaleFactor', 'nlevels', 'edgeThreshold', 'firstLevel', 'WTA_K', 'scoreType', 'patchSize', 'fastThreshold'],
      values: [1000, 2 * 1.2000000476837158, 16, 62, 2, 3, 1, 62, 40]
    };
    const Detector = cv.ORBDetector;
    detectorTests(() => testImg, defaults, customProps, Detector);
  });

  describe('SimpleBlobDetector', () => {
    const Detector = new cv.SimpleBlobDetector(new cv.SimpleBlobDetectorParams());
    detectorTests(() => testImg, null, null, Detector, false);
  });

  describe('drawing', () => {
    let kps;

    before(() => {
      kps = new cv.ORBDetector().detect(testImg);
    });

    it('drawKeyPoints', () => {
      const img = new cv.Mat(testImg.rows, testImg.cols, cv.CV_8UC3, [0, 0, 0]);
      const dst = cv.drawKeyPoints(img, kps);
      expect(dst).instanceOf(cv.Mat);
      assertMetaData(dst)(testImg);
      assert(isZeroMat(dst) === false, 'dst Mat contains zeros only');
    });

    it('drawMatches', () => {
      const desc = new cv.ORBDetector().compute(testImg, kps);
      const matches = cv.matchBruteForce(desc, desc);
      const img = new cv.Mat(testImg.rows, testImg.cols, cv.CV_8UC3, [0, 0, 0]);
      const dst = cv.drawMatches(img, img, kps, kps, matches);
      expect(dst).instanceOf(cv.Mat);
      assertMetaData(dst)(img.rows, img.cols * 2, img.type);
      assert(isZeroMat(dst) === false, 'dst Mat contains zeros only');
    });
  });
});
