import { TestContext } from '../model';
import TrackerParamTests from './TrackerParamTests';
import TrackerTests from './TrackerTests';

export default (args: TestContext) => {
  describe('TrackerParams', () => TrackerParamTests(args));
  describe('Trackers', () => TrackerTests(args));
};
