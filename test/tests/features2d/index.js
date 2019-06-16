const features2dTests = require('./features2dTests');
const KeyPointTests = require('./KeyPointTests');
const DescriptorMatchTests = require('./DescriptorMatchTests');
const BFMatcherTests = require('./BFMatcherTests');
const SimpleBlobDetectorParamsTests = require('./SimpleBlobDetectorParamsTests');
const descriptorMatchingTests = require('./descriptorMatchingTests');

module.exports = function (args) {
  describe('features2d', () => features2dTests(args));
  describe('KeyPoint', () => KeyPointTests(args));
  describe('DescriptorMatch', () => DescriptorMatchTests(args));
  describe('BFMatcher', () => BFMatcherTests(args));
  describe('SimpleBlobDetectorParams', () => SimpleBlobDetectorParamsTests(args));
  describe('descriptorMatching', () => descriptorMatchingTests(args));
};