import { features2d } from 'dut';
import { detectorTests } from './detectorTests';

describe('features2d', () => {
  describe('AGASTDetector', () => {
    const defaults = {
      type: 3,
      nonmaxSuppression: true,
      threshold: 10
    };
    const customProps = {
      type: 1,
      nonmaxSuppression: false,
      threshold: 50
    };
    const Detector = features2d.AGASTDetector;
    detectorTests(defaults, customProps, Detector, false);
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
      diffusivity: 2,
      nOctaveLayers: 8,
      nOctaves: 8,
      threshold: 2 * 0.0010000000474974513,
      descriptorChannels: 6,
      descriptorSize: 1,
      descriptorType: 1
    };
    const Detector = features2d.AKAZEDetector;
    detectorTests(defaults, customProps, Detector);
  });

  describe('BRISKDetector', () => {
    const defaults = {
      patternScale: 1.0,
      octaves: 3,
      thresh: 30
    };
    const customProps = {
      patternScale: 2.4,
      octaves: 6,
      thresh: 60
    };
    const Detector = features2d.BRISKDetector;
    detectorTests(defaults, customProps, Detector);
  });

  describe('FASTDetector', () => {
    const defaults = {
      type: 2,
      nonmaxSuppression: true,
      threshold: 10
    };
    const customProps = {
      type: 1,
      nonmaxSuppression: false,
      threshold: 20
    };
    const Detector = features2d.FASTDetector;
    detectorTests(defaults, customProps, Detector, false);
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
      k: 0.16,
      useHarrisDetector: true,
      blockSize: 6,
      minDistance: 2,
      qualityLevel: 0.04,
      maxCorners: 2000
    };
    const Detector = features2d.GFTTDetector;
    detectorTests(defaults, customProps, Detector, false);
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
      diffusivity: 2,
      nOctaveLayers: 8,
      nOctaves: 8,
      threshold: 2 * 0.0010000000474974513,
      upright: true,
      extended: true
    };
    const Detector = features2d.KAZEDetector;
    detectorTests(defaults, customProps, Detector);
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
      edgeBlurSize: 10,
      minMargin: 0.006,
      areaThreshold: 2.02,
      maxEvolution: 400,
      minDiversity: 0.4,
      maxVariation: 0.75,
      maxArea: 28800,
      minArea: 120,
      delta: 10
    };
    const Detector = features2d.MSERDetector;
    detectorTests(defaults, customProps, Detector, false);
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
      fastThreshold: 40,
      patchSize: 62,
      scoreType: 1,
      WTA_K: 3,
      firstLevel: 2,
      edgeThreshold: 62,
      nlevels: 16,
      scaleFactor: 2 * 1.2000000476837158,
      nfeatures: 1000
    };
    const Detector = features2d.ORBDetector;
    detectorTests(defaults, customProps, Detector);
  });

});