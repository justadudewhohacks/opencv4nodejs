import coreTests from './coreTests';
import MatTestSuite from './Mat';
import VecTestSuite from './Vec';
import PointTests from './PointTests';
import RectTests from './RectTests';
import TermCriteriaTests from './TermCriteriaTests';
import { TestContext } from '../model';

export default function (args: TestContext) {
  describe('core', () => coreTests(args));
  describe('Mat', () => MatTestSuite(args));
  describe('Vec', () => VecTestSuite(args));
  describe('Point', () => PointTests(args));
  describe('Rect', () => RectTests(args));
  describe('TermCriteria', () => TermCriteriaTests(args));
}
