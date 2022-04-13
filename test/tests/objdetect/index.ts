import CascadeClassifierTests from './CascadeClassifierTests';
import HOGDescriptorTests from './HOGDescriptorTests';
import DetectionROITests from './DetectionROITests';
import { TestContext } from '../model';

export default (args: TestContext) => {
  describe('DetectionROI', () => DetectionROITests(args));
  describe('CascadeClassifier', () => CascadeClassifierTests(args));
  describe('HOGDescriptor', () => HOGDescriptorTests(args));
};