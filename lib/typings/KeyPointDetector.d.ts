import { KeyPoint } from './KeyPoint.d';
import { Mat } from './Mat.d';
import './openCV.js';

declare module "./openCV.js" {
  export class KeyPointDetector {
    detect(image: Mat): KeyPoint[];
    detectAsync(image: Mat): Promise<KeyPoint[]>;
  }
}