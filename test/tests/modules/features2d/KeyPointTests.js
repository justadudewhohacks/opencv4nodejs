const cv = global.dut;
const { assertPropsWithValue, expectFloat } = global.utils;
const { expect } = require('chai');

module.exports = () => {
  describe('KeyPoint', () => {
    describe('constructor', () => {
      const point = new cv.Point(50, 50);
      const size = 2.5;
      const angle = Math.PI / 2;
      const response = 0.8;
      const octave = 21;
      const classId = 2;

      it('has default constructor', () => {
        expect(() => new cv.KeyPoint()).to.not.throw();
      });

      it('should throw if insufficient args passed', () => {
        expect(() => new cv.KeyPoint(point, undefined)).to.throw();
      });

      it('should be constructable with required args', () => {
        expect(() => new cv.KeyPoint(point, size, angle, response, octave, classId)).to.not.throw();
      });

      it('should initialize with correct values', () => {
        const kp = new cv.KeyPoint(point, size, angle, response, octave, classId);
        assertPropsWithValue(kp)({ size, octave, classId });
        expect(kp).to.have.property('point');
        assertPropsWithValue(kp.point)(point);
        expectFloat(kp.angle, angle);
        expectFloat(kp.response, response);
      });
    });
  });
};
