const coreTests = require('./coreTests');
const MatTestSuite = require('./Mat');
const VecTestSuite = require('./Vec');
const PointTests = require('./PointTests');
const RectTests = require('./RectTests');
const TermCriteriaTests = require('./TermCriteriaTests');

module.exports = function (args) {
  describe('core', () => coreTests(args));
  describe('Mat', () => MatTestSuite(args));
  describe('Vec', () => VecTestSuite(args));
  describe('Point', () => PointTests(args));
  describe('Rect', () => RectTests(args));
  describe('TermCriteria', () => TermCriteriaTests(args));
};