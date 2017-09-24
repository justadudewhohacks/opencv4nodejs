const cv = global.dut;
const { assertPropsWithValue, funcShouldRequireArgs } = global.utils;
const { assert, expect } = require('chai');

describe('calib3d', () => {
  describe('findHomography', () => {
    const srcPoints = [{ x: 100, y: 100 }, { x: 100, y: -100 }, { x: -100, y: 100 }, { x: -100, y: -100 }];
    const dstPoints = srcPoints.map(srcPt => ({ x: srcPt.x * 2, y: srcPt.y * 2 }));
    const method = cv.RANSAC;
    const confidence = 0.9;

    funcShouldRequireArgs(cv.findHomography);

    it('can be called if required args passed', () => {
      expect(() => cv.findHomography(srcPoints, dstPoints)).to.not.throw();
    });

    it('can be called with optional args', () => {
      expect(() => cv.findHomography(srcPoints, dstPoints, method)).to.not.throw();
    });

    it('can be called with optional args object', () => {
      expect(() => cv.findHomography(
        srcPoints,
        dstPoints,
        { method, confidence })).to.not.throw();
    });

    it('should throw if point validation fails', () => {
      let errMsg = '';
      try {
        cv.findHomography([{ x: 100 }], [{ x: 100 }]);
      } catch (err) {
        errMsg = err.toString();
      }
      assert.include(errMsg, 'has no property: y');
    });

    it('should calculate a valid homography', () => {
      const homography = cv.findHomography(srcPoints, dstPoints);
      assertPropsWithValue(homography)({ type: cv.CV_64F, rows: 3, cols: 3 });
    });
  });
});
