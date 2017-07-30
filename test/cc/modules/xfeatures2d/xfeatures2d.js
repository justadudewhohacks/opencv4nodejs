import { xfeatures2d } from 'dut';
import { detectorTests } from '../features2d/detectorTests';

describe('xfeatures2d', () => {
  describe('SIFTDetector', () => {
    const defaults = {
      sigma: 1.6,
      edgeThreshold: 10,
      contrastThreshold: 0.04,
      nOctaveLayers: 3,
      nFeatures: 0
    };
    const customProps = {
      sigma: 3.2,
      edgeThreshold: 20,
      contrastThreshold: 0.16,
      nOctaveLayers: 6,
      nFeatures: 500
    };
    const Detector = xfeatures2d.SIFTDetector;
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
      upright: true,
      extended: true,
      nOctaveLayers: 6,
      nOctaves: 8,
      hessianThreshold: 1000
    };
    const Detector = xfeatures2d.SURFDetector;
    detectorTests(defaults, customProps, Detector);
  });

});