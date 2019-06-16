const { expect } = require('chai');

module.exports = ({ cv, utils }) => {

  const {
    assertPropsWithValue
  } = utils;

  describe('constructor', () => {
    const queryIdx = 0;
    const trainIdx = 2;
    const distance = 2.5;

    it('has default constructor', () => {
      expect(() => new cv.DescriptorMatch()).to.not.throw();
    });

    it('should throw if insufficient args passed', () => {
      expect(() => new cv.DescriptorMatch(queryIdx, undefined)).to.throw();
    });

    it('should be constructable with required args', () => {
      expect(() => new cv.DescriptorMatch(queryIdx, trainIdx, distance)).to.not.throw();
    });

    it('should initialize with correct values', () => {
      const match = new cv.DescriptorMatch(queryIdx, trainIdx, distance);
      assertPropsWithValue(match)({ queryIdx, trainIdx, distance });
    });
  });

};
