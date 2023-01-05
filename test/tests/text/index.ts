import textTests from './textTests';
import OCRHMMClassifierTests from './OCRHMMClassifierTests';
import OCRHMMDecoderTests from './OCRHMMDecoderTests';
import { TestContext } from '../model';

export default (args: TestContext) => {
  describe('text', () => textTests(args));
  describe('OCRHMMClassifier', () => OCRHMMClassifierTests(args));
  describe('OCRHMMDecoder', () => OCRHMMDecoderTests(args));
};
