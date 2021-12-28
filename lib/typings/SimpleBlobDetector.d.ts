import { FeatureDetector } from './FeatureDetector.d';
import { SimpleBlobDetectorParams } from './SimpleBlobDetectorParams.d';
export * as cv from './cv';

declare module "./cv.js" {
  export class SimpleBlobDetector extends FeatureDetector {
    constructor(params: SimpleBlobDetectorParams);
  }
}