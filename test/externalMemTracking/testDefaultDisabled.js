const { expect } = require('chai');
const requireCv = require('../dut');

describe('External Memory Tracking', () => {
  it('should be enabled (opencv 3.1.0+)/ disabled(opencv 3.0.0) by default', () => {
    const cv = requireCv();
    if (cv.version.minor < 1) {
      expect(cv.isCustomMatAllocatorEnabled()).to.be.false;
    } else {
      expect(cv.isCustomMatAllocatorEnabled()).to.be.true;
    }
  });
});
