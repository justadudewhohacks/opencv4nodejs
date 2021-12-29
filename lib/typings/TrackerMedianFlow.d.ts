import { Mat } from './Mat.d';
import { Rect } from './Rect.d';
import './openCV.js';

declare module "./openCV.js" {
  export class TrackerMedianFlow {
    constructor(pointsInGrid?: number);
    clear(): void;
    init(frame: Mat, boundingBox: Rect): boolean;
    update(frame: Mat): Rect;
  }
}