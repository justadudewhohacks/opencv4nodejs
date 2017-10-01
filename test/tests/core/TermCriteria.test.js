const cv = global.dut;
const { assertPropsWithValue } = global.utils;
const { expect } = require('chai');

describe('TermCriteria', () => {
  describe('constructor', () => {
    it('has default constructor', () => {
      expect(() => new cv.TermCriteria()).to.not.throw();
    });

    it('can be constructed with args', () => {
      const type = cv.termCriteria.EPS;
      const maxCount = 100;
      const epsilon = 0.8;
      const termCriteria = new cv.TermCriteria(type, maxCount, epsilon);
      assertPropsWithValue(termCriteria)({ type, maxCount, epsilon });
    });
  });
});
