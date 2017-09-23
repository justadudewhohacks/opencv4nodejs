const cv = global.dut;
const BackgroundSubtractorKNNTests = require('./BackgroundSubtractorKNNTests');
const BackgroundSubtractorMOG2Tests = require('./BackgroundSubtractorMOG2Tests');

describe('objdetect', () => {
  BackgroundSubtractorKNNTests();
  BackgroundSubtractorMOG2Tests();
});
