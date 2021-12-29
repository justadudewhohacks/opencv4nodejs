import { FeatureDetector } from './FeatureDetector.d';
import { SimpleBlobDetectorParams } from './SimpleBlobDetectorParams.d';
export * as cv from './openCV.js';

declare module "./openCV.js" {
  export class SimpleBlobDetector extends FeatureDetector {
    constructor(params: SimpleBlobDetectorParams);
  }
}