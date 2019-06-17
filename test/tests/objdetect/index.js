const CascadeClassifierTests = require('./CascadeClassifierTests');
const HOGDescriptorTests = require('./HOGDescriptorTests');
const DetectionROITests = require('./DetectionROITests');

module.exports = function (args) {
  describe('DetectionROI', () => DetectionROITests(args));
  describe('CascadeClassifier', () => CascadeClassifierTests(args));
  describe('HOGDescriptor', () => HOGDescriptorTests(args));
};