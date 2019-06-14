const cv = global.dut;

const trackerParamTests = require('./trackerParamTests');
const trackerTests = require('./trackerTests');

describe('tracking', () => {
  if (!cv.modules.tracking) {
    it('compiled without tracking');
    return;
  }

  trackerParamTests();
  trackerTests();
});
