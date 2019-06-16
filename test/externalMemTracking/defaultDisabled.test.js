const { expect } = require('chai');
const cv = require('../requireCv')();
const utils = require('../utils')(cv);

describe('External Memory Tracking', () => {
  it('should be enabled (opencv 3.1.0+)/ disabled(opencv 3.0.0) by default', () => {
    if (utils.cvVersionLowerThan(3, 1, 0)) {
      expect(cv.isCustomMatAllocatorEnabled()).to.be.false;
    } else {
      expect(cv.isCustomMatAllocatorEnabled()).to.be.true;
    }
  });
});
