const BackgroundSubtractorKNNTests = require('./BackgroundSubtractorKNNTests');
const BackgroundSubtractorMOG2Tests = require('./BackgroundSubtractorMOG2Tests');

module.exports = function (args) {
  describe('BackgroundSubtractorKNN', () => BackgroundSubtractorKNNTests(args));
  describe('BackgroundSubtractorMOG2', () => BackgroundSubtractorMOG2Tests(args));
};