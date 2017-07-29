import { features2d } from 'dut';
import { assert, expect } from 'chai';
import { assertError, assertPropsWithValue, readTestImage } from 'utils';

// TODO test return values of compute, detect

exports.detectorTests = (defaults, customProps, Detector, implementsCompute = true) => {
  let testImg;
  let keyPoints;

  before(async () => {
    testImg = (await readTestImage()).resizeToMax(250);
    keyPoints = (new Detector()).detect(testImg);
  });

  it('should use default values for no args', () => {
    assertPropsWithValue(new Detector())(defaults);
  });

  it('should use default values for empty args', () => {
    assertPropsWithValue(new Detector({}))(defaults);
  });

  it('should be constructable with custom props', () => {
    assertPropsWithValue(new Detector(customProps))(customProps);
  });

  it('should have function detect', () => {
    expect(new Detector()).to.have.property('detect').to.be.a('function');
  });

  it('should have function compute', () => {
    expect(new Detector()).to.have.property('compute').to.be.a('function');
  });

  describe('detect', () => {
    it('should throw if no args', () => {
      assertError(() => (new Detector()).detect())('required argument image');
    });

    it('should return an array of KeyPoints', () => {
      expect(keyPoints).to.be.a('array');
      assert(keyPoints.length > 0, 'no KeyPoints detected');
      keyPoints.forEach(kp => assert(kp instanceof features2d.KeyPoint));
    });
  });

  if (implementsCompute) {
    describe('compute', () => {
      it('should throw if no args', () => {
        assertError(() => (new Detector()).compute())('required arguments image, keyPoints');
      });

      it('should return a Mat with descriptors for each KeyPoint', () => {
        const desc = (new Detector(defaults)).compute(testImg, keyPoints);
        assertPropsWithValue(desc)({ rows: keyPoints.length });
      });
    });
  }
};
