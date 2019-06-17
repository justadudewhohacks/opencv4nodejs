const textTests = require('./textTests');
const OCRHMMClassifierTests = require('./OCRHMMClassifierTests');
const OCRHMMDecoderTests = require('./OCRHMMDecoderTests');

module.exports = function (args) {
  describe('text', () => textTests(args));
  describe('OCRHMMClassifier', () => OCRHMMClassifierTests(args));
  describe('OCRHMMDecoder', () => OCRHMMDecoderTests(args));
};