const { expect } = require('chai');

module.exports = ({ cv, utils, getTestImg }) => {

  const {
    assertMetaData,
    assertPropsWithValue,
    funcShouldRequireArgs
  } = utils;

  const history = 1000;
  const dist2Threshold = 100.5;
  const detectShadows = false;

  describe('constructor', () => {
    it('should be constructable with default args', () => {
      expect(() => new cv.BackgroundSubtractorKNN()).to.not.throw();
    });

    it('should be constructable with optional args', () => {
      const bgsubtractor = new cv.BackgroundSubtractorKNN(
        history,
        dist2Threshold,
        detectShadows
      );
      assertPropsWithValue(bgsubtractor)({
        history,
        dist2Threshold,
        detectShadows
      });
    });

    it('should be constructable with optional args object', () => {
      const bgsubtractor = new cv.BackgroundSubtractorKNN({
        history,
        dist2Threshold,
        detectShadows
      });
      assertPropsWithValue(bgsubtractor)({
        history,
        dist2Threshold,
        detectShadows
      });
    });

    it('should implement apply', () => {
      const bgsubtractor = new cv.BackgroundSubtractorKNN();
      expect(bgsubtractor).to.have.property('apply').to.be.a('function');
    });
  });

  describe('apply', () => {
    const learningRate = 2.5;

    it('should throw if no args', () => {
      expect(() => (new cv.BackgroundSubtractorKNN()).apply()).to.throw('BackgroundSubtractor::Apply - Error: expected argument 0 to be of type');
    });

    it('can be called if required args passed', () => {
      const bgsubtractor = new cv.BackgroundSubtractorKNN();
      const fgMask = bgsubtractor.apply(getTestImg());
      expect(fgMask).instanceOf(cv.Mat);
      assertMetaData(fgMask)(getTestImg().rows, getTestImg().cols, cv.CV_8U);
    });

    it('can be called with learningRate', () => {
      const bgsubtractor = new cv.BackgroundSubtractorKNN();
      const fgMask = bgsubtractor.apply(getTestImg(), learningRate);
      expect(fgMask).instanceOf(cv.Mat);
      assertMetaData(fgMask)(getTestImg().rows, getTestImg().cols, cv.CV_8U);
    });
  });

};
