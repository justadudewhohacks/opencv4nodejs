const TrackerParamTests = require('./TrackerParamTests');
const TrackerTests = require('./TrackerTests');

module.exports = function (args) {
  describe('TrackerParams', () => TrackerParamTests(args));
  describe('Trackers', () => TrackerTests(args));
};