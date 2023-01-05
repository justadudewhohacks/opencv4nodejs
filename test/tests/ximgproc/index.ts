import ximgprocTests from './ximgprocTests';
import MatXImgprocTests from './MatXImgprocTests';
import { TestContext } from '../model';

export default (args: TestContext) => {
  describe('ximgproc', () => ximgprocTests(args));
  describe('MatXImgproc', () => MatXImgprocTests(args));
};
