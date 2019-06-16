const ParamGridTests = require('./ParamGridTests');
const StatModelTests = require('./StatModelTests');
const SVMTests = require('./SVMTests');
const TrainDataTests = require('./TrainDataTests');

module.exports = function (args) {
  describe('ParamGrid', () => ParamGridTests(args));
  describe('StatModel', () => StatModelTests(args));
  describe('TrainData', () => TrainDataTests(args));
  describe('SVM', () => SVMTests(args));
};
