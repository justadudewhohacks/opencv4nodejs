import imgprocTests from './imgprocTests';
import MatImgprocTests from './MatImgprocTests';
import ContourTests from './ContourTests';
import { TestContext } from '../model';

export default (args: TestContext) => {
  describe('imgproc', () => imgprocTests(args));
  describe('MatImgproc', () => MatImgprocTests(args));
  describe('Contour', () => ContourTests(args));
};
