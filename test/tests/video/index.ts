import { TestContext } from '../model';
import BackgroundSubtractorKNNTests from './BackgroundSubtractorKNNTests';
import BackgroundSubtractorMOG2Tests from './BackgroundSubtractorMOG2Tests';

export default (args: TestContext) => {
  describe('BackgroundSubtractorKNN', () => BackgroundSubtractorKNNTests(args));
  describe('BackgroundSubtractorMOG2', () => BackgroundSubtractorMOG2Tests(args));
};
