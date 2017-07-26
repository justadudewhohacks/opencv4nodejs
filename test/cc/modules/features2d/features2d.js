const { features2d } = require('../../../../');
const { expect } = require('chai');

const expectToHaveProps = detector => (props) => {
  Object.keys(props).forEach(key =>
    expect(detector).to.have.property(key).equal(props[key])
  );
};

const detectorTests = (defaults, customProps, Detector) => {
  it('should use default values for empty args', () => {
    expectToHaveProps(new Detector())(defaults);
  });

  it('should use default values for empty object', () => {
    expectToHaveProps(new Detector({}))(defaults);
  });

  it('should be constructable with custom props', () => {
    expectToHaveProps(new Detector(customProps))(customProps);
  });

  it('should have function detect', () => {
    expect(new Detector()).to.have.property('detect').to.be.a('function');
  });

  it('should have function compute', () => {
    expect(new Detector()).to.have.property('compute').to.be.a('function');
  });
};


describe('features2d', () => {
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
    detectorTests(defaults, customProps, Detector);
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