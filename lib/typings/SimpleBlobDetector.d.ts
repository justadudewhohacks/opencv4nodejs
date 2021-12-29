import { FeatureDetector } from './FeatureDetector.d';
import { SimpleBlobDetectorParams } from './SimpleBlobDetectorParams.d';
import './openCV.js';

declare module "./openCV.js" {
  export class SimpleBlobDetector extends FeatureDetector {
    constructor(params: SimpleBlobDetectorParams);
  }
}