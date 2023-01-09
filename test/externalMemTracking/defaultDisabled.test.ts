import { expect } from 'chai';
import cv from '@u4/opencv4nodejs';
import { TestContext } from '../tests/model';

const ctxt = new TestContext(cv);

describe('External Memory Tracking', () => {
  it('should be enabled (opencv 3.1.0+)/ disabled(opencv 3.0.0) by default', () => {
    if (ctxt.cvVersionLowerThan(3, 1, 0)) {
      expect(cv.isCustomMatAllocatorEnabled()).to.be.false;
    } else {
      expect(cv.isCustomMatAllocatorEnabled()).to.be.true;
    }
  });
});
