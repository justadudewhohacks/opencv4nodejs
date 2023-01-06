import imgHashTestsFactory from './imgHashTests';
import { TestContext } from '../model';

export default (args: TestContext) => {
  // const { cvVersionGreaterEqual } = utils
  const imgHashTests = imgHashTestsFactory(args);
  describe('ImgHash', () => {
    describe('PHash', () => {
      imgHashTests(args.cv.PHash);
    });
  });
};
