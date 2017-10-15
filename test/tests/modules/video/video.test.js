const BackgroundSubtractorKNNTests = require('./BackgroundSubtractorKNNTests');
const BackgroundSubtractorMOG2Tests = require('./BackgroundSubtractorMOG2Tests');

describe('video', () => {
  BackgroundSubtractorKNNTests();
  BackgroundSubtractorMOG2Tests();
});
