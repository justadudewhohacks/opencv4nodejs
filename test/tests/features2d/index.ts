import features2dTests from './features2dTests';
import KeyPointTests from './KeyPointTests';
import DescriptorMatchTests from './DescriptorMatchTests';
import BFMatcherTests from './BFMatcherTests';
import SimpleBlobDetectorParamsTests from './SimpleBlobDetectorParamsTests';
import descriptorMatchingTests from './descriptorMatchingTests';
import { TestContext } from '../model';

export default (args: TestContext) => {
  describe('features2d', () => features2dTests(args));
  describe('KeyPoint', () => KeyPointTests(args));
  describe('DescriptorMatch', () => DescriptorMatchTests(args));
  describe('BFMatcher', () => BFMatcherTests(args));
  describe('SimpleBlobDetectorParams', () => SimpleBlobDetectorParamsTests(args));
  describe('descriptorMatching', () => descriptorMatchingTests(args));
};